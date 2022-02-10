// B-4.Astar.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <list>
#include <vector>

#define INF		99999
#define MAP_SIZE 7

using namespace std;

/// 1: walkable
/// 0: not walkable
/// 

//bool map[MAP_SIZE][MAP_SIZE]
//{
//	{1,0,1},
//	{1,0,1},
//	{1,1,1}
//};

bool map[MAP_SIZE][MAP_SIZE] = {
	{1, 0, 1, 1, 1, 1, 1 },
	{1, 0, 1, 0, 1, 0, 1 },
	{1, 1, 1, 1, 1, 0, 1 },
	{1, 1, 0, 1, 1, 0, 1 },
	{1, 1, 1, 1, 1, 0, 0 },
	{1, 1, 0, 1, 1, 1, 1 },
	{1, 1, 1, 1, 1, 0, 1 }
};

// 현재 노드를 기준에서 여덟 방향을 확인하는 좌표를 담아둔 벡터.
vector<pair<int, int>> dir =
{
	{-1,-1}, // 좌상단
	{-1, 0}, // 상단
	{-1, 1}, // 우상단
	{ 0,-1}, // 좌측
	{ 0, 1}, // 우측
	{ 1,-1}, // 좌하단
	{ 1, 0}, // 하단
	{ 1, 1}  // 우하단
};

struct Point
{
	int X;
	int Y;

	Point()
	{
		X = -1;
		Y = -1;
	}

	Point(int X, int Y)
	{
		this->X = X;
		this->Y = Y;
	}

	Point operator=(const Point& point)
	{
		this->X = point.X;
		this->Y = point.Y;
		return *this;
	}

	bool operator==(const Point& other)
	{
		return (this->X == other.X) && (this->Y == other.Y);
	}
};

struct ASNode
{
	ASNode* pParent;
	Point		point;		// 좌표상 위치
	int			g, h, f;	// g : 이동했던 거리
							// h : 목표까지의 거리 (장애물 무시)
							// f : g + h (전체 가중치)
	ASNode()
	{
		pParent = nullptr;
		point = Point(-1, -1);
		g = INF;
		h = INF;
		f = INF;
	}
};

list<ASNode>::iterator getNodeFromList(list<ASNode>& _list, Point point)
{
	list<ASNode>::iterator iter = _list.begin();
	for (; iter != _list.end(); iter++)
	{
		if ((*iter).point == point)
			break;
	}
	return iter;
}


int getH(Point start, Point end)
{
	int xSize = abs(start.X - end.Y);
	int ySize = abs(start.Y - end.Y);
	int line = abs(xSize - ySize);
	int cross = xSize > ySize ? xSize - line : ySize - line;

	return 10 * line + 14 * cross;
}

ASNode* nodeWithLowestF(list<ASNode>& openList)
{
	ASNode* tempNode = new ASNode();
	int minF = INF;
	int minH = INF;
	for (list<ASNode>::iterator iter = openList.begin(); iter != openList.end(); iter++)
	{
		if ((*iter).f < minF || ((*iter).f == minF && (*iter).h < minH))
		{
			minF = (*iter).f;
			minH = (*iter).h;
			tempNode->pParent = (*iter).pParent;
			tempNode->point = (*iter).point;
			tempNode->f = (*iter).f;
			tempNode->g = (*iter).g;
			tempNode->h = (*iter).h;
		}
	}
	return tempNode;
}

void astar(ASNode start, ASNode end)
{
	list<ASNode> openList;
	list<ASNode> closeList;

	openList.push_back(start);
	int maxMapSizeX = sizeof(map[0]);
	int maxMapSizeY = sizeof(map) / sizeof(map[0]);

	while (true)
	{
		// 모든 노드를 다닐 때까지 값을 찾지 못했음.
		if (openList.size() == 0)
		{
			cout << "경로를 찾을 수 없습니다." << endl;
			return;
		}

		// openList 중 가장 경로에서 가까운 노드를 가져옴
		ASNode* openNode = nodeWithLowestF(openList);

		// 다음으로 선택된 Node가 목적지 Node일 때 (결과 도출 완료)
		if (openNode->point == end.point)
		{
			cout << "경로 탐색 완료. 결과 출력" << endl;
			while (nullptr != openNode)
			{
				cout << "(" << openNode->point.X << "," << openNode->point.Y << ")->";
				openNode = openNode->pParent;
			}
			cout << endl;
			return;
		}

		for (int i = 0; i < dir.size(); i++)
		{
			if (openNode->point.Y + dir[i].first >= 0 &&
				openNode->point.Y + dir[i].first < MAP_SIZE &&
				openNode->point.X + dir[i].second < MAP_SIZE &&
				openNode->point.X + dir[i].second >= 0)
			{
				int childY = openNode->point.Y + dir[i].first;
				int childX = openNode->point.X + dir[i].second;
				if (!map[childY][childX]) continue;

				// 닫힌 좌표일 경우
				if (getNodeFromList(closeList, Point(childX, childY)) != closeList.end())
					continue;

				// 처음 접근하는 좌표거나 열린 좌표일 경우
				int newG = dir[i].first != 0 && dir[i].second != 0 ? 14 : 10;
				int newH = getH(Point(childX, childY), end.point);
				int newF = newG + newH;
				list<ASNode>::iterator iter = getNodeFromList(openList, Point(childX, childY));
				if (iter == openList.end() || (*iter).f > newF)
				{
					ASNode newASNode;
					newASNode.f = newF;
					newASNode.g = newG;
					newASNode.h = newH;
					newASNode.point = Point(childX, childY);
					newASNode.pParent = openNode;
					openList.push_back(newASNode);
				}
			}
		}

		// 현재 정점을 닫힌 좌표에 집어 넣는다.
		closeList.push_back(*openNode);
		// 현재 정점을 열린 좌표에서 제외한다.
		for (list<ASNode>::iterator iter = openList.begin(); iter != openList.end(); iter++)
		{
			if ((*iter).point == openNode->point)
			{
				openList.erase(iter);
				break;
			}
		}
	}
}

int main()
{
	ASNode start, end;
	end.point = Point(6, 6);

	start.pParent = nullptr;
	start.point = Point(0, 0);
	start.g = 0;
	start.h = getH(start.point, end.point);
	start.f = start.g + start.h;

	astar(start, end);

	return 0;
}