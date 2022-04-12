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
    public Point(int _x, int _y)
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

public class ASNode
{
    public bool isActive;
    public ASNode prevNode;
    public Point point;
    public int g, h, f;

    public ASNode()
    {
        isActive = true;
        prevNode = null;
        point = null;
        g = Constants.INF;
        h = Constants.INF;
        f = Constants.INF;
    }
    public ASNode(ASNode _parent, Point _point, int _g, int _h)
    {
        isActive = true;
        prevNode = _parent;
        point = _point;
        g = _g;
        h = _h;
        f = g + h;
    }
}

public class PathFinder : MonoBehaviour
{
    public Board board;
    public int MAP_SIZE;
    int[,] map;
    public List<(int y, int x)> dir = new List<(int y, int x)>();

    public enum MODE { None4, None8, Half8, Both8 };

    // Start is called before the first frame update
    void Start()
    {
        board = FindObjectOfType<Board>();
        AddDir();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void AddDir()
    {
        dir.Add((-1, 0));
        dir.Add((1, 0));
        dir.Add((0, -1));
        dir.Add((0, 1));
        dir.Add((-1, -1));
        dir.Add((-1, 1));
        dir.Add((1, -1));
        dir.Add((1, 1));
    }

    public void ExcutePathFind(Point _start, Point _end, int[,] _map, int _mapSize, MODE _mode)
    {
        MAP_SIZE = _mapSize;
        map = _map;
        StartCoroutine(Astar(_start, _end, _mode));
    }

    // 한 정점을 기준으로 도착점까지의 h값을 추산하여 반환하는 함수
    public int GetH(Point start, Point end)
    {
        int xSize = Mathf.Abs(start.x - end.x);
        int ySize = Mathf.Abs(start.y - end.y);
        int line = Mathf.Abs(xSize - ySize);
        int cross = xSize > ySize ? xSize - line : ySize - line;

        return 10 * line + 14 * cross;
    }
    // 해당 좌표의 정점이 리스트에 존재하는지 확인하는 함수
    public ASNode GetNodeFromList(LinkedList<ASNode> _list, Point _point)
    {
        ASNode resultNode = null;
        foreach (ASNode node in _list)
        {
            if (node.point == _point)
                resultNode = node;
        }
        return resultNode;
    }
    // 오픈 리스트에서 f값이 가장 작은 정점을 반환하는 함수
    public ASNode NodeWithLowestF(LinkedList<ASNode> _list)
    {
        ASNode Node = null;
        int minF = Constants.INF;
        int minH = Constants.INF;
        foreach (ASNode node in _list)
        {
            if ((node.f < minF || (node.f == minF && node.h < minH)) &&
                node.isActive)
            {
                minF = node.f;
                minH = node.h;
                Node = node;
            }
        }
        return Node;
    }
    public IEnumerator Astar(Point start, Point end, MODE mode)
    {
        LinkedList<ASNode> openList = new LinkedList<ASNode>();
        openList.AddLast(new ASNode(null, start, 0, GetH(start, end)));

        while (true)
        {
            if (openList.Count == 0)
            {
                print("경로를 찾을 수 없습니다.");
                yield break;
            }

            ASNode openNode = NodeWithLowestF(openList);
            Point nodePos = openNode.point;
            if (openNode.point == end)
            {
                ASNode tempNode = openNode;
                
                while (null != tempNode)
                {
                    board.ASCubes[tempNode.point.y, tempNode.point.x].m_cRend.material = board.nodeTypes[(int)NodeType.End];
                    print("(" + tempNode.point.y + "," + tempNode.point.x + ")");
                    tempNode = tempNode.prevNode;
                }
                print("경로 탐색 완료. 결과 출력");
                yield break;
            }
            
            for (int i = 0; i < dir.Count; i++)
            {
                if (openNode.point.y + dir[i].y >= 0 &&
                    openNode.point.y + dir[i].y < MAP_SIZE &&
                    openNode.point.x + dir[i].x < MAP_SIZE &&
                    openNode.point.x + dir[i].x >= 0)
                {
                    int childY = openNode.point.y + dir[i].y;
                    int childX = openNode.point.x + dir[i].x;

                    ASNode tempNode = GetNodeFromList(openList, new Point(childX, childY));

                    // 못가는 노드면 다음 탐색
                    if (map[childY, childX] == 0) continue;

                    // 이미 오픈리스트에 있는 노드이면
                    if (GetNodeFromList(openList, new Point(childX, childY)) != null &&
                        !tempNode.isActive) continue;

                    // 모드에 따른 처리
                    if (mode == MODE.None4 && i >= dir.Count / 2) continue;

                    Point wall1 = new Point(childX, openNode.point.y);
                    Point wall2 = new Point(openNode.point.x, childY);

                    if (mode == MODE.Half8 &&
                        !(map[wall1.y, wall1.x] == 1 || map[wall2.y, wall2.x] == 1))
                        continue;
                    if (mode == MODE.Both8 &&
                        !(map[wall1.y, wall1.x] == 1 && map[wall2.y, wall2.x] == 1))
                        continue;


                    int newG = openNode.g + dir[i].y != 0 && dir[i].x != 0 ? 14 : 10;
                    int newH = GetH(new Point(childX, childY), end);
                    int newF = newG + newH;

                    if (tempNode == null)
                    {
                        openList.AddLast(new ASNode(openNode, new Point(childX, childY), newG, newH));
                        board.ASCubes[childY, childX].m_cRend.material = board.nodeTypes[(int)NodeType.Open];
                    }
                    else if(tempNode.f > newF)
                    {
                        tempNode.g = newG;
                        tempNode.h = newH;
                        tempNode.f = newF;
                        tempNode.prevNode = openNode;
                    }
                }
                yield return new WaitForSeconds(0.02f);
            }
            openNode.isActive = false;
            board.ASCubes[nodePos.y, nodePos.x].m_cRend.material = board.nodeTypes[(int)NodeType.Close];
            yield return new WaitForSeconds(0.02f);
        }
    }
}
