using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenInputManager : MonoBehaviour
{

    [SerializeField]
    private FaceDetector faceDetector; // camera screen


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        ReadKey(); // key input
    }

    void ReadKey()
    {
        if (Input.GetKey(KeyCode.Z)) // start camera
        {
            faceDetector.StartStreaming();
        }

        if (Input.GetKey(KeyCode.X)) // pause camera
        {
            faceDetector.Pause();
        }

        if (Input.GetKey(KeyCode.C)) // change classifier to face detection
        {
            faceDetector.ChangeClassifierFace();
        }

        if (Input.GetKey(KeyCode.V)) // change classifier to qr code detection
        {
            faceDetector.ChangeClassifierQR();
        }
    }
}
