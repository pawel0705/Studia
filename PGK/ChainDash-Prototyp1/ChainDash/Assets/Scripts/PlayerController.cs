using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class PlayerController : MonoBehaviour, IDamageable
{
    #region Singleton
    private static PlayerController instance;

    public static PlayerController Instance { get { return instance; } }
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

    [SerializeField]
    private string collisionTag;

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.transform.tag == collisionTag)
        {
            TakeDamage();
        }
    }

    public void Die()
    {
        GameManager.Instance.OnPlayersDeath.Invoke();
    }

    public void TakeDamage()
    {
        Die();
    }
}
