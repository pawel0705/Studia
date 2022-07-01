using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting.Antlr3.Runtime.Tree;
using UnityEngine;

public class GateController : MonoBehaviour
{
    [SerializeField]
    private Gate[] gates;

    [SerializeField]
    private TMP_Text[] texts;

    private int id;
  

    private string[,] math;
    void Start()
    {
        math = new string[3, 4]
        {
            {"2+2","4", "5", "2"},
            {"3+5", "8", "4", "9"}, 
            {"7-2", "5", "6", "4"}
        };
        
        gates = GetComponentsInChildren<Gate>();
        GenerateMath();
    }

    private void GenerateMath()
    {
        id = Random.Range(0, 3);
        texts[0].text = math[id, 0];

        SetAnswers();
    }

    private void SetAnswers()
    {
        int random = Random.Range(0, 2);
        gates[random].IsCorrect = true;
        texts[random + 1].text = math[id, 1];

        if (random == 0)
        {
            gates[2].IsCorrect = false;
            gates[1].IsCorrect = false;
            texts[2].text = math[id, 2];
            texts[3].text = math[id, 3];
        }
        else if (random == 1)
        {
            gates[2].IsCorrect = false;
            gates[0].IsCorrect = false;
            texts[1].text = math[id, 2];
            texts[3].text = math[id, 3];
        }
        else if (random == 2)
        {
            gates[0].IsCorrect = false;
            gates[1].IsCorrect = false;
            texts[2].text = math[id, 2];
            texts[1].text = math[id, 3];
        }
    }
}
