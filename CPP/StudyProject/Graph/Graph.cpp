// Graph.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 1. 그래프의 개념
//      정점과 간선으로 이루어진 자료구조로 정점간의 관계를 표현하는 조직도라 볼 수 있다.
//      인접행렬과 인접리스트 방식으로 구현될 수 있지만, 주로 인접리스트 방식을 많이 이용한다.
// 2. 인접행렬 장. 단점
//      장점 : 2차원 배열안에 모든 정점들의 간선 정보를 담기 때문에 배열의 위치를 확인하면 정보를 조회할떄 O(1)의 시간 복잡도를 가진다.
//             구현이 비교적 단순하다.
//      단점 : 모든 정점에 대해 간선 정보를 대입해야 하므로 O(n^2)의 시간복잡도가 소요된다.
//             무조건 2차원 배열이 필요하기에 필요 이상의 공간이 낭비된다.
// 
// 3. 인접리스트 장. 단점
//      장점 : 정점들의 연결 정보를 탐색할때 O(n)의 시간이면 가능하다.
//             필요한 만큼의 공간만 사용하여 공간의 낭비가 적다.
//      단점 : 특정 두 점이 연결되었는지 확인하려면 인접행렬에 비해 시간이 걸린다.
//             구현이 어렵다.
// 4. 그래프 종류
//      1) 무방향 그래프 : 두 정점을 연결하는 간선에 방향이 없는 그래프이다.
//      2) 방향 그래프 : 두 정점을 연결하는 간선에 방향이 존재하는 그래프이다.
//      3) 가중치 그래프 : 두 정점을 이동할 때 비용이 드는 그래프이다.
//      4) 완전 그래프 : 모든 정점이 간선으로 연결되어 있는 그래프
// 5. 그래프의 탐색
//      1) 깊이 우선 탐색(DFS) : 갈 수 잇는 만큼 최대한 깊이 가고 더 이상 갈 곳이 없다면 이전 정점으로 돌아가는 방식.
//                              재귀호출이나 스택을 사용하여 구현한다.
//      2) 넓이 우선 탐색(BFS) : 시작 정점을 방문한 후 시작 정점에 인접한 모든 정점을 방문한 후 시작 정점에 인접한 모든 정점을 우선 방문하는 방법.
//                              큐을 이용하여 지금 위치에서 갈 수 있는 것들을 모두 큐에 넣는 방식으로 구현한다.
//
#include <iostream>

#include <vector>

using namespace std;

const int MAX = 1050;
int n, m;
vector<int> v[MAX];
bool check_dfs[MAX];

//DFS Search
void DFS(int index) {
    check_dfs[index] = true; //정점 방문 체크
    printf("%d ", index); //방문한 정점 출력

    for (int i = 0; i < v[index].size(); i++) {
        int next = v[index][i];

        if (!check_dfs[next]) { //방문하지 않았다면 DFS() 호출
            DFS(next);
        }
    }
}

int main() {

    cin >> n >> m;
    //그래프 노드관계 입력
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        v[a].push_back(b);
        v[b].push_back(a);
    }

    DFS(0);

    return 0;
}