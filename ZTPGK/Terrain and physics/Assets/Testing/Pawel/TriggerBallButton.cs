using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerBallButton : MonoBehaviour
{
    public GameObject ball;

    public Direction direction;

    public float ballForce = 2000f;

    private float forceX = 0f;
    private float forceY = 0f;

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.name == "Player")
        {
            switch (direction)
            {
                case Direction.North:
                    forceX = 0f;
                    forceY = ballForce;
                    break;
                case Direction.East:
                    forceX = ballForce;
                    forceY = 0f;
                    break;
                case Direction.South:
                    forceX = 0f;
                    forceY = -ballForce;
                    break;
                case Direction.West:
                    forceX = -ballForce;
                    forceY = 0f;
                    break;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.name == "Player")
        {
            forceX = 0f;
            forceY = 0f;
        }
    }

    private void FixedUpdate()
    {
        ball.GetComponentInParent<Rigidbody>().AddForce(forceX * Time.deltaTime, 0f, forceY * Time.deltaTime);
    }
}


public enum Direction { North, East, South, West };