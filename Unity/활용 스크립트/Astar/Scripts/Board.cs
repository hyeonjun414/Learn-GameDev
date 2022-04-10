using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum NodeColor
{
    Normal,
    Denial,
    Open,
    Close,
    Start,
    End,

    Size
}



public class Board : MonoBehaviour
{
    public static int[,] map =
    {
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1}
     };
    public int x, y;
    [SerializeField]
    public ASNode[,] ASNodes;

    public NodeColor color;

    public Material[] nodeColors;

    // Start is called before the first frame update
    void Start()
    {
        ASNodes = new ASNode[x, y];
        ASNode[] nodes = gameObject.GetComponentsInChildren<ASNode>();

        int n = 0;
        foreach (ASNode node in nodes)
        {
            //node.rend.material = nodeColors[(int)NodeColor.Normal];
            ASNodes[(int)(n/x), (int)(n%x)] = node;
            ASNodes[(int)(n / x), (int)(n % x)].rend.material = nodeColors[0];
            ASNodes[(int)(n / x), (int)(n % x)].point = new Point((int)(n / x), (int)(n % x));
            n++;
            print(((int)(n / x)).ToString() +", "+ ((int)(n % x)).ToString());
        }
    }

    // Update is called once per frame
    void Update()
    {
        InputClick();
    }
    void InputClick()
    {
        if(Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                GameObject go = hit.transform.gameObject;
                print(go);
                ASNode node = go.GetComponent<ASNode>();
                if(null != node)
                {
                    node.rend.material = nodeColors[(int)color];
                }
            }
        }
    }
}
