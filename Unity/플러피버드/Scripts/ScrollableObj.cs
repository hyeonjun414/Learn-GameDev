using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScrollableObj : MonoBehaviour
{
    public float scrollSpeed = 5f;

    // Update is called once per frame
    void Update()
    {
        transform.Translate(-scrollSpeed*Time.deltaTime,0,0);
    }
}
