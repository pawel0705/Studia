using Microsoft.MixedReality.Toolkit.Input;
using UnityEngine;

public class MoveObjectWithPointer : MonoBehaviour, IMixedRealityPointerHandler
{
    private Vector3 pointerStartPos;
    public float speed = 4.0f;

    //Methods below are IMixedRealityPointerHandler interface implementation

    //this method is invoked when pointer is down/held on the object
    public void OnPointerDown(MixedRealityPointerEventData eventData)
    {
        //starting position of the pointer is saved as private data
        pointerStartPos = eventData.Pointer.Position;
    }

    //this method is invoked when pointer (is that is held on the object) is moved
    public void OnPointerDragged(MixedRealityPointerEventData eventData)
    {
        //move the object by the diffrence of pointer start and end position
        transform.position += (eventData.Pointer.Position - pointerStartPos) * speed;
        pointerStartPos = eventData.Pointer.Position;
    }

    //this method is invoked when pointer is released
    public void OnPointerUp(MixedRealityPointerEventData eventData)
    { }

    //this method informs that user clicked object with the pointer
    public void OnPointerClicked(MixedRealityPointerEventData eventData)
    { }
}
