using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyMovement : MonoBehaviour
{
    [SerializeField]
    private Vector3 origin;
    [SerializeField]
    private float movementSpeed = 10f;

    private Transform playersTransform;
    private bool isChasing;

    public Vector3 Origin { get => origin; set { origin = value; } }
    private void Start()
    {
        playersTransform = PlayerController.Instance.transform;
    }

    private void Update()
    {
        if (isChasing)
        {
            transform.position = Vector3.MoveTowards(transform.position, playersTransform.position, Time.deltaTime * movementSpeed);
        }
    }

    public void StopChasing()
    {
        isChasing = false;
    }

    public void Chase()
    {
        isChasing = true;
    }
}
