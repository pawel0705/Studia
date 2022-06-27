using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestShaders : MonoBehaviour
{
    public enum ShaderTypes
    {
        HeartZoom,
        Circle,
        Square,
        CircleZoom
    }

    public ShaderTypes shaderType = ShaderTypes.Circle;
    public float rollSpeed = 10.0f;
    public float shaderWidth = 0.03f;

    private Renderer renderer;
    private bool canChange = false;


    // Start is called before the first frame update
    void Start()
    {
        renderer = GetComponent<Renderer>() as Renderer;
        if (!renderer)
        {
            Debug.Log("No renderer");
        }

        string shaderName;

        switch (shaderType)
        {
            case ShaderTypes.Circle:
                shaderName = "Custom/CircleShader";
                break;
            case ShaderTypes.CircleZoom:
                shaderName = "Custom/ZoomShader";
                break;
            case ShaderTypes.Square:
                shaderName = "Custom/SquareShader";
                break;
            case ShaderTypes.HeartZoom:
                shaderName = "Custom/HeartZoomShader";
                break;
            default:
                shaderName = "Custom/HeartZoomShader";
                break;

        }

        renderer.material.shader = Shader.Find(shaderName);
        renderer.sharedMaterial.SetFloat("CX", 0);
        renderer.sharedMaterial.SetFloat("CY", 0);
        renderer.sharedMaterial.SetFloat("R", 0.2f);
        renderer.sharedMaterial.SetFloat("W", shaderWidth);

        float aspect = transform.localScale.x / transform.localScale.y;
        renderer.sharedMaterial.SetFloat("A", aspect);
    }

    private void OnMouseDown()
    {
        canChange = true;
    }

    private void OnMouseUp()
    {
        canChange = false;
    }

    private void OnMouseOver()
    {
        if (canChange)
        {
            MousePositionOnScreen();
            MouseScrollService();
        }
    }

    private void MousePositionOnScreen()
    {
        RaycastHit hit;
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        if (Physics.Raycast(ray, out hit))
        {
            if (hit.collider.gameObject == this.gameObject)
            {
                renderer.sharedMaterial.SetFloat("CX", hit.textureCoord.x);
                renderer.sharedMaterial.SetFloat("CY", hit.textureCoord.y);
            }
        }
    }

    private void MouseScrollService()
    {
        //Zooming
        if (shaderType == ShaderTypes.CircleZoom || shaderType == ShaderTypes.HeartZoom)
        {
            if (Input.GetAxis("Mouse ScrollWheel") > 0)
            {
                float Z = renderer.sharedMaterial.GetFloat("Z");
                Z += rollSpeed * Time.deltaTime;
                renderer.sharedMaterial.SetFloat("Z", Z);
            }
            else if (Input.GetAxis("Mouse ScrollWheel") < 0)
            {
                float Z = renderer.sharedMaterial.GetFloat("Z");
                Z -= rollSpeed * Time.deltaTime;
                renderer.sharedMaterial.SetFloat("Z", Z);
            }
        }
        //Changing size
        else
        {
            if (Input.GetAxis("Mouse ScrollWheel") > 0)
            {
                float R = renderer.sharedMaterial.GetFloat("R");
                R += rollSpeed * Time.deltaTime;
                renderer.sharedMaterial.SetFloat("R", R);
            }
            else if (Input.GetAxis("Mouse ScrollWheel") < 0)
            {
                float R = renderer.sharedMaterial.GetFloat("R");
                R -= rollSpeed * Time.deltaTime;
                renderer.sharedMaterial.SetFloat("R", R);
            }
        }
    }
}
