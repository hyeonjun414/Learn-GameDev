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
    bool visited[MAX_SIZE] = {false};
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
    cout << start+1 << "번 정점에서 각 정점으로의 최소 비용" << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << i + 1 << "번 노드 까지의 비용 : " << distance[i] << endl;
    }
}

// 위와 같이 작성하면 O(n^2)의 시간 복잡도가 나온다.
// 힙구조를 이용하면 O(nlogn)으로 만들 수 있다.

void dijkstar_heap(int start, vector<pair<int, int>> graph, int distance[])
{
    distance[start] = 0;
}

void heap_base(int start)
{
    vector<pair<int, int>> heap_graph[7];
    int d[7];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        d[i] = M;
    }

    heap_graph[1].push_back(make_pair(2, 2));
    heap_graph[1].push_back(make_pair(3, 5));
    heap_graph[1].push_back(make_pair(4, 1));
         
    heap_graph[2].push_back(make_pair(1, 2));
    heap_graph[2].push_back(make_pair(3, 3));
    heap_graph[2].push_back(make_pair(4, 2));
         
         
    heap_graph[3].push_back(make_pair(1, 5));
    heap_graph[3].push_back(make_pair(2, 3));
    heap_graph[3].push_back(make_pair(4, 3));
    heap_graph[3].push_back(make_pair(5, 1));
    heap_graph[3].push_back(make_pair(6, 5));
         
    heap_graph[4].push_back(make_pair(1, 1));
    heap_graph[4].push_back(make_pair(2, 2));
    heap_graph[4].push_back(make_pair(3, 3));
    heap_graph[4].push_back(make_pair(5, 1));
         
    heap_graph[5].push_back(make_pair(3, 1));
    heap_graph[5].push_back(make_pair(4, 1));
    heap_graph[5].push_back(make_pair(6, 2));
         
    heap_graph[6].push_back(make_pair(3, 5));
    heap_graph[6].push_back(make_pair(5, 2));

    dijkstar_heap(0, heap_graph, d);

}
int main()
{
    dijkstra(0, graph);
    dijkstra(2, graph);

}
