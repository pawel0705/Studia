using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grapple : MonoBehaviour
{
    [SerializeField]
    private float stopDistance = 4f;

    [SerializeField]
    private GameObject hookPrefab;

    [SerializeField]
    private Transform shootTransform;

    [SerializeField]
    private PlayerMovement playerMovement;

    private Hook hook;
    private bool pulling;
    private int pullSpeed = 50;
    private Rigidbody rigid;

    public CharacterController playerCharacterController;


    // Start is called before the first frame update
    void Start()
    {
        rigid = GetComponent<Rigidbody>();
        pulling = false;
        playerMovement.pullingOnChain = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (hook == null && Input.GetMouseButton(1))
        {
            StopAllCoroutines();
            pulling = false;
            playerMovement.pullingOnChain = false;
            hook = Instantiate(hookPrefab, shootTransform.position, Quaternion.identity).GetComponent<Hook>();
            hook.Initialize(this, shootTransform);
            StartCoroutine(DestroyHookAfterLifetime());
        }
        else if (hook != null && !Input.GetMouseButton(1))
        {
            DestroyHook();
        }

        if (!pulling || hook == null) return;

        if (Vector3.Distance(transform.position, hook.transform.position) <= stopDistance)
        {
            DestroyHook();
        }
        else
        {
            rigid.AddForce((hook.transform.position - transform.position).normalized * pullSpeed * Time.deltaTime, ForceMode.VelocityChange);
        }
    }

    public void StartPull()
    {
        pulling = true;
        playerMovement.pullingOnChain = true;
        playerCharacterController.enabled = false;
    }

    private void DestroyHook()
    {
        if (hook == null) return;

        Destroy(hook.gameObject);
        pulling = false;
        playerMovement.pullingOnChain = false;
        hook = null;
    }

    private IEnumerator DestroyHookAfterLifetime()
    {
        yield return new WaitForSeconds(4f);

        DestroyHook();
        playerMovement.pullingOnChain = false;
        pulling = false;
    }
}
