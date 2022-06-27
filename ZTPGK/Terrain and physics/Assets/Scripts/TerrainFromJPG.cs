using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TerrainFromJPG : MonoBehaviour
{
    public Texture2D heightMap;

    private int xRes;
    private int yRes;

    private float[,] heights;

    private Terrain terrain;
    private TerrainData tData;

    void Start()
    {
        Initialize();
        ResizeImage();
    }

    void Update() 
    {
    
    }

    private void Initialize()
    {
        terrain = transform.GetComponent<Terrain>();
        tData = terrain.terrainData;

        xRes = tData.heightmapResolution;
        yRes = tData.heightmapResolution;
    }

    private void ResizeImage()
    {
        RenderTexture rt = new RenderTexture(xRes, yRes, 24);
        RenderTexture.active = rt;
        Graphics.Blit(heightMap, rt);
        Texture2D result = new Texture2D(xRes, yRes);
        result.ReadPixels(new Rect(0, 0, xRes, yRes), 0, 0);
        result.Apply();

        heightMap = result;
    }

    public void SetPoints()
    {
        heights = tData.GetHeights(0, 0, xRes, yRes);

        for (int x = 0; x < xRes; x++)
        {
            for (int y = 0; y < yRes; y++)
            {
                heights[x, y] = Mathf.Abs(1 - heightMap.GetPixel(y, x).grayscale) * 0.6f;
            }
        }

        tData.SetHeights(0, 0, heights);
    }
}
