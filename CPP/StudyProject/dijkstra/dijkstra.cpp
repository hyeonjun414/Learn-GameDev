// dijkstra.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 다익스트라 알고리즘
// 1. 다익스트라 알고리즘이란?
//      1). 최단 경로 탐색 알고리즘으로, 특정한 하나의 정점에서 다른 모든 정점으로 가는 최단 경로를 알려준다.
//      2). 간선은 음의 값으로는 존재할 수 없다.
//      3). 최단 거리는 여러 개의 최단 거리로 이루어져있기 때문에 이전까지 구했던 최단 거리 정보를 그대로 사용한다.
// 2. 방법
//      1). 출발 노드를 설정한다.
//      2). 출발 노드를 기준으로 각 노드의 최소 비용을 저장한다.
//      3). 방문하지 않은 노드 중에서 가장 비용이 적은 노드를 선택한다.
//      4). 해당 노드를 거쳐서 특정한 노드로 가능 경우를 고려하여 최소 비용을 갱신한다.
//      5). 위 과정의 3~4번을 반복 수행한다.
// 
// 
// 
//

#include <iostream>
#include <queue>
#include <vector>

#define MAX_SIZE 6
#define M 100
using namespace std;

// 대각선을 기준으로 대칭성을 띈다.
int graph[MAX_SIZE][MAX_SIZE] = {
        {0, 2, 5, 1, M, M},
        {2, 0, 3, 2, M, M},
        {5, 3, 0, 3, 1, 5},
        {1, 2, 3, 0, 1, M},
        {M, M, 1, 1, 0, 2},
        {M, M, 5, M, 2, 0}
};

int getSmallIndex(int d[], bool v[])
{
    int min = M;
    int index = 0;
    // 방문하지 않은 노드를 중 가장 적은 비용을 가진 노드의 인덱스를 반환한다.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (d[i] < min && !v[i])
        {
            min = d[i];
            index = i;
        }
    }
    return index;
}


//      1). 출발 노드를 설정한다.
//      2). 출발 노드를 기준으로 각 노드의 최소 비용을 저장한다.
//      3). 방문하지 않은 노드 중에서 가장 비용이 적은 노드를 선택한다.
//      4). 해당 노드를 거쳐서 특정한 노드로 가능 경우를 고려하여 최소 비용을 갱신한다.
//      5). 위 과정의 3~4번을 반복 수행한다.
void dijkstra(int start, int graph[][MAX_SIZE])
{
    bool visited[MAX_SIZE] = { false };
    int distance[MAX_SIZE];

    // 출발 정점을 기준으로 각 정점 까지의 최소 비용을 저장한다.
    for (int i = 0; i < MAX_SIZE; i++)
    {
        distance[i] = graph[start][i];
    }

    visited[start] = true;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        // 방문 하지 않은 정점 중에 가장 비용이 적은 정점을 선택
        int current = getSmallIndex(distance, visited);
        visited[current] = true; // 해당 정점을 방문한 것으로 표시.

        // 각 정점을 돌면서 방문하지 않은 정점에 한하여
        // 선택된 비용이 적은 정점을 기준으로 탐색된 정점까지 비용을 더한 값이
        // 출발 정점에서의 거리보다 작으면 비용을 더해준다.
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (!visited[j])
            {
                if (distance[current] + graph[current][j] < distance[j])
                {
                    distance[j] = distance[current] + graph[current][j];
                }
            }
        }
    }
    cout << start + 1 << "번 정점에서 각 정점으로의 최소 비용" << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << i + 1 << "번 노드 까지의 비용 : " << distance[i] << endl;
    }
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

void heap_base(int start)
{
    vector<pair<int, int>> graph[MAX_SIZE];
    int d[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        d[i] = M;
    }
   
    // 비용의 삽입은 배열상 순서로 진행 하였다.
    // 첫번째 정점 -> graph[0];
    graph[0].push_back(make_pair(1, 2));
    graph[0].push_back(make_pair(2, 5));
    graph[0].push_back(make_pair(3, 1));

    graph[1].push_back(make_pair(0, 2));
    graph[1].push_back(make_pair(2, 3));
    graph[1].push_back(make_pair(3, 2));


    graph[2].push_back(make_pair(0, 5));
    graph[2].push_back(make_pair(1, 3));
    graph[2].push_back(make_pair(3, 3));
    graph[2].push_back(make_pair(4, 1));
    graph[2].push_back(make_pair(5, 5));

    graph[3].push_back(make_pair(0, 1));
    graph[3].push_back(make_pair(1, 2));
    graph[3].push_back(make_pair(2, 3));
    graph[3].push_back(make_pair(4, 1));

    graph[4].push_back(make_pair(2, 1));
    graph[4].push_back(make_pair(3, 1));
    graph[4].push_back(make_pair(5, 2));

    graph[5].push_back(make_pair(2, 5));
    graph[5].push_back(make_pair(4, 2));

    dijkstar_heap(start, graph, d);



}
int main()
{
    dijkstra(0, graph);
    dijkstra(2, graph);

    heap_base(0);
    heap_base(2);

}
