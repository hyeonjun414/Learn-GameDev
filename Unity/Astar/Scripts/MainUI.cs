using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainUI : MonoBehaviour
{
    public Board board;
    public Dropdown nodeTypeDropdown;
    public Text text_StartPos;
    public Text text_EndPos;
    // Start is called before the first frame update
    void Start()
    {
        for(int i = 0; i<(int)NodeType.Size; i++)
        {
            NodeType nc = (NodeType)i;
            Dropdown.OptionData data = new Dropdown.OptionData();
            data.text = nc.ToString();
            nodeTypeDropdown.options.Add(data);
        }


    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void OnNodeTypeChanged()
    {
        int value = nodeTypeDropdown.value;
        if(0 != value)
        {
            board.nodeType = (NodeType)(nodeTypeDropdown.value - 1);
        }
    }

}
