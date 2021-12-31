#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string ToLower(string str)
{
	//1. 모든 대문자를 대응되는 소문자로 치환
	for (int i = 0; i < str.size(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

string DeleteWord(string str)
{
	//2. 알파벳 소문자, 숫자, -, _, .를 제외한 문자를 제거
	for (int i = 0; i < str.size();)
	{
		
		if (!((str[i] >= '0' && str[i] <= '9') ||
			(str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] == '-' || str[i] == '_' || str[i] == '.')))
		{
			str.erase(i, 1);
		}
		else
			i++;
	}
	// 3~4 마침표 처리
	for (int i = 0; i < str.size();)
	{

		if (str[i] == '.')
		{
			if (i == 0 || i == str.size()-1)
			{
				str.erase(i, 1);
			}
			else if (str[i+1] == '.')
			{
				str.erase(i, 1);
			}
			else
				i++;
		}
		else
		{
			i++;
		}
	}
	// 5. 빈문자열 처리
	if (str.empty()) str = "aaa";
	return str;
	
}

string LengthCutAndAdd(string str)
{
	if (str.size() > 15)
		str.erase(15);

	if (str[str.size() - 1] == '.') str.erase(str.size() - 1);

	if (str.size() < 3)
	{
		char c = str[str.size() - 1];
		while (str.size() < 3)
		{
			str.push_back(c);
		}
	}
	
	return str;
}

string solution(string new_id) 
{
	//1. 모든 대문자를 대응되는 소문자로 치환
	//2. 알파벳 소문자, 숫자, -, _, .를 제외한 문자를 제거
	//3. 마침표가 두번 연속으로 나오면 하나를 제외
	//4. 마침표가 처음이나 끝에 위치하면 제거
	//5. 빈 문자열 이라면 a를 대입
	//6. 16자 이상이면 15개의 문자를 제외한 나머지 문자를 제거
	//6-2. 제거된 문자의 마지막이 마침표라면 제거
	//7. 아이디 길이가 2자 이하라면 마지막 문자를 아이디 길이가 3이 될때까지 반복
	string tempNewId;
	cout << new_id << endl;
	tempNewId = ToLower(new_id);
	tempNewId = DeleteWord(tempNewId);
	tempNewId = LengthCutAndAdd(tempNewId);

	return tempNewId;
}

int main()
{
	vector<string> input = { "...!@BaT#*..y.abcdefghijklm" ,	"z-+.^." ,	"=.=" ,	"123_.def" ,	"abcdefghijklmn.p" };

	for (int i = 0; i < input.size(); i++)
	{
		solution(input[i]);
	}

	return 0;
}