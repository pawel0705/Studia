using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Generator : MonoBehaviour
{
    [SerializeField]
    private List<GameObject> platforms;
    private List<GameObject> livePlatforms = new List<GameObject>();
    private int id;
    [SerializeField]
    private GameObject player;
    private float currentPosition;
    private float zPos = 0;
    private int counter = 4;
    private GameObject tmp;

    private void Start()
    {
        currentPosition = player.transform.position.z;
        Generate();
    }

    private void GenerateFirstOnes()
    {
        for(int i = 0; i < 3; i++)
        {
            GeneratePlatform(i);
        }
    }

    void Update()
    {
        currentPosition = player.transform.position.z;
        DestroyPlatforms();
    }

    private void GeneratePlatform(int id)
    {
        tmp = (GameObject)Instantiate(platforms[id], new Vector3(0, 0, zPos), Quaternion.identity);
        livePlatforms.Add(tmp);
        zPos += 50;
    }

    private void Generate()
    {
        for (int i = 0; i < 3; i++)
        {
            GenerateFirstOnes();
            GeneratePlatform(3);
        }
       
        GeneratePlatform(4);
       
    }

    private void DestroyPlatforms()
    {
        for (int i = livePlatforms.Count - 1; i >= 0; i--)
        {
            GameObject platform = livePlatforms[i];
            if (currentPosition - platform.transform.position.z  > 100 && platform!=null)
            {
                livePlatforms.RemoveAt(i);
                Destroy(platform);
            }
        }
    }
}

