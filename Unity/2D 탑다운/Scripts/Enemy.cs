using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour, ITraceable, IDamageable
{
    public float moveSpeed = 5.0f;

    [SerializeField]
    bool isTrace = false;
    public GameObject target;

    Animator anim;
    SpriteRenderer sr;
    private void Start()
    {
        anim = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
    }
    private void Update()
    {
        Trace();
    }
    public void Hit()
    {
    }

    public void Trace()
    {
        if (!isTrace) return;

        Vector2 dirVec = (target.transform.position - transform.position).normalized;
        anim.SetFloat("hSpeed", dirVec.x);
        anim.SetFloat("vSpeed", dirVec.y);

        if (dirVec.x > 0)
        {
            sr.flipX = false;
        }
        else if (dirVec.x < 0)
        {
            sr.flipX = true;
        }
        if (dirVec.magnitude > 0.1f)
        {
            int dir = 0;
            if (Mathf.Abs(dirVec.y) < Mathf.Abs(dirVec.x))
            {
                dir = dirVec.x > 0 ? 3 : 2;
                anim.SetFloat("PrevDir", dir);
            }
            else
            {
                dir = dirVec.y > 0 ? 0 : 1;
                anim.SetFloat("PrevDir", dir);
            }
        }

        transform.Translate(dirVec * moveSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.tag == "Player")
        {
            target = other.gameObject;
            isTrace = true;
            anim.SetBool("IsTrace", isTrace);
        }
    }
    private void OnTriggerExit2D(Collider2D other)
    {
        if(other.tag == "Player")
        {
            target = null;
            isTrace = false;
            anim.SetBool("IsTrace", isTrace);
        }
    }
}
