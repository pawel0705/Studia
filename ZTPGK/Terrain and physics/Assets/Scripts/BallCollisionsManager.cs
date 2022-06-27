using System;
using UnityEngine;

public class BallCollisionsManager : MonoBehaviour
{
    public GameObject respawnPoint;
    public GameObject victoryArea;

    public GameObject resetFloor;

    public GameObject traps;
    public GameObject trapsTrigger;

    private Rigidbody ballRigidbody;
    public void Start()
    {
        ballRigidbody = GetComponent<Rigidbody>();
        if(ballRigidbody == null)
        {
            throw new Exception("Rigidbody object is null!");
        }
    }

    private void ResetGame()
    {
        transform.position = respawnPoint.transform.position;
        ballRigidbody.velocity = Vector3.zero;
        ballRigidbody.angularVelocity = Vector3.zero;
        traps.SetActive(false);
    }

    private void OnCollisionEnter(UnityEngine.Collision collision)
    {
        if (collision.gameObject.Equals(resetFloor))
        {
            Debug.Log("RESET");
            ResetGame();
        }
        else if (collision.gameObject.CompareTag("Trap"))
        {
            Debug.Log("ZDERZENIE");
            ResetGame();
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.Equals(victoryArea))
        {
            Debug.Log("WYGRANA");
            ResetGame();
        }
        else if (other.gameObject.Equals(trapsTrigger))
        {
            traps.SetActive(true);
        }
    }
}
