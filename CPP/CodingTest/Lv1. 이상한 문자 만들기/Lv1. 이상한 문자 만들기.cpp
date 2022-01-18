// Lv1. 이상한 문자 만들기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string s) {
    string answer = "";
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            count = 0;
        }
        else
        {
            if (count % 2 == 0)
                s[i] = toupper(s[i]);
            else
                s[i] = tolower(s[i]);
            count++;
        }
    }
    return s;
}

int main()
{
    cout << solution("Hello My Games") << endl;
}