#define MAX_SIZE 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Astar
{
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
        public ASNode parent;
        public Point point;
        public int g, h, f;

        public ASNode()
        {
            isActive = true;
            parent = null;
            point = null;
            g = Constants.INF;
            h = Constants.INF;
            f = Constants.INF;
        }
        public ASNode(ASNode _parent, Point _point, int _g, int _h)
        {
            isActive = true;
            parent = _parent;
            point = _point;
            g = _g;
            h = _h;
            f = g + h;
        }
    }

    public class PathFinder
    {

        // 맵 사이즈, 최대 값 정의
        public int MAP_SIZE;
        int[,] map;
        public List<(int y, int x)> dir = new List<(int y, int x)>();

        public PathFinder()
        {
            AddDir();
        }

        ~PathFinder(){}

        public void ExcutePathFind(Point _start, Point _end, int[,] _map, int _mapSize, MODE _mode)
        {
            MAP_SIZE = _mapSize;
            map = _map;
            ShowMap(_start, _end);
            Astar(_start, _end, _mode);
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

        public enum MODE { None4, None8, Half8, Both8 };

        // 한 정점을 기준으로 도착점까지의 h값을 추산하여 반환하는 함수
        public int GetH(Point start, Point end)
        {
            int xSize = Math.Abs(start.x - end.y);
            int ySize = Math.Abs(start.y - end.y);
            int line = Math.Abs(xSize - ySize);
            int cross = xSize > ySize ? xSize - line : ySize - line;

            return 10 * line + 14 * cross;
        }

        // 해당 좌표의 정점이 리스트에 존재하는지 확인하는 함수
        public ASNode GetNodeFromList(LinkedList<ASNode> _list, Point _point)
        {
            foreach (ASNode node in _list)
            {
                if (node.point == _point && node.isActive)
                    return node;
            }
            return null;
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

        public bool FindPathNodeInMap(int _i, int _j, ASNode _node = null)
        {
            if (_node == null) return false;

            ASNode tempNode = _node.parent;
            while (null != tempNode)
            {
                if (_i == tempNode.point.y && _j == tempNode.point.x)
                    return true;

                tempNode = tempNode.parent;
            }

            return false;
        }

        public void ShowMap(Point _start, Point _end, ASNode _node = null)
        {
            for (int i = 0; i < MAP_SIZE + 1; i++)
            {
                Console.Write("==");
            }
            Console.WriteLine();
            for (int i = 0; i < MAP_SIZE; i++)
            {
                Console.Write("|");
                for (int j = 0; j < MAP_SIZE; j++)
                {
                    // 해당 좌표가 시작점일때
                    if (i == _start.y && j == _start.x)
                        Console.Write("ST");
                    // 해당 좌표가 도착점일때
                    else if (i == _end.y && j == _end.x)
                        Console.Write("GL");
                    // 해당 좌표가 최단경로일때
                    else if (_node != null && FindPathNodeInMap(i, j, _node))
                    {
                        Console.Write("★");
                    }
                    // 해당 좌표가 어떤 특징도 없을때 이동 가능 여부를 표기한다.
                    else
                    {
                        if (map[i, j] == 1)
                            Console.Write("■");
                        else
                            Console.Write("□");
                    }
                }
                Console.WriteLine("|");
            }
            for (int i = 0; i < MAP_SIZE + 1; i++)
            {
                Console.Write("==");
            }
            Console.WriteLine();
        }

        public void Astar(Point start, Point end, MODE mode)
        {
            LinkedList<ASNode> openList = new LinkedList<ASNode>();
            openList.AddLast(new ASNode(null, start, 0, GetH(start, end)));

            while (true)
            {
                if (openList.Count == 0)
                {
                    Console.WriteLine("경로를 찾을 수 없습니다.");
                    return;
                }

                ASNode openNode = NodeWithLowestF(openList);

                if (openNode.point == end)
                {
                    ASNode tempNode = openNode;
                    ASNode showMapNode = openNode;
                    Console.WriteLine("경로 탐색 완료. 결과 출력");
                    while (null != tempNode)
                    {
                        if (null == tempNode.parent)
                            Console.Write("(" + tempNode.point.y + "," + tempNode.point.x + ")");
                        else
                            Console.Write("(" + tempNode.point.y + "," + tempNode.point.x + ")->");
                        tempNode = tempNode.parent;
                    }
                    Console.WriteLine();
                    ShowMap(start, end, showMapNode);

                    return;
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

                        if (map[childY, childX] == 0) continue;

                        if (GetNodeFromList(openList, new Point(childX, childY)) != null) continue;

                        if (mode == MODE.None4 && i >= dir.Count / 2) continue;

                        Point wall1 = new Point(childX, openNode.point.y);
                        Point wall2 = new Point(openNode.point.x, childY);

                        if (mode == MODE.Half8 &&
                            !(map[wall1.y, wall1.x] == 1 || map[wall2.y, wall2.x] == 1))
                            continue;
                        if (mode == MODE.Both8 &&
                            !(map[wall1.y, wall1.x] == 1 && map[wall2.y, wall2.x] == 1))
                            continue;

                        int newG = dir[i].y != 0 && dir[i].x != 0 ? 14 : 10;
                        int newH = GetH(new Point(childX, childY), end);
                        int newF = newG + newH;

                        ASNode tempNode = GetNodeFromList(openList, new Point(childX, childY));

                        if (tempNode == null || tempNode.f > newF)
                        {
                            openList.AddLast(new ASNode(openNode, new Point(childX, childY), newG, newH));
                        }
                    }
                }
                openNode.isActive = false;
            }
        }
    }
}
