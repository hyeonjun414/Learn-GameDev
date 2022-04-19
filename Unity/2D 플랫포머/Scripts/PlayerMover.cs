using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMover : MonoBehaviour
{
    private Rigidbody2D rb;
    private Animator anim;
    private SpriteRenderer sr;
    private CapsuleCollider2D coll;

    public float moveSpeed = 5.0f;
    public float jumpPower = 5.0f;

    bool IsCrouch
    {
        get
        {
            return anim.GetBool("IsCrouch");
        }
        set
        {
            anim.SetBool("IsCrouch", value);
        }
    }
    bool IsGround
    {
        get
        {
            return anim.GetBool("IsGround");
        }
        set
        {
            anim.SetBool("IsGround", value);
        }
    }

    float moveX;
    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
        coll = GetComponent<CapsuleCollider2D>();
    }
    private void Update()
    {
        Move();
        Jump();
        Crouch();
    }
    private void FixedUpdate()
    {
        Vector2 startVec = new Vector2(transform.position.x, transform.position.y);
        RaycastHit2D hit = Physics2D.Raycast(startVec, Vector2.down, 1.5f, LayerMask.GetMask("Ground"));
        Debug.DrawRay(startVec, Vector2.down*1.5f, new Color(0, 0, 1));

        if(null != hit.collider)
        {
            IsGround = true;
        }
        else
        {
            IsGround = false;
        }
    }
    private void Move()
    {
        

        moveX = Input.GetAxisRaw("Horizontal");

        if (IsCrouch) return;

        anim.SetInteger("AxisX", (int)moveX);
        if(moveX < 0)
        {
            sr.flipX = true;
        }
        else if (moveX > 0)
        {
            sr.flipX = false;
        }
        rb.transform.Translate(Vector2.right * moveX * moveSpeed * Time.deltaTime);
    }
    private void Jump()
    {
        bool jump = Input.GetButtonDown("Jump");
        if (jump && IsGround)
        {
            rb.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
        }

        if(!IsGround)
        {
            anim.SetInteger("AxisY", (int)rb.velocity.y);
        }
    }
    private void Crouch()
    {
        if(!IsGround && Input.GetAxisRaw("Vertical") < 0)
        {
            IsCrouch = true;
        }
        else
        {
            IsCrouch = false;
        }
    }
    private void Attack(IStampable monster)
    {
        rb.AddForce(Vector2.up * jumpPower/2, ForceMode2D.Impulse);
        monster.Stamp();
    }
    private void OnCollisionEnter2D(Collision2D other)
    {
        if(other.gameObject.tag == "Monster")
        {
            if(transform.position.y > other.transform.position.y)
            {
                IStampable monster = other.gameObject.GetComponent<IStampable>();
                if(monster != null)
                    Attack(monster);
            }
        }
    }



}
