using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Chest : MonoBehaviour, IInteractable
{
    GameManager gm;

    [TextArea]
    public string[] conversation;
    int converIndex = 0;
    private void Start()
    {
        gm = FindObjectOfType<GameManager>();
    }
    public bool Interaction()
    {
        if (converIndex < conversation.Length)
        {
            print("상자와 상호작용");
            gm.SetActiveDialog(true);
            gm.SetDialogContent("상자", conversation[converIndex]);
            converIndex++;
            return true;
        }
        else
        {
            converIndex = 0;
            gm.SetActiveDialog(false);
            return false;
        }

    }
}
