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
#include <tuple>

using namespace std;

#define MAP_SIZE 7

char map[MAP_SIZE][MAP_SIZE] = {
	{'G', '0', '1', '1', '1','1', '1' },
	{'1', '0', '1', '0', '1','0', '1' },
	{'1', '1', '0', '0', '1','0', '1' },
	{'1', '1', '0', '0', '1','S', '1' },
	{'1', '1', '1', '1', '1','1', '1' },
	{'1', '1', '0', '1', '1','1', '1' },
	{'1', '1', '1', '1', '1','1', '1' }
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

struct Node
{
	Node* pParent; // 지나온 부모 정점
	int x, y; // 해당 정점의 맵 인덱스
	int g, h, f;
	char nodeName; // 특수한 노드의 이름
	char value;

	Node(int y, int x, char v, int i)
	{
		this->y = y;
		this->x = x;
		this->value = v;
		this->nodeName = i;
		this->g = 0;
		this->h = 0;
		this->f = 0;
		this->pParent = nullptr;
	}
};

static char uniqueName = 'a';

list<Node*> openList;
list<Node*> closeList;

tuple<int, int> getGoalIndex()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == 'G')
				return make_tuple(i, j);
		}
	}
}
tuple<int, int> getStartIndex()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == 'S')
				return make_tuple(i, j);
		}
	}
}

void debugPrintList(list<Node*>& nodeList, string name)
{
	// 경로를 표기.
	cout << name.c_str() << ":" << endl;
	//cout << "list length:" << nodelist.size() << endl;
	for (auto& ele : nodeList)
	{
		cout << "(" << ele->y << "," << ele->x << ")";
	}
	cout << endl;
}

int getH(tuple<int, int> start, tuple<int, int> end)
{
	int xSize = abs(get<1>(start) - get<1>(end));
	int ySize = abs(get<0>(start) - get<0>(end));
	int line = abs(xSize - ySize);
	int cross = xSize > ySize ? xSize - line : ySize - line;

	return 10 * line + 14 * cross;
}

Node* createNodeByIndex(int Index_Y, int Index_X, Node* parentNode, int add_g)
{
	char val = map[Index_Y][Index_X];
	// 만약 만든 노드가 지나갈 수 없는 곳이라면 nullptr을 반환.
	if (val == '0')
		return nullptr;

	// 빈 노드 생성
	Node* node = nullptr;

	// 이번 노드가 목적지라면
	if (val == 'G')
	{
		node = new Node(Index_Y, Index_X, 'G', 'G');
		node->g = parentNode->g + add_g;
		node->h = 0;
		node->f = node->g;
		node->pParent = parentNode;
	}
	// 목적지가 아니라 경로 노드라면
	else
	{
		node = new Node(Index_Y, Index_X, val, uniqueName++);
		node->g = parentNode->g + add_g; // g값을 증가시켜줌

		// 목적지의 인덱스를 가져와서 
		auto inds = getGoalIndex();
		int goalRowInd = get<0>(inds);
		int goalColInd = get<1>(inds);
		
		// 휴리스틱 측정치를 적용한다.
		//int h = getH(abs(goalRowInd - Index_Y) + abs(goalColInd - Index_X);
		node->h = getH(inds, make_tuple(Index_Y, Index_X));
		node->f = node->g + node->h;
		node->pParent = parentNode;
	}
}

Node* getChildNodes(int childIndex_Y, int childIndex_X, Node* parentNode, int add_g)
{
	
	// 오픈리스트에서 하위 노드를 가져온다.
	auto it_open = find_if(openList.begin(), openList.end(), [&](Node* node)
		{
			return node->y == childIndex_Y && node->x == childIndex_X;
		});
	// 클로즈리스트에서 하위 노드를 가져온다.
	auto it_close = find_if(closeList.begin(), closeList.end(), [&](Node* node)
		{
			return node->y == childIndex_Y && node->x == childIndex_X;
		});

	// 오픈리스트에서 하위 노드를 찾았다면
	if (it_open != openList.end())
	{
		//exist
		if ((*it_open)->g < parentNode->g + add_g)
		{
			(*it_open)->g = parentNode->g + add_g;
			parentNode->pParent = (*it_open);
			(*it_open)->f = (*it_open)->g + (*it_open)->h;

			//cout << "[parenting openlist]";
			//DebugPrintElement(*it_open, parentNode);
		}
		return *it_open;
	}
	// closeList에서 하위 노드를 찾았다면
	else if (it_close != closeList.end())
	{
		//exist
		if ((*it_close)->g < parentNode->g + add_g)
		{
			(*it_close)->g = parentNode->g + add_g;
			parentNode->pParent = (*it_close);
			(*it_close)->f = (*it_close)->g + (*it_close)->h;
			/*	cout << "[parenting closelist]";
				DebugPrintElement(*it_close, parentNode);*/
		}
		return *it_close;
	}
	// 하위 노드를 찾지 못했다면
	else
	{
		// 새로운 노드를 생성한다.
		Node* newNode = createNodeByIndex(childIndex_Y, childIndex_X, parentNode, add_g);

		// 노드가 성공적으로 생성되었다면 
		if (newNode != nullptr)
		{
			// openList에 추가한다.
			//cout << "[push] to openlist:" << newNode->row << "," << newNode->col << endl;
			openList.push_back(newNode);
		}
		// 추가로 생성한 노드를 반환한다.
		return newNode;
	}
	
	return nullptr;
	
}


void showMap()
{
	cout << "\n=======================================" << endl;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "=======================================" << endl;
}

void Astar()
{
	// openList에 정점이 없다면 함수 중지. 길찾기 실패
	if (openList.size() == 0)
	{
		cout << " 최단 경로 찾기를 실패했습니다." << endl;
		return;
	}

	// 빈 노드를 하나 생성.
	Node* openNode = nullptr;

	int smallest_f = 10000;
	// 오픈 리스트를 탐지하여 f값이 가장 작은 노드를 현재 노드로 만든다.
	// f값은 출발점부터 현재노드의 거리와 현재 노드에서 목표점까지의 거리의 합이다.
	for (auto& op : openList)
	{
		if (op->f < smallest_f)
		{
			smallest_f = op->f;
			openNode = op;
		}
	}

	if (openNode != nullptr)
	{
		// 만약에 이번 노드가 목적지라면 경로를 보여주고 맵에 표시한다.
		if (openNode->nodeName == 'G')
		{
			cout <<  " 최단 경로 : " << endl;
			while (openNode != nullptr)
			{
				cout << "(" << openNode->y << "," << openNode->x << ")";

				int indexY = openNode->y;
				int indexX = openNode->x;
				if(!(map[indexY][indexX] == 'S' || map[indexY][indexX] == 'G'))
					map[indexY][indexX] = '*';

				openNode = openNode->pParent;
				if (openNode != nullptr)
					cout << "<==";
			}

			showMap();
		}
		else
		{
			// 현재 정점에서 다음 정점을 탐색한다.
			int IndexY = openNode->y;
			int IndexX = openNode->x;

			Node* childNode;

			for (int i = 0; i < dir.size(); i++)
			{
				if (openNode->y + dir[i].first >= 0 &&
					openNode->y + dir[i].first < MAP_SIZE &&
					openNode->x + dir[i].second < MAP_SIZE &&
					openNode->x + dir[i].second >= 0)
				{
					int childIndexY = openNode->y + dir[i].first;
					int childIndexX = openNode->x + dir[i].second;
					int add_g = dir[i].first != 0 && dir[i].second != 0 ? 14 : 10;
					childNode = getChildNodes(childIndexY, childIndexX, openNode, add_g);
				}
			}

			// 현재 노드를 오픈리스트에서 제거하고 
			openList.remove_if([&](Node* node)
				{
					return node->y == IndexY && node->x == IndexX;
				});

			// 클로즈리스트에 추가하여 검사를 마쳤다는 것을 확인한다.
			closeList.push_back(openNode);

			// 다음 길찾기를 수행한다.
			Astar();
		}
	}
}

int main()
{
	showMap();
	tuple<int, int> start_index = getStartIndex();
	int startY = get<0>(start_index);
	int startX = get<1>(start_index);

	Node* startNode = new Node(startY, startX, 'S', 'S');

	openList.push_back(startNode);

	Astar();
}
