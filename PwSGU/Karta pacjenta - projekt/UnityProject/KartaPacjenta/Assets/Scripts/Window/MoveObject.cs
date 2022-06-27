using System.Collections;

using System.Collections.Generic;

using UnityEngine;



public class MoveObject : MonoBehaviour

{
    private Vector3 mOffset;
    private float mZCoord;
    private float scrollPosition=0.0f;


    void OnMouseDown()

    {
        mZCoord = Camera.main.WorldToScreenPoint(gameObject.transform.position).z;
        // Store offset = gameobject world pos - mouse world pos
        mOffset = gameObject.transform.position - GetMouseAsWorldPoint();
    }



    private Vector3 GetMouseAsWorldPoint()

    {
        // Pixel coordinates of mouse (x,y)
        Vector3 mousePoint = Input.mousePosition;
        scrollPosition += Input.GetAxis("Mouse ScrollWheel");
        // z coordinate of game object on screen
        mousePoint.z = mZCoord+ scrollPosition;
        // Convert it to world points
        return Camera.main.ScreenToWorldPoint(mousePoint);
    }



    void OnMouseDrag()
    { 
        transform.position = GetMouseAsWorldPoint() + mOffset;
    }
}