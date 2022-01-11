#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> sizes) {
    for (int i = 0; i < sizes.size(); i++)
    {
        if (sizes[i][0] < sizes[i][1])
        {
            int temp;
            temp = sizes[i][1];
            sizes[i][1] = sizes[i][0];
            sizes[i][0] = temp;
        }
    }
    int w = sizes[0][0];
    int h = sizes[0][1];
    for (int i = 1; i < sizes.size(); i++)
    {
        w = w < sizes[i][0] ? sizes[i][0] : w;
        h = h < sizes[i][1] ? sizes[i][1] : h;
    }

    return w * h;
}

int BestSolution(vector<vector<int>> sizes)
{
    int answer = 0;

    int w = 0, h = 0;
    for (int i = 0; i < sizes.size(); i++)
    {
        // 가로 길이를 볼때 이번 명함 번호의 가로 길이와 세로 길이의 최소값과 비교하여 큰 값을 넣는다.
        // 세로 길이를 볼때도 마찬가지이다.
        w = max(w, min(sizes[i][0], sizes[i][1]));
        h = max(h, max(sizes[i][0], sizes[i][1]));
    }
    answer = w * h;

    return answer;
}


int main()
{
    vector<vector<int>> vec = { {60,50}, {30,70}, {60,30}, {80,40} };
    cout << solution(vec) << endl;
    cout << BestSolution(vec) << endl;
}