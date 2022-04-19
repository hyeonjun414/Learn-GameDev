using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;


public class Item : MonoBehaviour
{
    public UnityEvent onUse;

    public string itemName;
    public int score;

    private void OnDestroy()
    {
        onUse.Invoke();
    }
}
