using UnityEngine;

public class TrapManager : MonoBehaviour
{
    private Vector3 startPosition;
    private Quaternion startRotation;

    private void Awake()
    {
        startPosition = transform.position;
        startRotation = transform.rotation;
        
    }

    private void OnEnable()
    {
        transform.position = startPosition;
        transform.rotation = transform.rotation;
    }
}
