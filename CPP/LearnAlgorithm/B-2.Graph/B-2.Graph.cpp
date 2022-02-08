// B-2.Graph.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>

#define MAX_SIZE 8
using namespace std;

// 대각선을 기준으로 대칭성을 띈다.
bool graph1[MAX_SIZE][MAX_SIZE] = {
        {0, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0}
};

bool graph2[MAX_SIZE][MAX_SIZE] = {
        {0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0}
};

bool graph3[MAX_SIZE][MAX_SIZE] = {
        {0, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0}
};


// 깊이 우선 탐색
// 스택이나 재귀 방식으로 구현
void dfs_inner(int start, bool graph[][MAX_SIZE], bool* visited)
{
    visited[start] = true;
    cout << "visited " << start + 1 << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        // 탐색되는 노드가 방문되지 않고, 현재 노드에서 탐색되는 노드와 연결되어 있다면
        // 탐색되는 노드로 다시 깊이 우선 탐색을 실행한다.
        if (!visited[i] && graph[start][i])
            dfs_inner(i, graph, visited);
    }
}

void dfs(int start, bool graph[][MAX_SIZE])
{
    bool visited[MAX_SIZE] = { false };
    cout << "dfs : " << endl;
    dfs_inner(start, graph, visited);
    cout << endl;
}

// 넓이 우선 탐색
void bfs_inner(int start, bool graph[][MAX_SIZE], bool* visited)
{
    queue<int> bfsQueue;

    // 첫 노드를 탐색 표시 해준다.
    bfsQueue.push(start);
    visited[start] = true;

    // 큐가 빌때까지, 즉 모든 노드를 다 방문할 때까지 반복한다.
    while (!bfsQueue.empty())
    {
        // 큐에서 가장 먼저 들어간 노드의 정보를 가져온다.
        int next = bfsQueue.front();
        // 큐에서 가장 먼저 들어간 노드를 제거한다.
        bfsQueue.pop();
        // 얻어온 노드의 정보를 방문하였다고 출력한다.
        cout << "visited " << next + 1 << endl;

        // 현재 노드에서 연결된 모든 모드를 탐색하며
        // 탐색되는 노드가 방문되어있지 않으면 큐에 집어넣고 방문 표시를 해준다.
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (!visited[i] && graph[next][i])
            {
                bfsQueue.push(i);
                visited[i] = true;
            }
        }
    }
}
void bfs(int start, bool graph[][MAX_SIZE])
{
    bool visited[MAX_SIZE] = { false };
    cout << "bfs : " << endl;
    bfs_inner(start, graph, visited);
    cout << endl;
}

int main()
{
    dfs(0, graph1);
    bfs(0, graph1);

    dfs(0, graph2);
    bfs(0, graph2);

    dfs(0, graph3);
    bfs(0, graph3);
}
