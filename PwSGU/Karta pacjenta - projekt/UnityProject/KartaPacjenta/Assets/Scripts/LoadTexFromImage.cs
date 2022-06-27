using Assets.Model.DAL;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;

public class LoadTexFromImage : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        // Load image data from DataBase
        var fileId = GetComponent<DBSyncFile>().fileId;
        byte[] imageData = FileDAO.GetFile(fileId)?.Data;
        Texture2D image = new Texture2D(1, 1, TextureFormat.ARGB32, false);
        image.LoadImage(imageData);

        Texture2D flipped = new Texture2D(image.width, image.height);

        int originalWidth = image.width;
        int originalHeight = image.height;

        // Rotating image 180 degrees, because image loads upside-down by default
        for (int x = 0; x < originalWidth; x++)
        {
            for (int y = 0; y < originalHeight; y++)
            {
                flipped.SetPixel(originalWidth - x - 1, originalHeight - y - 1, image.GetPixel(x, y));
            }
        }

        flipped.Apply();

        // Apply texture to object
        GetComponent<Renderer>().material.mainTexture = flipped;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

}
