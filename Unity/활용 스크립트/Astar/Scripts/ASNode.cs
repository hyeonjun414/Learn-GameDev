using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Point
{
    public int x;
    public int y;

    public Point()
    {
        x = -1;
        y = -1;
    }
    public Point(int _y, int _x)
    {
        x = _x;
        y = _y;
    }
    public static bool operator ==(Point a, Point b)
    {
        return a.x == b.x && a.y == b.y;
    }
    public static bool operator !=(Point a, Point b)
    {
        return !(a == b);
    }
}
public class ASNode : MonoBehaviour
{
    public Material nodeColor;
    public bool isActive;
    public ASNode prevNode;
    [SerializeField]
    public Point _point;
    public Point point
    {
        get
        {
            return _point;
        }
        set
        {
            _point = value;
            x = value.x;
            y = value.y;
        }
    }
    public int x, y;
    public int g, h, f;

    public Renderer rend;
    // Start is called before the first frame update
    void Start()
    {
        rend = GetComponent<Renderer>();
        rend.material = nodeColor;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
