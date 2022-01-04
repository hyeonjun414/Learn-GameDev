#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int solution(vector<int> citations) {
    int answer = 0;
    // 논문별 인용 횟수를 내림차순으로 정렬한다.
    sort(citations.begin(), citations.end(), greater<int>());
    //제일 큰값이 0이라면 H-index 는 0이다
    if (!citations[0])        return 0;

    for (int i = 0; i < citations.size(); i++) {
        //h-index범위 안이라면 h-index를 하나 늘려준다.
        if (citations[i] > i)    answer++;

        //i가 h-index를 벗어났다면 탐색을 멈춘다.
        else
            break;
    }
    return answer;
}

// 이 문제는 인덱스 값으로 참조횟수를 비교하는 것이 포인트였다.
int main()
{
    vector<int> arr = { 3, 0, 6, 1, 5 };



    cout << "입력 값 :";
    PrintVector(arr);
    cout << "실행 결과 : " << solution(arr);
    return 0;
}