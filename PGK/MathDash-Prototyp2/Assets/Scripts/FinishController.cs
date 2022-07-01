using UnityEngine;

public class FinishController : MonoBehaviour
{
    [SerializeField]
    private SO_GameController gameController;

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log(other.gameObject.name);

        if (other.gameObject.name.Contains("Hook"))
        {
            return;
        }

        if (gameObject.CompareTag("Finish"))
        {
            Debug.Log("wygranko");
        }

        EndGame();
    }

    private void EndGame()
    {
        gameController.isGameOver = true;
    }
}