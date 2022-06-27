using System;
using UnityEngine;
using UnityEngine.UI;

public class TerrainManager2 : MonoBehaviour
{
    private Terrain terrain;
    private TerrainData terrainData;
    private int terrainSize;

    private float[,] originalTerrainHeights;
    private Vector2Int animatedTerrainPos = new Vector2Int(100, 100);
    private int animatedTerrainHalfSize = 100;

    // Start is called before the first frame update
    void Start()
    {
        terrain = GetComponent<Terrain>();
        if (terrain == null)
        {
            throw new Exception("terrain object is null!");
        }

        terrainData = terrain.terrainData;
        terrainSize = terrainData.heightmapResolution;

        terrainData.SetHeights(0, 0, RandomiseTerrain(terrainSize));
        //ustawić to po utworzeniu terenu
        originalTerrainHeights = terrainData.GetHeights(animatedTerrainPos.x, animatedTerrainPos.y, animatedTerrainHalfSize * 2, animatedTerrainHalfSize * 2);
    }

    private void Update()
    {
        AnimateTerrain();
    }

    private void OnApplicationQuit()
    {
        FlattenTerrain();
    }

    private void FlattenTerrain()
    {
        var terrainHeights = new float[terrainSize, terrainSize];
        for (int x = 0; x < terrainSize; ++x)
        {
            for (int y = 0; y < terrainSize; ++y)
            {
                terrainHeights[x, y] = 0;
            }
        }
        terrainData.SetHeights(0, 0, terrainHeights);
    }

    private float[,] RandomiseTerrain(int size)
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

    private void AnimateTerrain()
    {
        var newHeights = terrainData.GetHeights(animatedTerrainPos.x, animatedTerrainPos.y, animatedTerrainHalfSize * 2, animatedTerrainHalfSize * 2);
        Vector2 middle = new Vector2(animatedTerrainHalfSize, animatedTerrainHalfSize);
        for (int i = 0; i < animatedTerrainHalfSize * 2; ++i)
        {
            for (int j = 0; j < animatedTerrainHalfSize * 2; ++j)
            {
                Vector2 point = new Vector2(i, j);
                float distance = Vector2.Distance(point, middle);
                if (distance < animatedTerrainHalfSize)
                {
                    //value: 0.0 - 1.0
                    float distanceNorm = (animatedTerrainHalfSize - distance) / animatedTerrainHalfSize;
                    float x = Time.time + distance * 0.0125f;
                    newHeights[i, j] = (float)Math.Abs(Math.Sin(x + 1.8*Math.Sin(x)) * 0.66f + 1f) * distanceNorm * distanceNorm * originalTerrainHeights[i, j] + originalTerrainHeights[i, j];
                }
            }
        }
        terrainData.SetHeights(animatedTerrainPos.x, animatedTerrainPos.y, newHeights);
    }

    //funkcja do obrotu terenu - nie została użyta
    private float[,] fun(float[,] inArray, int offset)
    {
        int arraySize = inArray.GetLength(0);
        int currentLength = arraySize - 2 * offset;
        if (currentLength <= 1)
            return inArray;


        float[,] array = (float[,])inArray.Clone();

        //first row
        for (int i = 0; i < currentLength - 1; ++i)
        {
            array[offset + i, offset] = inArray[offset + i + 1, offset];
        }
        //last row
        for (int i = 1; i < currentLength; ++i)
        {
            array[offset + i, arraySize - 1 - offset] = inArray[offset + i - 1, arraySize - 1 - offset];
        }

        //first collumn
        for (int i = 1; i < currentLength; ++i)
        {
            array[offset, offset + i] = inArray[offset, offset + i - 1];
        }
        //last collumn
        for (int i = 0; i < currentLength - 1; ++i)
        {
            array[arraySize - 1 - offset, offset + i] = inArray[arraySize - 1 - offset, offset + i + 1];
        }

        array = fun(array, offset + 1);
        return array;
    }
}
