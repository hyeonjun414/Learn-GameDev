using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMover : MonoBehaviour
{

    public float moveSpeed = 1.0f;

    float vSpeed;
    float hSpeed;

    Animator anim;
    SpriteRenderer sr;

    bool isActing = false;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
    }
    private void Update()
    {
        Move();
        Action();
    }
    private void Move()
    {
        if (isActing)
        {
            anim.SetBool("IsMove", false);
            return;
        }


        vSpeed = Input.GetAxis("Vertical");
        hSpeed = Input.GetAxis("Horizontal");
        anim.SetFloat("vSpeed", vSpeed);
        anim.SetFloat("hSpeed", hSpeed);

        Vector2 moveVec = new Vector2(hSpeed, vSpeed);
        anim.SetBool("IsMove", moveVec.sqrMagnitude > 0.01f);

        if(hSpeed > 0)
        {
            sr.flipX = false;
        }
        else if (hSpeed < 0)
        {
            sr.flipX= true;
        }
        if(moveVec.magnitude > 0.1f)
        {
            int dir = 0;
            if (Mathf.Abs(vSpeed) < Mathf.Abs(hSpeed))
            {
                dir = hSpeed > 0 ? 3 : 2;
                anim.SetFloat("PrevDir", dir);
            }
            else
            {
                dir = vSpeed > 0 ? 0 : 1;
                anim.SetFloat("PrevDir", dir);
            }
        }

        
        transform.Translate(new Vector2(hSpeed, vSpeed) * moveSpeed * Time.deltaTime);
    }

    void Action()
    {
        if(Input.GetButtonDown("Interaction"))
        {
            Vector2 dirVec = Vector2.zero;
            float dir = anim.GetFloat("PrevDir");
            switch (dir)
            {
                case 0: dirVec = Vector2.up; break;
                case 1: dirVec = Vector2.down; break;
                case 2: dirVec = Vector2.left; break;
                case 3: dirVec = Vector2.right; break;
            }
            RaycastHit2D hit = Physics2D.Raycast(transform.position, dirVec, 1.5f, LayerMask.GetMask("Interactable"));
            Debug.DrawRay(transform.position, dirVec * 1.5f, Color.yellow, 0.5f);
            if(null != hit.collider)
            {
                IInteractable target = hit.collider.gameObject.GetComponent<IInteractable>();
                isActing = target.Interaction();
            }

        }
    }
}
