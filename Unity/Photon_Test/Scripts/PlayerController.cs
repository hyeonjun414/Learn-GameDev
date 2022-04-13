using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

public class PlayerController : MonoBehaviour
{
    public PhotonView pv;
    public SpriteRenderer sr;
    void Update()
    {
        if(pv.IsMine)
        {
            MoveFunc();
        }
    }
    void MoveFunc()
    {
        float x = Input.GetAxisRaw("Horizontal");
        float y = Input.GetAxisRaw("Vertical");

        Vector3 move = new Vector3(x, y, 0);
        transform.Translate(move*10*Time.deltaTime);

        if (x != 0) pv.RPC("FlipXRPC", RpcTarget.AllBuffered, x);

    }

    [PunRPC]
    void FlipXRPC(float axis)
    {
        // 왼쪽이면 True, 아니면 false
        sr.flipX = axis == -1;
    }
}
