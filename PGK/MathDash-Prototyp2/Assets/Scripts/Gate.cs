using System;
using UnityEngine;

public class Gate : MonoBehaviour
{

    [SerializeField]
    private SO_GameController gameController;
    
    public bool IsCorrect { get; set; }

    private void Awake()
    {
        gameController.isGameOver = false;
    }

    private void Update()
    {
        if (IsCorrect)
        {
            gameObject.SetActive(false);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        gameController.isGameOver = true;
        Time.timeScale = 0;
    }
}
