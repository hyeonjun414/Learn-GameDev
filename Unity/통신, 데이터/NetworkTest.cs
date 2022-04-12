using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkTest : MonoBehaviour
{

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(WWWGETTest());
        StartCoroutine(UnityWebRequestGetTest());
    }
    IEnumerator WWWGETTest()
    {
        string apiKey = "u3lm5PR8KkOu9isHGt6di9eQ2jHLg3R7";
        string url = "https://api.neople.co.kr/df/servers?apikey=" + apiKey;

        WWW www = new WWW(url);

        yield return www;

        if(www.error == null)
        {
            Debug.Log(www.text);
        }
        else
        {
            Debug.Log("error");
        }
    }
    IEnumerator UnityWebRequestGetTest()
    {
        string jobId = "41f1cdc2ff58bb5fdc287be0db2a8df3";
        string jobGrowId = "37495b941da3b1661bc900e68ef3b2c6";

        string apiKey = "u3lm5PR8KkOu9isHGt6di9eQ2jHLg3R7";
        string url = $"https://api.neople.co.kr/df/skills/{jobId}?jobGrowId={jobGrowId}&apikey=" + apiKey;

        UnityWebRequest www = UnityWebRequest.Get(url);

        yield return www.SendWebRequest();

        if(www.error == null)
        {
            Debug.Log(www.downloadHandler.text);
        }
        else
        {
            Debug.Log("errer");
        }
    }

}
