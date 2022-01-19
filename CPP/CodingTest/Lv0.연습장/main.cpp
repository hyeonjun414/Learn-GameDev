#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
	float num1, num2, result = 0;
	string s = "115+1312/123*123-52";
	float result = 0;
	int i=0, start=0;
	char op;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] == '+' || s[i] == '-' ||
			s[i] == '*' || s[i] == '/')
		{
			op = s[i];
			switch (op)
			{
			case '+':
				result += stof(s.substr(start, i));
				break;
			case '-':
				result -= stof(s.substr(0, i));
				break;
			case '*':
				result *= stof(s.substr(0, i));
				break;

			case '/':
				if (num2 == 0)
					cout << "0으로는 나눌 수 없습니다." << endl;
				else
					result /= stof(s.substr(0, i));
				break;
			}
			break;
		}
			
	}
	
	num1 = stof(s.substr(0, i));
	num2 = stof(s.substr(i + 1));
	
	switch (op)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;

	case '/':
		if (num2 == 0)
			cout << "0으로는 나눌 수 없습니다." << endl;
		else
			result = num1 / num2;
		break;
	}
	cout << result << endl;
}