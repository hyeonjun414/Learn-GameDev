using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Background : MonoBehaviour
{
    public BoxCollider2D bc;

    void Update()
    {
        RePosition();
    }
    void RePosition()
    { 
       if(transform.position.x <= -bc.size.x)
            transform.Translate(bc.size.x * 2, 0,0);
    }
}
