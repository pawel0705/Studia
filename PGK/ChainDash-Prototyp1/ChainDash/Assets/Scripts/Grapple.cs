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
    private GameObject chain;

    [SerializeField]
    private GameObject chainStart;

    [SerializeField]
    private PlayerMovement playerMovement;

    private Hook hook;
    private bool pulling;
    private int pullSpeed = 100;
    private Rigidbody rigid;

    public CharacterController playerCharacterController;
    public Collider playerCollider;
    public Rigidbody playerGidbody;

    // Start is called before the first frame update
    void Start()
    {
        rigid = GetComponent<Rigidbody>();
        pulling = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (hook == null && Input.GetMouseButton(1))
        {
            StopAllCoroutines();
            pulling = false;
            hook = Instantiate(hookPrefab, shootTransform.position, Quaternion.identity).GetComponent<Hook>();
            hook.Initialize(this, shootTransform);
            StartCoroutine(DestroyHookAfterLifetime());

            chainStart.SetActive(false);
            chain.SetActive(false);
            playerMovement.hasPickableElement = false;

            GameObject[] pickableElements = GameObject.FindGameObjectsWithTag("PickableElement");

            foreach (GameObject element in pickableElements)
            {
                element.GetComponent<AddElementOnChain>().attachToChain = false;
            }

        }
        else if (hook != null && !Input.GetMouseButton(1))
        {
            DestroyHook();
            playerMovement.isGrounded = true;
            playerMovement.pullingOnChain = false;
            playerMovement.velocity.y = Mathf.Sqrt(playerMovement.jumpHeight * -2f * playerMovement.gravity);
        }

        if (!pulling || hook == null) return;

        if (Vector3.Distance(transform.position, hook.transform.position) <= stopDistance)
        {
            DestroyHook();
            playerMovement.isGrounded = true;
            playerMovement.pullingOnChain = false;
            playerMovement.velocity.y = Mathf.Sqrt(playerMovement.jumpHeight * -2f * playerMovement.gravity);
        }
        else
        {
            Debug.Log(pullSpeed * Time.deltaTime);
            rigid.AddForce((hook.transform.position - transform.position).normalized * pullSpeed * Time.deltaTime, ForceMode.VelocityChange);
        }
    }

    public void StartPull()
    {
        pulling = true;
        playerCharacterController.enabled = false;
        playerCollider.enabled = true;
        playerGidbody.useGravity = true;
        playerGidbody.isKinematic = false;
        playerMovement.pullingOnChain = true;
    }

    private void DestroyHook()
    {
        if (hook == null) return;

        pulling = false;
        Destroy(hook.gameObject);
        playerCharacterController.enabled = true;
        playerCollider.enabled = false;
        playerGidbody.useGravity = false;
        playerGidbody.isKinematic = true;
        hook = null;

        chainStart.SetActive(true);
        chain.SetActive(true);
    }

    private IEnumerator DestroyHookAfterLifetime()
    {
        yield return new WaitForSeconds(6f);

        DestroyHook();
    }
}
