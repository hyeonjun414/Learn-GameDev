using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPC : MonoBehaviour, IInteractable
{
    GameManager gm;

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
            print("NPC와 상호작용");
            gm.SetActiveDialog(true);
            gm.SetDialogContent("NPC", conversation[converIndex]);
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
