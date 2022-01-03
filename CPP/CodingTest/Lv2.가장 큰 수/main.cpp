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

string solution(vector<int> numbers) {
    string answer = "";
    // ������� �� �Լ��� �̿��� �����Ѵ�.
    sort(numbers.begin(), numbers.end(), comp);
    for (int i = 0; i < numbers.size(); i++)
    {
        answer += to_string(numbers[i]);
    }
    // ù��° ���ڰ� 0�϶� �ڿ� ���ڵ� 0�̹Ƿ� 0 �ϳ��� ��ȯ�Ѵ�.
    if (answer[0] == '0') return "0";
    return answer;
}

int main()
{
    vector<int> arr = { 3, 30, 34, 5, 9 };
    vector<int> arr2 = { 0,0,0,0,0, };



    cout << "�Է� �� :";
    PrintVector(arr);
    cout << "���� ��� : " << solution(arr);

    cout << "�Է� �� :";
    PrintVector(arr2);
    cout << "���� ��� : " << solution(arr2);
    return 0;
}