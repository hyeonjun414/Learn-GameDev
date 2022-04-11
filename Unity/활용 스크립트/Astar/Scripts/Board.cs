using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum NodeType
{
    Normal,
    Denial,
    Start,
    End,
    Open,
    Close,


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
    public ASCube[,] ASCubes;

    public MainUI mainUI;
    public PathFinder astar;

    public NodeType nodeType;
    public Point startPos = null;
    public Point EndPos = null;

    public Material[] nodeTypes;

    bool IsChoiceNode = false;

    // Start is called before the first frame update
    void Start()
    {
        mainUI = FindObjectOfType<MainUI>();
        astar = FindObjectOfType<PathFinder>();

        ASCubes = new ASCube[y, x];
        ASCube[] nodes = gameObject.GetComponentsInChildren<ASCube>();

        int n = 0;
        foreach (ASCube node in nodes)
        {
            int pointX = (int)(n % x);
            int pointY = (int)(n / y);
            ASCubes[pointY, pointX] = node;
            ASCubes[pointY, pointX].m_cRend.material = nodeTypes[0];
            ASCubes[pointY, pointX].point = new Point(pointX, pointY);
            n++;
            
        }
        BtnReset();
    }

    // Update is called once per frame
    void Update()
    {
        InputClick();
    }
    void InputClick()
    {
        if(Input.GetMouseButton(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                GameObject go = hit.transform.gameObject;
                print(go);
                ASCube node = go.GetComponent<ASCube>();
                if (null != node && 
                    (NodeType.Start == node.m_eNodeType ||
                     NodeType.End == node.m_eNodeType))
                {
                    
                }
            }
        }
        if(Input.GetMouseButton(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                GameObject go = hit.transform.gameObject;
                print(go);
                ASCube node = go.GetComponent<ASCube>();
                if(null != node)
                {
                    node.m_cRend.material = nodeTypes[(int)NodeType.Denial];
                    Point pos = node.point;
                    map[pos.y, pos.x] = 0;
                }
            }
        }

        if (IsChoiceNode) return;

        else if (Input.GetMouseButton(1))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                GameObject go = hit.transform.gameObject;
                print(go);
                ASCube node = go.GetComponent<ASCube>();
                if (null != node)
                {
                    node.m_cRend.material = nodeTypes[(int)NodeType.Normal];
                    Point pos = node.point;
                    map[pos.y, pos.x] = 1;
                }
            }
        }
    }

    public void BtnStart()
    {
        astar.ExcutePathFind(startPos, EndPos, map, 10, PathFinder.MODE.Half8);
    }
    public void BtnReset()
    {
        foreach (ASCube node in ASCubes)
        {
            node.m_cRend.material = nodeTypes[(int)NodeType.Normal];
            map[node.point.y,node.point.x] = 1;
        }
        ASCubes[0,0].m_cRend.material = nodeTypes[(int)NodeType.Start];
        startPos = new Point(0, 0);
        mainUI.text_StartPos.text = "0, 0";
        ASCubes[9,9].m_cRend.material = nodeTypes[(int)NodeType.End];
        EndPos = new Point(9, 9);
        mainUI.text_EndPos.text = "9, 9";
    }
}
