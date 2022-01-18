// Lv1.시저 암호.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string s, int n)
{
    string answer = "";
    int c = 0; // char로 처리하면 문자가 꼬이게 된다.
    for (int i = 0; i < s.size(); i++)
    {

        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            c = s[i] + n;
            if (c > 'Z') c -= 26;
            answer += c;

        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            c = s[i] + n;
            if (c > 'z') c -= 26;
            answer += c;
        }
        else
            answer += s[i];
    }
    return answer;
}


int main()
{
    cout << solution("AaEksA Akwdj A", 3) << endl;
}