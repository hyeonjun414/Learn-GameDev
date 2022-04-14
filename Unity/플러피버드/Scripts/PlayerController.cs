using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
public class PlayerController : MonoBehaviour
{
    public UnityAction OnScore;
    public UnityAction OnDead;

    public float jumpPower = 1f;
    public float maxSpeed = 5f;

    Rigidbody2D rb;
    

    public GameObject animObject;

    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
    }


    private void Update()
    {
        Jump();
        
    }
    void Jump()
    {
        if(Input.GetButtonDown("Jump"))
        {
            rb.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
            
        }
        if(rb.velocity.y > maxSpeed)
            rb.velocity = new Vector2(0, maxSpeed);
        else if(rb.velocity.y < -maxSpeed)
            rb.velocity = new Vector2(0, -maxSpeed);
        animObject.transform.rotation = Quaternion.Euler(0, 0, rb.velocity.y*5);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        OnDead?.Invoke();
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("ScoreArea"))
            OnScore?.Invoke();
    }
}
