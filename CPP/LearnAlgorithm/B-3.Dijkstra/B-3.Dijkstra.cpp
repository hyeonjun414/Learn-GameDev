// B-3.Dijkstra.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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

#define MAX_SIZE 6
#define M 100
using namespace std;

// 대각선을 기준으로 대칭성을 띈다.
int graph[MAX_SIZE][MAX_SIZE] = {
        {0, 2, 5, 1, M, M},
        {2, 0, 3, 2, M, M},
        {5, 3, 0, 3, 1, 5},
        {1, 2, 3, 0, 1, M},
        {M, M, 5, 1, 0, 2},
        {M, M, 5, M, 2, 0}
};

int getSmallIndex(int d[], bool v[])
{
    int min = M;
    int index = 0;
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

void dijkstra(int start, int graph[][MAX_SIZE])
{
    bool visited[MAX_SIZE];
    int distance[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        distance[i] = graph[start][i];
    }

    visited[start] = true;
    for (int i = 0; i < MAX_SIZE -2; i++)
    {
        int current = getSmallIndex(distance, visited);
        visited[current] = true;
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
}

int main()
{
    std::cout << "Hello World!\n";
}
