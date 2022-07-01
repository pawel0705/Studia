using System.Globalization;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{
    [SerializeField] private TMP_Text timerText;
    [SerializeField] private SO_GameController controller;
    [SerializeField] private Button restartButton;

    private float startTime;
    private float currentTime;
    private string minutes;
    private string seconds;

    
    void Start()
    {
        Time.timeScale = 1;
        startTime = Time.time;
        restartButton.gameObject.SetActive(false);
    }

    void Update()
    {
        currentTime = Time.time - startTime;
        UpdateText();

        if (controller.isGameOver)
        {
            Time.timeScale = 0;
            restartButton.gameObject.SetActive(true);
        }
    }
    
    public void RestartButton()
    {
        SceneManager.LoadScene(sceneBuildIndex: 0);
        
    }
    private void UpdateText()
    {
        minutes = ((int) currentTime / 60).ToString();
        seconds = (currentTime % 60).ToString("f2");
        timerText.text = "Time: " + minutes + ":" + seconds;
    }
}
