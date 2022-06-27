using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using UnityEngine;

public class FaceDetector : MonoBehaviour
{
    private WebCamTexture webCamTexture; // video renderer texture
    private Renderer rendererComponent; // renderer component of screen
    private Texture2D t; // texture from camera view

    [DllImport("OCVWrapper", EntryPoint = "detectFace", CallingConvention = CallingConvention.StdCall)]
    public static extern void detectFace(long length, int width, int height, byte[] data, out float tlx, out float tly, out float brx, out float bry);  // deklaracja funkcji

    [DllImport("OCVWrapper", EntryPoint = "loadClassifier", CallingConvention = CallingConvention.StdCall)]
    public static extern void loadClassifier(string fileName);

    // Start is called before the first frame update
    void Start()
    {
        loadClassifier("classifier.xml"); // load qr classifier
        initWebCamTexture(); // initialize web camera
    }

    // Update is called once per frame
    void Update()
    {
        if (webCamTexture.isPlaying) // Classify object if camera is playing
        {
            Classify();
        }
    }

    public void StartStreaming() => webCamTexture.Play(); // start camera
    public void Pause() => webCamTexture.Pause(); // pause camera

    /*
     * Change classifier for detecting faces.
    */
    public void ChangeClassifierFace()
    {
        loadClassifier("haarcascade_frontalface_default.xml");
    }

    /*
     * Change classifier for detecting QR codes.
    */
    public void ChangeClassifierQR()
    {
        loadClassifier("classifier.xml");
    }

    /*
     * Initialize Web Cam Texture.
    */
    private void initWebCamTexture()
    {
        webCamTexture = new WebCamTexture();
        rendererComponent = GetComponent<Renderer>();
    }

    /*
     * Classify image and draw red box.
     */
    private void Classify()
    {
        rendererComponent.material.mainTexture = webCamTexture; // change screen texture to camera view
        t = new Texture2D(rendererComponent.material.mainTexture.width, rendererComponent.material.mainTexture.height, TextureFormat.RGB24, false); // initialize 2D texture

        t.SetPixels((rendererComponent.material.mainTexture as WebCamTexture).GetPixels()); // set pixels from camera view
        t.Apply(); // apply set pixels
        byte[] bytes = t.GetRawTextureData(); // get pixel data from texture

        float tlx = 0, tly = 0, brx = 0, bry = 0; // red box coordinates
        int frameWidth = 10; // size of red box frame

        detectFace(bytes.Length, t.width, t.height, bytes, out tlx, out tly, out brx, out bry); // detect object

        // draw red box if object is detected
        if (tlx != 0 && tly != 0)
        {
            for (int x = (int)tlx - frameWidth; x <= (int)tlx + brx + frameWidth; x++)
            {
                for (int y = (int)tly - frameWidth; y <= (int)tly + bry + frameWidth; y++)
                {
                    if (x > tlx && x < tlx + brx && y > tly && y < tly + bry) // dont fill middle of red box
                    {
                        continue;
                    }
                    // fix x and y position and set red box pixels on screen texture
                    t.SetPixel(Math.Abs(rendererComponent.material.mainTexture.width - x), Math.Abs(rendererComponent.material.mainTexture.height - y), UnityEngine.Color.red);
                }
            }
            t.Apply(); // apply set pixels
        }

        rendererComponent.material.mainTexture = t; // set edited texture as screen texture
    }
}
