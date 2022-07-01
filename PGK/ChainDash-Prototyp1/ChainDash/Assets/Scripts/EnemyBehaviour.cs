using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBehaviour : MonoBehaviour, IDamageable
{
    private enum State
    {
        Idle = 0,
        Chase = 1
    }

    [SerializeField]
    private EnemyMovement enemyMovement;
    [SerializeField]
    private float playerDetectionRange;
    [SerializeField]
    private string hitTag;

    private State state;
    private int _id;
    private Transform playersTransform;

    public int id { get => _id; set { _id = value; } }

    private void Start()
    {
        playersTransform = PlayerController.Instance.transform;
        enemyMovement = GetComponent<EnemyMovement>();
    }

    private void FixedUpdate()
    {
        switch (state)
        {
            case State.Idle:
                {
                    enemyMovement.StopChasing();
                    ChangeState();
                    break;
                }
            case State.Chase:
                {
                    enemyMovement.Chase();
                    ChangeState();
                    break;
                }
            default:
                {
                    break;
                }
        }
    }

    private void ChangeState()
    {
        state = DetectPlayer() ? State.Chase : State.Idle;
    }

    private bool DetectPlayer()
    {
        if(Vector3.Distance(transform.position, playersTransform.position) <= playerDetectionRange)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public void Die()
    {
        Destroy(gameObject);
        CustomEventSystem.Instance.OnEnemyDeath(_id);
    }

    public void TakeDamage()
    {
        Die();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.transform.TryGetComponent(out AddElementOnChain addElementOnChain))
        {
            TakeDamage();
        }
    }
}
