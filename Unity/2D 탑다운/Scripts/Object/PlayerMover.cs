using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMover : MonoBehaviour, IAttackable
{

    public float moveSpeed = 1.0f;
    public float ShotPower = 100f;
    public int arrowDamage = 5;

    float vSpeed;
    float hSpeed;

    Animator anim;
    SpriteRenderer sr;
    
    Collider2D coll;

    bool isActing = false;
    bool isAttack = false;

    public Projectile Arrow;
    public Transform shotPoint;

    private void Awake()
    {
        anim = GetComponent<Animator>();
        sr = GetComponent<SpriteRenderer>();
        coll = GetComponent<Collider2D>();
    }
    private void Update()
    {
        Move();
        Action();
        Attack();
        DropItem();
    }
    private void Move()
    {
        if (isActing || isAttack)
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


        if (hSpeed > 0)
        {
            sr.flipX = false;
        }
        else if (hSpeed < 0)
        {
            sr.flipX= true;
        }
        if(moveVec.magnitude != 0)
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

    public void Attack()
    {
        if (isActing || isAttack) return;

        if(Input.GetButtonDown("Jump"))
        {
            Vector2 dirVec = Vector2.zero;
            float dir = anim.GetFloat("PrevDir");
            float rotAngle = 0;
            switch (dir)
            {
                case 0: dirVec = Vector2.up; rotAngle = 0;      break;
                case 1: dirVec = Vector2.down; rotAngle = 180;  break;
                case 2: dirVec = Vector2.left; rotAngle = 90;  break;
                case 3: dirVec = Vector2.right; rotAngle = -90;  break;
            }

            Projectile arrow = Instantiate<Projectile>(Arrow, shotPoint.position, Quaternion.identity * Quaternion.Euler(0,0, rotAngle));
            arrow.SetUp(arrowDamage, 2);
            arrow.rb.AddForce(dirVec * ShotPower);
            isAttack = true;
            anim.SetBool("IsAttack", isAttack);
            
        }
    }
    public void AttackEnd()
    {
        isAttack = false;
        anim.SetBool("IsAttack", isAttack);
    }

    void DropItem()
    {

        if (Input.GetKeyDown(KeyCode.Z) && InventoryManager.Instance.items.Count > 0)
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
            GameObject obj = InventoryManager.Instance.items[0].prefab;
            Instantiate(obj, transform.position + (Vector3)dirVec, Quaternion.identity);
            InventoryManager.Instance.items[0].Remove();
        }
    }
}
