// Astar.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//1. P = 시작점
//2. P에 f, g, h 할당
//3. Open 리스트에 P 넣기
//4. B = Open 리스트에서 가장 낮은 f 값을 가진 노드
//a. B가 목표점이면, 경로 완성
//b. Open 리스트가 비었으면, 목표점까지 경로가 존재하지 않음
//5. C = B에 연결된 노드
//a. C에 f, g, h 값 할당
//b. Open / Close 리스트에서 C가 있는지 체크
//1. 있으면, 더 낮은 f 값으로 경로 업데이트
//2. 없으면, C를 Open 리스트에 넣기
//c. 5번으로 돌아가서 B에 연결된 모든 노드를 대상으로 진행
//6. 4번으로 돌아감
#include <iostream>
#include <list>
#include <algorithm>
#include <tuple>

using namespace std;

char map[7][5] = {
	{'G', '0', '1', '1', '1' },
	{'1', '0', '1', '0', '1' },
	{'1', '1', '1', '0', '1' },
	{'1', '1', '0', 'S', '1' },
	{'1', '1', '1', '1', '1' },
	{'1', '1', '0', '1', '1' },
	{'1', '1', '1', '1', '1' }
};

class ASNode {
public:
	ASNode* conn; // 실제 패스에 연결되는 노드
	int row, col; // 해당 노드의 맵 인덱스
	int g, h, f;
	char nodeName; // 특수한 노드의 이름
	char value;

public:
	ASNode(int _x, int _y, char _v, int _i)
	{
		row = _x;
		col = _y;
		value = _v;
		nodeName = _i;
		g = 0;
		h = 0;
		f = 0;
	}
};

ASNode* GetChildNodes(int childIndRow, int childIndCol, ASNode* parentNode);
ASNode* CreateNodeByIndex(int rowIndex, int colIndex, ASNode* parentNode);

static char uniqueName = 'a';
list<ASNode*> openList;
list<ASNode*> closeList;


tuple<int, int> GetGoalIndex()
{
	int maxMapSizeRow = sizeof(map) / sizeof(map[0]);
	int maxMapSizeCol = sizeof(map[0]);

	for (int i = 0; i < maxMapSizeRow; i++)
	{
		for (int j = 0; j < maxMapSizeCol; j++)
		{
			if (map[i][j] == 'G')
			{
				return make_tuple(i, j);
			}
		}
	}
}
void DebugPrintList(list<ASNode*>& nodelist, string name)
{
	cout << name.c_str() << ":" << endl;
	//cout << "list length:" << nodelist.size() << endl;
	for (auto& ele : nodelist)
	{
		cout << "(" << ele->row << "," << ele->col << ")";
	}
	cout << endl;
}

void ShowMap()
{
	int maxMapSizeRow = sizeof(map) / sizeof(map[0]);
	int maxMapSizeCol = sizeof(map[0]);

	cout << "\n=======================================" << endl;
	for (int i = 0; i < maxMapSizeRow; i++)
	{
		for (int j = 0; j < maxMapSizeCol; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "=======================================" << endl;
}

void FindPath()
{
	//DebugPrintList(openList, "Open");
	//DebugPrintList(closeList, "Close");
	int maxMapSizeRow = sizeof(map) / sizeof(map[0]);
	int maxMapSizeCol = sizeof(map[0]);

	//cout << "maxMapSizeRow:" << maxMapSizeRow << ", maxMapSizeCol:" << maxMapSizeCol <<endl;

	if (openList.size() == 0)
	{
		//end of finding.  no route to goal
		cout << "no path exists." << endl;
		return;
	}

	ASNode* openNode = nullptr;

	int smallest_f = 10000;
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
		if (openNode->nodeName == 'G') //arrive at Goal
		{
			cout << "< Optimal Path (row, column)>" << endl;
			while (openNode != nullptr)
			{
				cout << "(" << openNode->row << "," << openNode->col << ")";

				int rowind = openNode->row;
				int colind = openNode->col;
				map[rowind][colind] = '*';

				openNode = openNode->conn;
				if (openNode != nullptr)
					cout << "<==";
			}

			ShowMap();
		}
		else
		{
			//Get children nodes from the current node
			//check 4-way, up,down,left,right
			int rowInd = openNode->row;
			int colInd = openNode->col;

			//check up
			ASNode* childNode;
			if (openNode->row - 1 >= 0)
			{
				int childIndRow = openNode->row - 1;
				int childIndCol = openNode->col;

				childNode = GetChildNodes(childIndRow, childIndCol, openNode);
			}

			if (openNode->row + 1 < maxMapSizeRow)
			{
				int childIndRow = openNode->row + 1;
				int childIndCol = openNode->col;

				childNode = GetChildNodes(childIndRow, childIndCol, openNode);
			}

			if (openNode->col + 1 < maxMapSizeCol)
			{
				int childIndRow = openNode->row;
				int childIndCol = openNode->col + 1;

				childNode = GetChildNodes(childIndRow, childIndCol, openNode);
			}

			if (openNode->col - 1 >= 0)
			{
				int childIndRow = openNode->row;
				int childIndCol = openNode->col - 1;

				childNode = GetChildNodes(childIndRow, childIndCol, openNode);
			}

			//cout << "[Remove from openlist] (" << rowInd << "," << colInd << ")" << endl;
			openList.remove_if([&](ASNode* node)
				{
					if (node->row == rowInd && node->col == colInd)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

			//cout << "[push] to closeList:" << rowInd << "," << openNode->col << endl;
			closeList.push_back(openNode);

			FindPath();
		}
	}
}

ASNode* GetChildNodes(int childIndRow, int childIndCol, ASNode* parentNode)
{
	auto it_open = find_if(openList.begin(), openList.end(), [&](ASNode* node)
		{
			if (node->row == childIndRow && node->col == childIndCol)
			{
				return true;
			}
			else
			{
				return false;
			}
		});

	auto it_close = find_if(closeList.begin(), closeList.end(), [&](ASNode* node)
		{
			if (node->row == childIndRow && node->col == childIndCol)
			{
				return true;
			}
			else
			{
				return false;
			}
		});

	if (it_open != openList.end())
	{
		//exist
		if ((*it_open)->g < parentNode->g + 1)
		{
			(*it_open)->g = parentNode->g + 1;
			parentNode->conn = (*it_open);
			(*it_open)->f = (*it_open)->g + (*it_open)->h;

			//cout << "[parenting openlist]";
			//DebugPrintElement(*it_open, parentNode);
		}

		return *it_open;
	}
	else if (it_close != closeList.end())
	{

		//exist
		if ((*it_close)->g < parentNode->g + 1)
		{
			(*it_close)->g = parentNode->g + 1;
			parentNode->conn = (*it_close);
			(*it_close)->f = (*it_close)->g + (*it_close)->h;
			/*	cout << "[parenting closelist]";
				DebugPrintElement(*it_close, parentNode);*/
		}
		return *it_close;
	}
	else
	{
		ASNode* newNode = CreateNodeByIndex(childIndRow, childIndCol, parentNode);

		if (newNode != nullptr)
		{
			//cout << "[push] to openlist:" << newNode->row << "," << newNode->col << endl;
			openList.push_back(newNode);
		}
		return newNode;
	}

	return nullptr;
}


ASNode* CreateNodeByIndex(int rowIndex, int colIndex, ASNode* parentNode)
{
	char val = map[rowIndex][colIndex];

	if (val == '0')
		return nullptr;

	ASNode* node = nullptr;
	if (val == 'G')
	{
		node = new ASNode(rowIndex, colIndex, 'G', 'G');
		node->g = parentNode->g + 1;
		node->h = 0;
		node->f = node->g;
		node->conn = parentNode;
	}
	else
	{
		node = new ASNode(rowIndex, colIndex, val, uniqueName++);
		node->g = parentNode->g + 1;

		auto inds = GetGoalIndex();
		int goalRowInd = get<0>(inds);
		int goalColInd = get<1>(inds);

		int h = abs(goalRowInd - rowIndex) + abs(goalColInd - colIndex);
		node->h = h;
		node->f = node->g + h;
		node->conn = parentNode;
	}

	return node;
}

int main()
{
	ShowMap();

	int startRowInd = 3;
	int startColInd = 3;

	ASNode* startNode = new ASNode(startRowInd, startColInd, 'S', 'S');

	//put open list first
	openList.push_back(startNode);

	FindPath();
}