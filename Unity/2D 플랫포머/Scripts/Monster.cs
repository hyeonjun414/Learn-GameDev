using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IStampable
{
    void Stamp();
}

public class Monster : MonoBehaviour, IStampable
{
    public enum State
    {
        Idle,
        Jump,
        Move,
    }
    public enum MonsterType
    {
        Frog,
        Opossum,
    }
    Animator anim;
    Rigidbody2D rb;
    SpriteRenderer sr;

    public float jumpPower = 5.0f;
    public float moveSpeed = 5.0f;

    public bool isRight;
    public State state;
    public MonsterType type;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
        sr = GetComponent<SpriteRenderer>();

        if (type == MonsterType.Opossum)
        {
            anim.SetBool("IsRight", isRight);
            sr.flipX = isRight;
        }

    }
    private void FixedUpdate()
    {
        //anim.SetFloat("vSpeed", rb.velocity.y);
        if(type == MonsterType.Opossum)
        {
            if (state == State.Move)
            {
                Vector2 startVec = new Vector2(transform.position.x, transform.position.y);
                RaycastHit2D hit = Physics2D.Raycast(startVec, isRight ? Vector2.right : Vector2.left, 1.5f, LayerMask.GetMask("Ground"));
                Debug.DrawRay(startVec, isRight ? Vector2.right : Vector2.left * 1.5f, new Color(0, 0, 1));
                if (hit.collider != null)
                {
                    isRight = !isRight;
                    anim.SetBool("IsRight", isRight);
                    sr.flipX = isRight;
                }

                RaycastHit2D hit2 = Physics2D.Raycast(startVec, new Vector2(isRight ? 1 : -1, -1), 1.5f, LayerMask.GetMask("Ground"));
                Debug.DrawRay(startVec, new Vector2(isRight ? 1 : -1, -1) * 1.5f, new Color(0, 1, 0));
                if (hit2.collider == null)
                {
                    isRight = !isRight;
                    anim.SetBool("IsRight", isRight);
                    sr.flipX = isRight;
                }
            }
        }
        


    }
    public void Idle()
    {
        state = State.Idle;
        StartCoroutine(IdlePattern());
    }
    public void Jump()
    {
        state = State.Jump;
        StartCoroutine(JumpPattern());
    }
    public void Move()
    {
        state = State.Move;
        StopCoroutine("MovePattern");
        StartCoroutine("MovePattern");
    }
    IEnumerator IdlePattern()
    {
        yield return new WaitForSeconds(3.0f);
        anim.SetBool("IsJump", true);
        yield return null;
    }
    IEnumerator JumpPattern()
    {
        float dir = Random.Range(-1, 2);
        sr.flipX = dir > 0;
        rb.AddForce(new Vector2(dir >0?1:-1, 1) * jumpPower, ForceMode2D.Impulse);
        yield return new WaitForSeconds(1.0f);
        anim.SetBool("IsJump", false);
        yield return null;
    }
    IEnumerator MovePattern()
    {
        while(true)
        {
            transform.Translate((isRight? Vector2.right : Vector2.left)*moveSpeed*Time.deltaTime);
            yield return null;
        }
        
    }
    public void Die()
    {
        anim.SetTrigger("IsDead");
        moveSpeed = 0f;
        jumpPower = 0f;
    }
    public void OnDieEffect()
    {
        Destroy(gameObject);
    }

    public void Stamp()
    {
        Die();
    }
}
