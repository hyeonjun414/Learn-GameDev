using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMover : MonoBehaviour
{
    private Rigidbody2D rb;
    private Animator anim;
    private SpriteRenderer sr;

    public float moveSpeed = 5.0f;
    public float jumpPower = 5.0f;

    bool IsGround = true;
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
    bool IsJump
    {
        get
        {
            return anim.GetBool("IsJump");
        }
        set
        {
            anim.SetBool("IsJump", value);
        }
    }

    float moveX;
    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
    }
    private void Update()
    {
        Move();
        Jump();
        Crouch();
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
        if (jump && !IsJump)
        {
            rb.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
            IsJump = true;
        }

        if(IsJump)
        {
            anim.SetInteger("AxisY", (int)rb.velocity.y);
        }
    }
    private void Crouch()
    {
        if(IsGround && Input.GetAxisRaw("Vertical") < 0)
        {
            IsCrouch = true;
        }
        else
        {
            IsCrouch = false;
        }
    }
   

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.collider.tag == "Ground")
        {
            IsJump = false;
        }
    }
    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.collider.tag == "Ground")
        {
            IsJump = true;
        }
    }

}
