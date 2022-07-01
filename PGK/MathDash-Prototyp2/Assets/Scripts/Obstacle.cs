using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Obstacle : MonoBehaviour
{
    [SerializeField] 
    private SO_GameController gameController;

    private void Awake()
    {
        gameController.isGameOver = false;
    }

    // Start is called before the first frame update
    private void OnTriggerEnter(Collider other)
    {
        Time.timeScale = 0;
        gameController.isGameOver = true;
    }
}
