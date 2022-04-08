using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.UI;

// Json 쓴다고 하면 Serializable은 무조건 사용한다는 생각
[System.Serializable]
public class ServerInfo
{
    public string serverId;
    public string serverName;
}
[System.Serializable]
public class ServerRoot
{
    public List<ServerInfo> rows;
}

[System.Serializable]
public class CharacterInfo
{
    public string serverId;
    public string characterId;
    public string characterName;
    public int level;
    public string jobId;
    public string jobGrowId;
    public string jobName;
    public string jobGrowName;
}

[System.Serializable]
public class CharacterRoot
{
    public List<CharacterInfo> rows;
}




public class Server : MonoBehaviour
{
    public string apiKey = "u3lm5PR8KkOu9isHGt6di9eQ2jHLg3R7";
    public Dropdown serverList;
    public Text selectedServerName;
    string serverId = "";
    string characterName = "";
    string characterId = "";
    public InputField inputText;
    public RawImage img;

    ServerRoot serverData = new ServerRoot();
    CharacterRoot characterData = new CharacterRoot();

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(ServerRequest());
    }

    public void CharacterSearch()
    {
        string temp = selectedServerName.text;
        // 람다식 활용
        serverId =  serverData.rows.Find(x => x.serverName == temp).serverId;
        characterName = UnityWebRequest.EscapeURL(inputText.text);

        StartCoroutine(CharacterRequest(serverId, characterName));
        

    }

    IEnumerator ServerRequest()
    {
        string url = $"https://api.neople.co.kr/df/servers?apikey={apiKey}";
        UnityWebRequest www = UnityWebRequest.Get(url);

        yield return www.SendWebRequest();

        if(www.error == null)
        {
            Debug.Log(www.downloadHandler.text);

            serverData = JsonUtility.FromJson<ServerRoot>(www.downloadHandler.text);

            foreach(var item in serverData.rows)
            {
                Dropdown.OptionData option = new Dropdown.OptionData();
                option.text = item.serverName;
                serverList.options.Add(option);
            }
        }
        else
        {
            Debug.Log("ERROR");
        }
    }

    IEnumerator CharacterRequest(string serverId, string characterName)
    {
        string url = $"https://api.neople.co.kr/df/servers/{serverId}/characters?characterName={characterName}&apikey={apiKey}";
        UnityWebRequest www = UnityWebRequest.Get(url);

        yield return www.SendWebRequest();

        if (www.error == null)
        {
            print(www.downloadHandler.text);
            characterData = JsonUtility.FromJson<CharacterRoot>(www.downloadHandler.text);
            characterId = characterData.rows.Find(x => x.characterName == inputText.text).characterId;

            print(characterId);
            StartCoroutine(CharacterImageRequest(serverId, characterId));
        }
        else
        {
            Debug.Log("ERROR");
        }

    }

    IEnumerator CharacterImageRequest(string serverId, string characterId)
    {
        string url = $"https://img-api.neople.co.kr/df/servers/{serverId}/characters/{characterId}?zoom=3";
        UnityWebRequest www = UnityWebRequestTexture.GetTexture(url);

        yield return www.SendWebRequest();

        if (www.error == null)
        {
            img.texture = ((DownloadHandlerTexture)www.downloadHandler).texture;
        }
        else
        {
            Debug.Log("ERROR");
        }
    }

}
