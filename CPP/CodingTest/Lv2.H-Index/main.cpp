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

bool comp(int a, int b)
{
    string sa = to_string(a);
    string sb = to_string(b);
    // ex) a가 33, b가 34일때,
    // 3334 < 3433 b가 더 크므로 앞으로 이동한다.
    if (sa + sb > sb + sa)
        return true;
    return false;
}


int solution(vector<int> citations) {
    int answer = 0;
    return answer;
}
int main()
{
    vector<int> arr = { 3, 0, 6, 1, 5 };



    cout << "입력 값 :";
    PrintVector(arr);
    cout << "실행 결과 : " << solution(arr);
    return 0;
}