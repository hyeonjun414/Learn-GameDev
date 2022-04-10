using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 코드를 Json으로 변경하는 법
// 1. 데이터(코드 = 클래스)를 만들어야함 -> 저장할 데이터 생성
// 2. 그 데이터를 Json으로 변환
// 원래 코드로 변경하는 법
// 1. 

class Data
{
    public string  nickName;
    public int     level;
    public int     gold;
    public bool    skiil;
    // 여러가지 정보
}

public class JsonTest : MonoBehaviour
{
    Data player = new Data();

    // Start is called before the first frame update
    void Start()
    {
        player.nickName = "장현준";
        player.level = 30;
        player.gold = 100;
        player.skiil = false;

        // Json으로 변환
        string jsonData = JsonUtility.ToJson(player);

        print(jsonData);

        Data player2 = JsonUtility.FromJson<Data>(jsonData);

        print(player2.nickName);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
