using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class PopUpText : MonoBehaviour
{
    private TMP_Text text;
    private void Awake()
    {
        text = GetComponentInChildren<TMP_Text>();
        text.gameObject.SetActive(false);
    }

    private void OnTriggerEnter(Collider other)
    {
        text.gameObject.SetActive(true);
    }
}
