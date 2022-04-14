using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine.SceneManagement;

public class MyManager : MonoBehaviour
{
    public int score = 0;
    public Text scoreText;
    public GameObject GameoverUI;
    public GameObject ReadyUI;

    bool IsPlay = false;

    public PlayerController player;
    private void Start()
    {
        player.OnDead += GameOver;
        player.OnScore += AddScore;
        Time.timeScale = 0;
    }
    private void Update()
    {
        if (!IsPlay && Input.GetButtonDown("Jump"))
            GameStart();
            
    }
    public void AddScore()
    {
        score++;
        scoreText.text = $"SCORE : {score}";
    }
    public void ReStart()
    {
        SceneManager.LoadScene("Main", LoadSceneMode.Single);
    }
    public void GameOver()
    {
        GameoverUI.SetActive(true);
        Time.timeScale = 0;
    }
    public void GameStart()
    {
        IsPlay = true;
        Time.timeScale = 1;
        ReadyUI.SetActive(false);
    }

}
