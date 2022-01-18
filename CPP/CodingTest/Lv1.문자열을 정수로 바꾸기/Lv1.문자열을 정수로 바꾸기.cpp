// Lv1.문자열을 정수로 바꾸기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string s) {
  
    int answer = 1;
    int i = 0;
    if (s[0] == '+' || s[0] == '-')
    {
        if (s[0] == '-')
            answer *= -1;
        i = 1;
    }
    answer *= atoi(s.substr(i, s.size()).c_str());
    // stoi나 atoi는 모두 부호를 포함해서 변경해준다.
    //answer = stoi(s);
    return answer;
}

int main()
{
    cout << solution("-12231") << endl;
}