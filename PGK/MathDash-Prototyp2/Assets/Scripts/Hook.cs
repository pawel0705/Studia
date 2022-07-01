using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hook : MonoBehaviour
{
    private int hookForce = 300000;

    Grapple grapple;
    Rigidbody rigid;
    LineRenderer lineRenderer;

    public void Initialize(Grapple grapple, Transform shootTransform)
    {
        RaycastHit hit = new RaycastHit();

        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(ray, out hit, 1000, ~1 << 6))
        {
            if (!hit.collider.gameObject.name.Contains("Pullable"))
            {
                return;
            }
        } else
        {
            return;
        }

        transform.forward = shootTransform.forward;
        this.grapple = grapple;
        rigid = GetComponent<Rigidbody>();
        lineRenderer = GetComponent<LineRenderer>();


        if (Physics.Raycast(ray, out hit, 1000, ~1 << 6))
        {
            if (!hit.collider.gameObject.name.Contains("Pullable"))
            {
                return;
            }

            var pos = hit.collider.gameObject.transform.position;

            Debug.Log(hit.collider.gameObject.name);

            var diffVec = (pos - transform.position);
            rigid.AddForce(diffVec / diffVec.magnitude * Time.deltaTime * hookForce);
        }
    }

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        var positions = new Vector3[]
        {
            transform?.position ?? new Vector3(-100,-100,-100),
            grapple?.transform?.position ?? new Vector3(-100,-100,-100)
        };

        lineRenderer?.SetPositions(positions);
    }

    private void OnTriggerEnter(Collider other)
    {
        if ((LayerMask.GetMask("Grapple") & 1 << other.gameObject.layer) > 0)
        {
            rigid.useGravity = false;
            rigid.isKinematic = true;

            grapple.StartPull();
        }
    }
}
