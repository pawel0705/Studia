using UnityEngine;

public class Trigger : MonoBehaviour
{
    public GameObject ball;
    private void OnTriggerEnter(Collider other)
    {
        //cos z wygrana
        //pewnie znowu reset kuli, ale z jakims napisam, ze "hej, wygrana!"
        //ten reset to powtórka z resetu przy zderzeniu z lancuchową kula
        //pomysle jeszcze jak to sprytnie zrobic, zeby nie duplokowac po prostu
    }
}
