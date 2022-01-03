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

string solution(vector<int> numbers) {
    string answer = "";
    // 만들어준 비교 함수를 이용해 정렬한다.
    sort(numbers.begin(), numbers.end(), comp);
    for (int i = 0; i < numbers.size(); i++)
    {
        answer += to_string(numbers[i]);
    }
    // 첫번째 문자가 0일때 뒤에 글자도 0이므로 0 하나만 반환한다.
    if (answer[0] == '0') return "0";
    return answer;
}

int main()
{
    vector<int> arr = { 3, 30, 34, 5, 9 };
    vector<int> arr2 = { 0,0,0,0,0, };



    cout << "입력 값 :";
    PrintVector(arr);
    cout << "실행 결과 : " << solution(arr);

    cout << "입력 값 :";
    PrintVector(arr2);
    cout << "실행 결과 : " << solution(arr2);
    return 0;
}