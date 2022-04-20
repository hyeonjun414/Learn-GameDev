using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public GameObject dialog;
    public Text nameText;
    public Text discText;

    public void SetActiveDialog(bool Active)
    {
        dialog.SetActive(Active);
    }
    public void SetDialogContent(string name, string disc)
    {
        nameText.text = name;
        discText.text = disc;
    }
}
