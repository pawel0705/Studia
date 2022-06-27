using System;
using UnityEngine;

public class TerrainManager : MonoBehaviour
{
    private Terrain terrain;
    private TerrainData terrainData;
    private int terrainSize;

    private float[,] originalTerrainHeights;
    private float[,] randomisedHeights;
    private readonly Vector2Int animTerrainPosition = new Vector2Int(100, 100);
    private readonly int animTerrainSize = 200;

    private bool animateTerrain = false;

    void Start()
    {
        terrain = GetComponent<Terrain>();
        if (terrain == null)
        {
            throw new Exception("Terrain object is null!");
        }
        terrainData = terrain.terrainData;
        terrainSize = terrainData.heightmapResolution;

        randomisedHeights = GetRandomisedTerrainHeights(terrainSize);
        terrainData.SetHeights(0, 0, randomisedHeights);
        originalTerrainHeights = terrainData.GetHeights(animTerrainPosition.x, animTerrainPosition.y, animTerrainSize, animTerrainSize);
    }

    public void StartAnimateTerrain()
    {
        terrainData.SetHeights(0, 0, randomisedHeights);
        originalTerrainHeights = terrainData.GetHeights(animTerrainPosition.x, animTerrainPosition.y, animTerrainSize, animTerrainSize);
        animateTerrain = true;
    }

    public void StopAnimateTerrain()
    {
        animateTerrain = false;
        FlattenTerrain();
    }

    void Update()
    {
        if (animateTerrain)
        {
            AnimateTerrain(animTerrainPosition.x, animTerrainPosition.y, animTerrainSize);
        }
    }

    private void OnApplicationQuit()
    {
        FlattenTerrain();
    }

    private float[,] GetRandomisedTerrainHeights(int size)
    {
        var newHeights = new float[size, size];

        const int numberOfRepeats = 5;
        float[] scale = new float[numberOfRepeats];
        for (int k = 0; k < numberOfRepeats; ++k)
        {
            scale[k] = UnityEngine.Random.Range(1.5f, 2.5f);
        }
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                float xCoeff = (float)i / size;
                float yCoeff = (float)j / size;

                newHeights[i, j] = 0;
                for (int k = 0; k < numberOfRepeats; ++k)
                {
                    newHeights[i, j] += Mathf.PerlinNoise(xCoeff * scale[k], yCoeff * scale[k]);
                }
                newHeights[i, j] /= numberOfRepeats;
            }
        }
        return newHeights;
    }

    private void AnimateTerrain(int posX, int posY, int size)
    {
        var newHeights = terrainData.GetHeights(posX, posY, size, size);
        Vector2 middle = new Vector2(size * 0.5f, size * 0.5f);
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                Vector2 point = new Vector2(i, j);
                float distance = Vector2.Distance(point, middle);
                if (distance < size * 0.5f)
                {
                    //value: 0.0 - 1.0
                    float distanceNorm = (size * 0.5f - distance) / (size * 0.5f);
                    float x = Time.time + distance * 0.0125f;
                    newHeights[i, j] = (float)Math.Abs(Math.Sin(x + 1.8f * Math.Sin(x)) * 0.66f + 1f) * distanceNorm * distanceNorm * originalTerrainHeights[i, j] + originalTerrainHeights[i, j];
                }
            }
        }
        terrainData.SetHeights(posX, posY, newHeights);
    }

    private void FlattenTerrain()
    {
        var terrainHeights = new float[terrainSize, terrainSize];
        for (int i = 0; i < terrainSize; ++i)
        {
            for (int j = 0; j < terrainSize; ++j)
            {
                terrainHeights[i, j] = 0.0f;
            }
        }
        terrainData.SetHeights(0, 0, terrainHeights);
    }
}
