using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    private static GameManager _instance;
    public static GameManager Instance
    {
        get 
        { 
            if(_instance == null )
            {
                _instance = FindObjectOfType<GameManager>();
            }
            return _instance;
        }
    }

    public int score = 0;
    public Text scoreText;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void AddScore(int value)
    {
        score += value;
        scoreText.text = $"Score : {score}";
    }
}
