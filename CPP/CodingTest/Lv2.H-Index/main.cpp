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
    // ex) a�� 33, b�� 34�϶�,
    // 3334 < 3433 b�� �� ũ�Ƿ� ������ �̵��Ѵ�.
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



    cout << "�Է� �� :";
    PrintVector(arr);
    cout << "���� ��� : " << solution(arr);
    return 0;
}