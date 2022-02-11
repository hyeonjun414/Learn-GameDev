// MyAstar.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// A* 알고리즘
// 1. A* 알고리즘이란
//		1) 다익스트라 알고리즘과 다르게 출발지와 목적지를 정하는 알고리즘이다.
//		2) 최단 거리뿐만아니라 최단 경로를 파악할 수 있다.
//		3) 휴리스틱 추정값을 사용하는데 어떤 방식으로 제공하느냐에 따라 알고리즘의 속도가 결정된다.
// 
// 2. 속성
//		1) 열린 목록과 닫힌 목록이 있다 ( Open List, Close List )
//		2) 열린 목록에는 최단 경로를 분석하기 위한 상태값들이 계속 갱신된다.
//		3) 닫힌 목록에는 처리가 완료된 노드를 담아 두기 위한 목적으로 사용된다.
//		4) G : 시작 정점에서 해당 정점까지의 실제 비용
//		5) H : 휴리스틱 추정 값으로 해당 정점에서 최종 목적지 까지 도달하는데 소요될 것으로 추정되는 값.
//		6) F : G + H
//		7) 부모 정점 : Parent Node, 해당 정점에 도달하기 직전에 거치는 정점
// 
// 3. 방법
//		1) 먼저 출발 정점을 닫힌 목록에 넣는다.
//		2) 출발 정점에 연결되어 있는 정점들을 열린 목록에 추가한다.
//		3) 열린 목록에 추가할때 F, G, H, Parent Node 값을 같이 집어 넣는다.
//		4) H 값은 맨해튼 거리로 좌표상 목적지까지의 직선거리로 추정한다.
//		   만약 목적지까지 바로 연결된다면 해당 비용을 적용한다.
//		5) 열린 목록에서 f 값이 가장 작은 정점를 찾아 닫힌 목록에 추가하고
//		   닫힌 목록에 존재하지 않는 정점에 대해 열린 목록에 추가한다.
//		6) G 값은 직전 정점에 소요되는 비용에 더해 이번에 확인하는 정점의 비용을 추가하는 식으로 값을 갱신한다.
//		7) 위의 작업을 반복하며 열린목록에 없는 정점을 추가를, 있던 정점을 갱신을 해준다.
//		8) 최종적으로 열린 목록 중 닫힌 목록에 추가되는 정점이 목적지라면 알고리즘은 종료된다.
//		9) 닫힌 목록의 목적지 노드를 추적하여 올라가면 경로가 나오게 된다.
#include <iostream>
#include <list>
#include <vector>

#define INF		99999
#define MAP_SIZE 7

using namespace std;

/// 1: walkable
/// 0: not walkable

//bool map[MAP_SIZE][MAP_SIZE]
//{
//	{1,0,1},
//	{1,0,1},
//	{1,1,1}
//};

bool map[MAP_SIZE][MAP_SIZE] = {
	{1, 0, 1, 1, 1, 1, 1 },
	{1, 0, 1, 0, 1, 0, 1 },
	{1, 1, 1, 0, 1, 0, 1 },
	{1, 1, 0, 1, 1, 0, 1 },
	{1, 1, 1, 1, 1, 0, 0 },
	{1, 1, 0, 1, 1, 1, 1 },
	{1, 1, 1, 1, 1, 0, 1 }
};

// 현재 노드를 기준에서 여덟 방향을 확인하는 좌표를 담아둔 벡터.
vector<pair<int, int>> dir =
{
	// 4방향
	{-1, 0}, // 상단
	{ 1, 0}, // 하단
	{ 0,-1}, // 좌측
	{ 0, 1}, // 우측

	// 8방향
	{-1,-1}, // 좌상단
	{-1, 1}, // 우상단
	{ 1,-1}, // 좌하단
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
	ASNode(ASNode* pParent, Point point, int g, int h)
	{
		this->pParent = pParent;
		this->point = point;
		this->g = g;
		this->h = h;
		this->f = g + h;
	}
};
// 4방향, 길이 최소 하나, 길이 최소 두개, 조건없는 8방향
enum class MODE { Normal4, Half8, Both8, None8};

// 해당 좌표의 정점이 리스트에 존재하는지 확인하는 함수
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

// 한 정점을 기준으로 도착점까지의 h값을 추산하여 반환하는 함수
int getH(Point start, Point end)
{
	int xSize = abs(start.X - end.Y);
	int ySize = abs(start.Y - end.Y);
	int line = abs(xSize - ySize);
	int cross = xSize > ySize ? xSize - line : ySize - line;

	return 10 * line + 14 * cross;
}

// 오픈 리스트에서 f값이 가장 작은 정점을 반환하는 함수
// 오픈 리스트에 있는 정점들은 아직 주변 정점을 확인하지 않은 정점들이다.
ASNode* nodeWithLowestF(list<ASNode>& openList)
{
	ASNode* tempNode = new ASNode();
	int minF = INF;
	int minH = INF;
	for (list<ASNode>::iterator iter = openList.begin(); iter != openList.end(); iter++)
	{
		// f뿐만이 아니라 h값도 비교하는 이유는
		// f값이 같은 최단 경로중 가장 목적이에 근접해 있는 정점을 먼저 탐지하기 위해서이다.
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

// 현재 확인하려는 좌표가 경로 정점 중에 하나인지 확인하는 함수.
bool findPathNodeInMap(int i, int j, ASNode* Node = nullptr)
{
	if (Node == nullptr) return false;
	ASNode* tempNode = Node->pParent;
	while (nullptr != tempNode)
	{
		if (i == tempNode->point.Y && j == tempNode->point.X)
			return true;

		tempNode = tempNode->pParent;
	}

	return false;
}

// 시작점, 도착점, 경로등을 출력하는 함수.
void showMap(Point start = Point(-1, -1), Point end = Point(-1, -1), ASNode* node = nullptr)
{
	for (int i = 0; i < MAP_SIZE + 1; i++)
	{
		cout << "==";
	}
	cout << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < MAP_SIZE; j++)
		{
			// 해당 좌표가 시작점일때
			if (i == start.Y && j == start.X)
				cout << "ST";
			// 해당 좌표가 도착점일때
			else if (i == end.Y && j == end.X)
				cout << "GL";
			// 해당 좌표가 최단경로일때
			else if (node != nullptr && findPathNodeInMap(i, j, node))
			{
				cout << "★";
			}
			// 해당 좌표가 어떤 특징도 없을때 이동 가능 여부를 표기한다.
			else
			{
				if (map[i][j])
					cout << "■";
				else
					cout << "□";
			}
		}
		cout << "|" << endl;
	}
	for (int i = 0; i < MAP_SIZE + 1; i++)
	{
		cout << "==";
	}
	cout << endl;
}

// A* : 최단경로 탐색 알고리즘
void astar(Point start, Point end, MODE mode)
{
	list<ASNode> openList;
	list<ASNode> closeList;

	openList.push_back(ASNode(nullptr, start, 0, getH(start, end)));

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
		if (openNode->point == end)
		{
			ASNode* showMapNode = openNode;
			cout << "경로 탐색 완료. 결과 출력" << endl;
			while (nullptr != openNode)
			{
				if (nullptr == openNode->pParent)
					cout << "(" << openNode->point.X << "," << openNode->point.Y << ")";
				else
					cout << "(" << openNode->point.X << "," << openNode->point.Y << ")->";
				openNode = openNode->pParent;
			}
			cout << endl;

			showMap(start, end, showMapNode);

			return;
		}

		for (int i = 0; i < dir.size(); i++)
		{
			// 현재 정점에서 탐색되는 정점이 맵의 범위에서 벗어나는지 확인
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

				// 기본 4방향
				if (mode == MODE::Normal4 && i >= dir.size() / 2) continue;

				Point wall1 = Point(childX, openNode->point.Y);
				Point wall2 = Point(openNode->point.X, childY);

				// 인접 정점에 하나는 길이 열려있어야 함.
				if (mode == MODE::Half8 && !(map[wall1.Y][wall1.X] || map[wall2.Y][wall2.X])) continue;

				// 인접 정점에 길이 두개 다 열려있어야 함.
				if (mode == MODE::Both8 && !(map[wall1.Y][wall1.X] && map[wall2.Y][wall2.X])) continue;




				// 처음 접근하는 좌표거나 열린 좌표일 경우
				int newG = dir[i].first != 0 && dir[i].second != 0 ? 14 : 10;
				int newH = getH(Point(childX, childY), end);
				int newF = newG + newH;

				list<ASNode>::iterator iter = getNodeFromList(openList, Point(childX, childY));

				if (iter == openList.end() || (*iter).f > newF)
				{
					ASNode newASNode(openNode, Point(childX, childY), newG, newH);
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
	Point start = Point(0, 0);
	Point goal = Point(6, 6);

	showMap(start, goal);
	astar(start, goal, MODE::Both8);

	return 0;
}