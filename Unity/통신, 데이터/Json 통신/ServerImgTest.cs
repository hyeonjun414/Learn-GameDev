using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;

public class ServerImgTest : MonoBehaviour
{
    public RawImage img;
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(TextureLoad());
    }

    IEnumerator TextureLoad()
    {
        string url = "https://t1.daumcdn.net/cfile/tistory/24283C3858F778CA2E";
        UnityWebRequest www = UnityWebRequestTexture.GetTexture(url);
        
        // 올때까지 대기
        yield return www.SendWebRequest();

        if(www.error == null)
        {
            // 내려받은 리퀘스트를 텍스쳐로 변환한뒤에 받아온 이미지를 지정해준다.
            img.texture = ((DownloadHandlerTexture)www.downloadHandler).texture;
        }
        else
        {
            Debug.LogError(www.error);
        }
    }
}
