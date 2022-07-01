using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    #region Singleton
    private static GameManager instance;

    public static GameManager Instance { get { return instance; } }
    private void Awake()
    {
        if (instance != null && instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            instance = this;
        }
    }
    #endregion

    public Action OnPlayersDeath;
    private void Start()
    {
        OnPlayersDeath += LoadLastCheckpoint;   
    }

    private void OnDestroy()
    {
        OnPlayersDeath -= LoadLastCheckpoint;
    }

    private void LoadLastCheckpoint()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
