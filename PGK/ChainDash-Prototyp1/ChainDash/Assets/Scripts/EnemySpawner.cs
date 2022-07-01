using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    [SerializeField]
    private Dictionary<Vector3, EnemyBehaviour> enemies;
    [SerializeField]
    private Vector3[] spawnPoints;
    [SerializeField]
    private GameObject enemyPrefab;
    [SerializeField]
    private int iD;

    private void Start()
    {
        enemies = new Dictionary<Vector3, EnemyBehaviour>();
        foreach (var sp in spawnPoints)
        {
            enemies.Add(sp, null);
        }
        CustomEventSystem.Instance.onEnemyDeath += EnemyDeath;

        foreach (var sp in spawnPoints)
        {
            enemies.TryGetValue(sp, out EnemyBehaviour value);
            if (value == null)
            {
                SpawnEnemy(sp);
            }
        }
    }

    private void EnemyDeath(int id)
    {
        if (id == iD)
        {
            foreach (var enemy in enemies)
            {
                if (enemy.Value == null)
                {
                    SpawnEnemy(enemy.Key);
                    break;
                }
            }
        }
    }

    private void SpawnEnemy(Vector3 spawnPoint)
    {
        var go = Instantiate(enemyPrefab, spawnPoint, Quaternion.identity);
        var enemy = go.GetComponent<EnemyBehaviour>();
        enemy.GetComponent<EnemyMovement>().Origin = spawnPoint;
        enemies[spawnPoint] = enemy;
        enemy.id = iD;
    }
}
