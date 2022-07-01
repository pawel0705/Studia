using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddElementOnChain : MonoBehaviour
{
    public bool attachToChain = false;

    [SerializeField]
    private Transform lastChainElement;

    [SerializeField]
    private PlayerMovement playerMovement;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (attachToChain)
        {
            transform.position = new Vector3(lastChainElement.position.x, lastChainElement.position.y, lastChainElement.position.z);
        }

        if (Input.GetKeyDown(KeyCode.K))
        {
            attachToChain = false;
            playerMovement.hasPickableElement = false;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.name == "Player")
        {
            if (!playerMovement.hasPickableElement)
            {
                attachToChain = true;
                playerMovement.hasPickableElement = true;
            }
        }
    }
}
