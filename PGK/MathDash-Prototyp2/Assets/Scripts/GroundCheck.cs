using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GroundCheck : MonoBehaviour
{
    public bool IsOnGround;
    // Start is called before the first frame update
    private void OnTriggerEnter(Collider other)
    {
        IsOnGround = true;
    }
}
