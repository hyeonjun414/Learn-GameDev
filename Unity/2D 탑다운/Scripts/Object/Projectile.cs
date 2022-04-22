using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    public Rigidbody2D rb;
    public int damage;
    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
    }
    public void SetUp(int damage, int duration)
    {
        this.damage = damage;
        Destroy(gameObject, duration);
    }
    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.tag == "Enemy" && !other.isTrigger)
        {
            IDamageable enemy = other.GetComponent<IDamageable>();
            enemy?.Hit(damage);
            
            Destroy(gameObject);
        }
    }
}
