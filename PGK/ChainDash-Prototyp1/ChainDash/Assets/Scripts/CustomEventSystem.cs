using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomEventSystem : MonoBehaviour
{
    #region Singleton
    private static CustomEventSystem instance;

    public static CustomEventSystem Instance { get { return instance; } }
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

    public event Action<int> onEnemyDeath;
    public void OnEnemyDeath(int id)
    {
        if (onEnemyDeath != null)
        {
            onEnemyDeath(id);
        }
    }

}
