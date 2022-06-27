using Assets.Model;
using Assets.Model.DAL;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DBSyncFile : MonoBehaviour
{
    public int fileId = -1;
    public float updateTime = 1;
    /// <summary>
    /// Starts a data saving coroutine
    /// </summary>
    void Start()
    {
        StartCoroutine(UpdateFileCoroutine());
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    /// <summary>
    /// Periodically save this object transformation to DB
    /// </summary>
    /// <returns></returns>
    IEnumerator UpdateFileCoroutine()
    {
        while (true)
        {
            yield return new WaitForSeconds(updateTime);
            File file = FileDAO.GetFile(fileId);
            file.PosX = transform.position.x;
            file.PosY = transform.position.y;
            file.PosZ = transform.position.z;
            file.RotX = transform.rotation.eulerAngles.x;
            file.RotY = transform.rotation.eulerAngles.y;
            file.RotZ = transform.rotation.eulerAngles.z;
            file.ScaleX = transform.localScale.x;
            file.ScaleY = transform.localScale.y;
            file.ScaleZ = transform.localScale.z;
            FileDAO.UpdateFile(file);
        }
    }
}
