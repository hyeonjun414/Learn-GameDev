﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : EquipItem
{
    public int damage;

    public Collider2D coll;

    private void Awake()
    {
        damage = ((EquipInvenItem)myData).damage;
        coll = GetComponent<Collider2D>();
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.tag == "Enemy" && !other.isTrigger)
        {
            IDamageable enemy = other.GetComponent<IDamageable>();
            if(null != enemy)
            {
                enemy.Hit(damage);
            }
        }
    }
    public void AttackStart()
    {
        gameObject.SetActive(true);
    }
    public void AttackEnd()
    {
        print("공격 종료");
        gameObject.SetActive(false);
    }
}
