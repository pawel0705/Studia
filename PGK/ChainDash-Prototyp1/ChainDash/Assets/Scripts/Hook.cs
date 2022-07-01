using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hook : MonoBehaviour
{
    private int hookForce = 1000;

    Grapple grapple;
    Rigidbody rigid;
    LineRenderer lineRenderer;

    public void Initialize(Grapple grapple, Transform  shootTransform)
    {
        transform.forward = shootTransform.forward;
        this.grapple = grapple;
        rigid = GetComponent<Rigidbody>();
        lineRenderer = GetComponent<LineRenderer>();
        rigid.AddForce((transform.forward + transform.up / 2) * hookForce * Time.deltaTime, ForceMode.Impulse);
    }

    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {
        Vector3[] positions = new Vector3[]
        {
            transform.position,
            grapple.transform.position
        };

        lineRenderer.SetPositions(positions);
    }

    private void OnTriggerEnter(Collider other)
    {
        if(((LayerMask.GetMask("Grapple") & 1 << other.gameObject.layer) > 0) || 
            ((LayerMask.GetMask("Ground") & 1 << other.gameObject.layer) > 0))
        {
            rigid.useGravity = false;
            rigid.isKinematic = true;

            grapple.StartPull();
        }
    }
}
