// B-3.Dijkstra.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>

#define MAX_SIZE 9
#define INF 99999

using namespace std;

#pragma region Graph Data
int graph[MAX_SIZE][MAX_SIZE] = {
    {  0,  35, INF, INF, 247, INF, INF, INF, INF},
    { 35,   0, 126, INF, INF, 150, INF, INF, INF},
    {INF, 126,   0, 117, INF, 162, 220, INF, INF},
    {INF, INF, 117,   0, INF, INF, INF, INF, INF},
    {247, INF, INF, INF,   0,  82, INF,  98, INF},
    {INF, 150, 162, INF,  82,   0, 154, 120, INF},
    {INF, INF, 220, INF, INF, 154,   0, INF, 106},
    {INF, INF, INF, INF,  98, 120,  INF,  0, INF},
    {INF, INF, INF, INF, INF, INF, 106, INF,   0}
};

int graph1[MAX_SIZE][MAX_SIZE] =
{
    {  0, INF,   2, INF, INF, INF, INF, INF,   9},
    {INF,   0,   7, INF, INF, INF,   2, INF, INF},
    {  2,   7,   0, INF,  10,   8, INF, INF, INF},
    {INF, INF, INF,   0, INF, INF, INF, INF,   3},
    {INF, INF,  10, INF,   0, INF, INF,   6, INF},
    {INF, INF,   8, INF, INF,   0, INF, INF, INF},
    {INF,   2, INF, INF, INF, INF,   0, INF,  11},
    {INF, INF, INF, INF,   6, INF, INF,   0, INF},
    {  9, INF, INF,   3, INF, INF, INF,  11,   0}
};

int graph2[MAX_SIZE][MAX_SIZE] =
{
    {  0,   1, INF, INF, INF, INF,   6, INF, INF},
    {  1,   0, INF, INF, INF, INF, INF, INF,   7},
    {INF, INF,   0, INF, INF,   2, INF,   3, INF},
    {INF, INF, INF,   0, INF, INF, INF, INF,   4},
    {INF, INF, INF, INF,   0,   6, INF, INF, INF},
    {INF, INF,   2, INF,   6,   0, INF, INF,   1},
    {  6, INF, INF, INF, INF, INF,   0, INF, INF},
    {INF, INF,   3, INF, INF, INF, INF,   0, INF},
    {INF,   7, INF,   4, INF,   1, INF, INF,   0}
};

int graph3[MAX_SIZE][MAX_SIZE] =
{
    {  0, INF,   1,   3, INF, INF, INF,   5, INF},
    {INF,   0, INF, INF, INF,   4, INF, INF, INF},
    {INF, INF,   0, INF, INF, INF, INF, INF, INF},
    {  5, INF, INF,   0, INF, INF, INF, INF, INF},
    {INF, INF,   9, INF,   0, INF, INF, INF,   2},
    {  1, INF, INF, INF, INF,   0, INF,   6, INF},
    {INF, INF,   3, INF, INF, INF,   0, INF, INF},
    {INF,   1, INF, INF,   4, INF, INF,   0, INF},
    {INF, INF, INF,   2, INF, INF, INF, INF,   0}
};
#pragma endregion

int getSmallIndex(int distance[], bool visited[])
{
    int min = INF;
    int index = 0;

    // 방문하지 않은 정점들 중 가장 적은 비용을 가진 정점의 인덱스를 반환한다.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start, int graph[][MAX_SIZE])
{
    //출발 정점를 설정한다. -> start
    bool visited[MAX_SIZE] = { false };
    int distance[MAX_SIZE];

    // 출발 정점을 기준으로 각 정점 까지의 최소 비용을 저장한다.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        distance[i] = graph[start][i];
    }

    // 최단 거리를 찾고자 하는 출발 정점을 방문했다고 확인한다.
    visited[start] = true;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        // 방문 하지 않은 정점 중에 가장 비용이 적은 정점을 선택
        int current = getSmallIndex(distance, visited);
        visited[current] = true; // 해당 정점을 방문한 것으로 표시.


        for (int j = 0; j < MAX_SIZE; j++)
        {
            // 각 정점을 돌면서 방문하지 않은 정점에 한하여
            if (!visited[j])
            {
                // 선택된 비용이 적은 정점을 기준으로 탐색된 정점까지 비용을 더한 값이
                // 출발 정점에서의 거리보다 작으면 비용을 더해준다.
                if (distance[current] + graph[current][j] < distance[j])
                {
                    distance[j] = distance[current] + graph[current][j];
                }
            }
        }
    }
    //cout << start + 1 << "번 정점에서 각 정점으로의 최소 비용" << endl;
    //for (int i = 0; i < MAX_SIZE; i++)
    //{
    //    cout << i + 1 << "번 노드 까지의 비용 : " << distance[i] << endl;
    //}
    //cout << endl;

    cout << start + 1 << "번 정점에서 각 노드 최단거리 : ";
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if(distance[i] == INF)
            cout << "X" << ", ";
        else
            cout << distance[i] << ", ";
    }
    cout << endl;
}

// 위와 같이 작성하면 O(n^2)의 시간 복잡도가 나온다.
// 힙구조를 이용하면 O(nlogn)으로 만들 수 있다.

void dijkstar_heap(int start, vector<pair<int, int>> graph[], int d[])
{
    d[start] = 0; // 출발 정점의 비용은 0으로 처리한다.

    // 우선 순위 큐, 힙 구조
    // 우선 순위 큐의 특징 : 각 원소마다 우선 순위를 부여하여 들어간 순서에 상관없이 
    //                      높은 우선순위를 가진 원소가 순서대로 나온다.
    priority_queue<pair<int, int>> pq;

    // 출발 정점은 0의 우선순위를 가진다.
    // 여기서 우선순위는 곧 비용이다.
    pq.push(make_pair(start, 0));

    // 가까운 순서대로 처리하므로 큐를 사용한다.
    while (!pq.empty())
    {
        // 큐에 들어가있는 정점 중 우선순위가 가장 높은 정점
        // 즉, 비용이 가장 적은 정점을 가져온다.
        int current = pq.top().first;
        // 음수로 집어 넣은 비용을 다시 정상화 하여 가져온다.
        int distance = -pq.top().second;
        pq.pop(); // 꺼낸 정점 큐에서 제거한다.

        // 만약 큐에서 꺼내온 정점의 비용이 해당 정점까지의 원래 비용보다 작을때 코드를 진행한다.
        if (d[current] < distance) continue;

        // 출발 정점을 기준으로 모든 정점를 탐색한다.
        for (int i = 0; i < graph[current].size(); i++)
        {
            // 꺼내온 정점을 기준으로 각 정점과 정점의 비용을 가져온다.
            int next = graph[current][i].first;

            // 이때 정점에서 추가로 연결되는 비용이기 때문에
            // 기존에 구한 비용에 더해준다.
            int nextDistance = distance + graph[current][i].second;

            // 최종 비용이 기존 비용보다 작으면
            if (nextDistance < d[next])
            {
                // 비용을 갱신하고
                d[next] = nextDistance;
                // 현재 정점과 비용을 큐에 넣어준다.
                // 비용을 음수로 넣는 이유는 우선순위 큐는 second값이 클수록 먼저 pop되기 때문에
                // 출발 정점을 0으로 잡아 가장 늦게 나오도록하고 비용이 작을 수록 먼저 나올 수 있게 하기 위해
                // 음수로 저장하고 꺼내서 사용할때도 해당 값을 다시 음수로 받아 정상적으로 비용을 사용할 수 있게 한다.
                pq.push(make_pair(next, -nextDistance));
            }
        }
    }

    cout << "Dijkstra Heap" << endl;
    cout << start + 1 << "번 정점에서 각 정점으로의 최소 비용" << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << i + 1 << "번 노드 까지의 비용 : " << d[i] << endl;
    }
}


void heap_base(int start, int graph[][MAX_SIZE])
{
    vector<pair<int, int>> a[MAX_SIZE];
    int d[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        d[i] = INF;
    }

    // 비용의 삽입은 배열상 순서로 진행 하였다.
    // 첫번째 정점 -> a[0];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (graph[i][j] == 0 || graph[i][j] == INF)
                continue;
            a[i].push_back(make_pair(j, graph[i][j]));
        }
    }
   
    dijkstar_heap(start, a, d);

}
int main()
{
    cout << "Graph 최단 거리 탐색 " << endl;
    for (int i = 0; i < MAX_SIZE; i++)
        dijkstra(i, graph);
    cout << endl;

    cout << "Graph 1 최단 거리 탐색 " << endl;
    for (int i = 0; i < MAX_SIZE; i++)
        dijkstra(i, graph1);
    cout << endl;

    cout << "Graph 2 최단 거리 탐색 " << endl;
    for (int i = 0; i < MAX_SIZE; i++)
        dijkstra(i, graph2);
    cout << endl;

    cout << "Graph 3 최단 거리 탐색 " << endl;
    for (int i = 0; i < MAX_SIZE; i++)
        dijkstra(i, graph3);
    cout << endl;

    //heap_base(0, graph);
    //heap_base(2, graph);

}