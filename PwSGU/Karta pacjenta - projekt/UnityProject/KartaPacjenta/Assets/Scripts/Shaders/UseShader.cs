using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UseShader : MonoBehaviour
{
    private const float MAX_ZOOM = 10; // max value of zoom
    private const float MIN_ZOOM = 1; // min value of zoom
    
    private Renderer renderer; // object renderer
    private bool canChange = false; // can change flag
    private float rollSpeed = 10.0f; // speed of roll


    // Start is called before the first frame update
    void Start()
    {
        renderer = GetComponent<Renderer>() as Renderer; // get renderer component
        if (!renderer)
        {
            Debug.Log("No renderer");
        }

        string shaderName = "Custom/HeartZoom"; // name of shader

        renderer.material.shader = Shader.Find(shaderName); // find shader by name
        renderer.sharedMaterial.SetFloat("CX", 0);
        renderer.sharedMaterial.SetFloat("CY", 0);
        renderer.sharedMaterial.SetFloat("R", 0.2f);
        renderer.sharedMaterial.SetFloat("W", 0.03f);
        renderer.sharedMaterial.SetFloat("Z", MIN_ZOOM);


        float aspect = transform.localScale.x / transform.localScale.y; // set new aspect
        renderer.sharedMaterial.SetFloat("A", aspect);
    }

    private void OnMouseDown() // set change flag on true
    {
        canChange = true;
    }

    private void OnMouseUp() // set change flag on false
    {
        canChange = false;
    }

    private void OnMouseOver()
    {
        if (canChange)
        {
            MousePositionOnScreen(); // handle mouse position
            MouseScrollService(); // handle mouse scrool
        }
    }

    /*
    * Change shader position.
    */
    private void MousePositionOnScreen()
    {
        RaycastHit hit;
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        if(Physics.Raycast(ray, out hit)) // check if mouse is on object and set position coords
        {
            if(hit.collider.gameObject == this.gameObject)
            {
                renderer.sharedMaterial.SetFloat("CX", hit.textureCoord.x);
                renderer.sharedMaterial.SetFloat("CY", hit.textureCoord.y);
            }
        }
    }

    /*
     * Change zoom.
     */
    private void MouseScrollService()
    {
        if (Input.GetAxis("Mouse ScrollWheel") > 0) // zoom up
        {
            float Z = renderer.sharedMaterial.GetFloat("Z");
            Z += rollSpeed * Time.deltaTime;

            if (Z > MAX_ZOOM)
            {
                Z = MAX_ZOOM;
            }
            else
            {
                renderer.sharedMaterial.SetFloat("Z", Z);
            }
        }
        else if (Input.GetAxis("Mouse ScrollWheel") < 0) // zoom down
        {
            float Z = renderer.sharedMaterial.GetFloat("Z");
            Z -= rollSpeed * Time.deltaTime;

            if (Z < MIN_ZOOM)
            {
                Z = MIN_ZOOM;
            }
            else
            {
                renderer.sharedMaterial.SetFloat("Z", Z);
            }

        }
    }
}