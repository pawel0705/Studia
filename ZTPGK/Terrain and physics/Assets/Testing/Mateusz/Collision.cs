using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collision : MonoBehaviour
{
    public GameObject ball;
    public GameObject respawnArea;

    private void OnCollisionEnter(UnityEngine.Collision collision)
    {
        Debug.Log("Coś");
        if(collision.gameObject.Equals(ball))
        {
            ball.transform.position = respawnArea.transform.position;
        }
    }
}
