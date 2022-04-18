using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class background : MonoBehaviour
{
    public GameObject target;
    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(Mathf.Lerp(transform.position.x, target.transform.position.x, Time.deltaTime),
                                        0, 0);
    }
}
