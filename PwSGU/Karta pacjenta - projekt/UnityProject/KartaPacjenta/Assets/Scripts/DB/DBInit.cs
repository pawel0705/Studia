using Assets.Model;
using Assets.Model.DAL;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class DBInit : MonoBehaviour
{
    private string dbPath;
    public string dbName = "database.db";
   
    /// <summary>
    /// Initializes the DB before any Start method is called
    /// </summary>
    void Awake()
    {
        dbPath = Application.persistentDataPath + "/" + dbName;
        Debug.Log("Creating DB in path" + dbPath);

        if (!System.IO.File.Exists(dbPath))
        {
            string filePath = System.IO.Path.Combine(Application.streamingAssetsPath, dbName);
            byte[] result = { };
            result = System.IO.File.ReadAllBytes(filePath);

            System.IO.File.WriteAllBytes(dbPath, result);
        }

        if (!DBManager.isInitialized)
        {
            DBManager.Initialize("URI=file:" + dbPath);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
