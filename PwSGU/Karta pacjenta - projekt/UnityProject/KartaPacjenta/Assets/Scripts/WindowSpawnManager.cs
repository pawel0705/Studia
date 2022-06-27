using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Microsoft.MixedReality.Toolkit.UI;
using Assets.Model;
using Assets.Model.DAL;
using System.Linq;
using Microsoft.MixedReality.Toolkit.WindowsMixedReality;
using Microsoft.MixedReality.Toolkit.UI.BoundsControl;

public class WindowSpawnManager : MonoBehaviour
{
    public int patientId = 1;
    private List<GameObject> spawnedWindows = null;
    private GameObject windowPrefab;

    private void Start()
    {
		//Loading MR_Window prefab from assets
        windowPrefab = Resources.Load("MR_Window") as GameObject;

		//Getting data from database
        Patient patient = PatientDAO.GetPatient(patientId);
        if (patient.FilesVisible)
        {
            spawnedWindows = new List<GameObject>();

			//Spawning MR_Window with data which should be visible
            foreach (var file in patient.Files)
            {
                SpawnWindow(new Vector3(file.PosX, file.PosY, file.PosZ),
                    Quaternion.Euler(file.RotX, file.RotY, file.RotZ),
                    new Vector3(file.ScaleX, file.ScaleY, file.ScaleZ),
                    $"{patient.Name} {patient.Surname}",
                    file.Id);
            }
        }
    }

	// Method for spawning/destroying windows with patient data
    public void SpawnWindowsForPatient()
    {
		//Getting data from database
        Patient patient = PatientDAO.GetPatient(patientId);
        if (spawnedWindows == null)
        {
            spawnedWindows = new List<GameObject>();

			//Spawning MR_Window with patient data
            foreach (var file in patient.Files)
            {
                SpawnWindow(new Vector3(file.PosX, file.PosY, file.PosZ),
                    Quaternion.Euler(file.RotX, file.RotY, file.RotZ),
                    new Vector3(file.ScaleX, file.ScaleY, file.ScaleZ),
                    $"{patient.Name} {patient.Surname}",
                    file.Id);
            }
			//Saving information that data is visible
            patient.FilesVisible = true;
            PatientDAO.UpdatePatient(patient);
        }
        else
        {
			//Destroying MR_Windows with patient data
            foreach(var window in spawnedWindows)
            {
                Destroy(window);
            }
            spawnedWindows = null;
			//Saving information that data is not visible
            patient.FilesVisible = false;
            PatientDAO.UpdatePatient(patient);
        }
    }

	//Test method - for spawning one window
    public void SpawnWin1()
    {
        SpawnWindow(new Vector3(1, 1, 1), new Quaternion(), new Vector3(1, 1, 1), "Patient 1");
    }

	//Test method - for spawning one window
    public void SpawnWin2()
    {
        SpawnWindow(new Vector3(-1, -1, -1), new Quaternion(), new Vector3(1, 1, 1), "Patient 2");
    }

	//Test method - for spawning one window
    public void SpawnWin3()
    {
        SpawnWindow(new Vector3(0.5f, 0.5f, 0.5f), new Quaternion(), new Vector3(1, 1, 1), "Patient 3");
    }

	//Method for instanting prefab MR_Window with chosen transform
    private void SpawnWindow(Vector3 position, Quaternion rotation, Vector3 scale, string tooltip, int fileId = -1)
    {
		//Spawning object with given rotation and position
        GameObject newObject = Instantiate(windowPrefab, position, rotation, gameObject.transform);
		//Changing scale of object
        newObject.transform.localScale = scale;
        //newObject.GetComponent<ToolTip>().ToolTipText = tooltip;
		//Setting id of file
        newObject.GetComponent<DBSyncFile>().fileId = fileId;
		//Setting tooltip text
        newObject.GetComponent<ToolTipSpawner>().toolTipText = tooltip;
		//Setting BoundsControl settings
        newObject.GetComponent<BoundsControl>().TranslationHandlesConfig.HandleSize = 0.1f;
        newObject.GetComponent<BoundsControl>().ScaleHandlesConfig.HandleSize = 0.1f;
        newObject.GetComponent<BoundsControl>().RotationHandlesConfig.HandleSize = 0.05f;
        spawnedWindows.Add(newObject);
    }
}
