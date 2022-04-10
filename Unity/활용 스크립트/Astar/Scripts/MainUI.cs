using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainUI : MonoBehaviour
{
    public Board board;
    public Dropdown nodeTypeDropdown;
    // Start is called before the first frame update
    void Start()
    {
        for(int i = 0; i<(int)NodeColor.Size; i++)
        {
            NodeColor nc = (NodeColor)i;
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
            board.color = (NodeColor)(nodeTypeDropdown.value - 1);
        }
    }
}
