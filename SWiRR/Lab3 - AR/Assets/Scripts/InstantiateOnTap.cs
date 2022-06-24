using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;

public class InstantiateOnTap : MonoBehaviour
{
    [SerializeField] GameObject prefab;

    ARRaycastManager raycastManager;

    static List<ARRaycastHit> hits = new List<ARRaycastHit>();

    void Awake() {
        raycastManager = GetComponent<ARRaycastManager>();
    }

    void Update()
    {
        if(Input.touchCount > 0)
        {
            Vector2 tap = Input.GetTouch(0).position;

            if(raycastManager.Raycast(tap, hits, UnityEngine.XR.ARSubsystems.TrackableType.PlaneWithinPolygon))
            {
                Vector3 pos = hits[0].pose.position;
                Instantiate(prefab, pos, Quaternion.identity);
            }
        }
    }
}
