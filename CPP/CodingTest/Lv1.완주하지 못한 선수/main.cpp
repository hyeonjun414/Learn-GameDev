#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

string solution(vector<string> participant, vector<string> completion) {

    // 두 벡터를 먼저 정렬한다.
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    // 완주한 사람 벡터의 크기만큼 반복한다.

    for (int i = 0; i < completion.size(); i++)
    {
        //똑같이 정렬했는데 순서가 다르다면 그 사람이 완주하지 못한 사람이다.
        if (participant[i] != completion[i])
            return participant[i]; // 바로 반환
    }
    // 완주한 사람을 다 확인했는데 없다면 마지막 한사람이 통과하지 못한 것이다.
    return participant[participant.size() - 1];
}

int main()
{
    vector<string> part = { "marina", "josipa", "nikola", "vinko", "filipa" };
    vector<string> comp = { "josipa", "filipa", "marina", "nikola" };
    cout << "참가자 :"; 
    PrintVector(part);
    cout << "완주자 :";
    PrintVector(comp);

    cout << "완주하지 못한 사람 : " << solution(part, comp);
    return 0;
}