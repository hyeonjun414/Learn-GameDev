using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ASCube : MonoBehaviour
{
    public NodeType m_eNodeType;
    public Renderer m_cRend;
    public Point    m_tPoint;
    public Point point
    {
        get
        {
            return m_tPoint;
        }
        set
        {
            m_tPoint = value;
            m_PosX = value.x;
            m_PosY = value.y;
        }
    }
    public int m_PosX;
    public int m_PosY;
    // Start is called before the first frame update
    void Start()
    {
        m_cRend = GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
