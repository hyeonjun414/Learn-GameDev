#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

int BestSolution(string s)
{
    // 받아온 문자열에서 정규식에 해당하는 문자를 치환하는 방식을 사용하였다.
    s = regex_replace(s, regex("zero"), "0");
    s = regex_replace(s, regex("one"), "1");
    s = regex_replace(s, regex("two"), "2");
    s = regex_replace(s, regex("three"), "3");
    s = regex_replace(s, regex("four"), "4");
    s = regex_replace(s, regex("five"), "5");
    s = regex_replace(s, regex("six"), "6");
    s = regex_replace(s, regex("seven"), "7");
    s = regex_replace(s, regex("eight"), "8");
    s = regex_replace(s, regex("nine"), "9");
    return stoi(s);
}

int solution(string s) {
    cout << s << endl;
    string temp;
    for (int i = 0; i < s.size(); i++)
    {
        switch (s[i])
        {
        case 'o':
            temp.push_back('1');
            i += 2;
            break;
        case 't':
            if (s[i + 1] == 'w') 
            {
                temp.push_back('2');
                i += 2;
            }
            else if (s[i + 1] == 'h')
            {
                temp.push_back('3');
                i += 4;
            }   
            break;
        case 'f': 
            if (s[i + 1] == 'o')
            {
                temp.push_back('4');
                i += 3;
            }
            else if (s[i + 1] == 'i')
            {
                temp.push_back('5');
                i += 3;
            }
            break;
        case 's': 
            if (s[i + 1] == 'i')
            {
                temp.push_back('6');
                i += 2;
            }
            else if (s[i + 1] == 'e')
            {
                temp.push_back('7');
                i += 4;
            }
            break;
        case 'e': 
            temp.push_back('8');
            i += 4;
            break;
        case 'n': 
            temp.push_back('9');
            i += 3; break;
        case 'z':
            temp.push_back('0');
            i += 3; break;
        default: 
            temp.push_back(s[i]);
            break;

        }
    }
    int answer = stoi(temp);
    return answer;
}

int main()
{
    vector<string> word = { "one4seveneight" ,"23four5six7" ,
                            "2three45sixseven" ,"123" };

    vector<string>::iterator iter;

    for (iter = word.begin(); iter != word.end(); iter++)
    {
        int n = solution(*iter);
        int best = BestSolution(*iter);
        cout << "나의 코드 : " << n << endl;
        cout << "최고의코드 : " << best << endl;
    }
	return 0;
}