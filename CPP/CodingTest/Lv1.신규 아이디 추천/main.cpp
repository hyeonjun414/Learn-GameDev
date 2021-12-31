#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string ToLower(string str)
{
	//1. ��� �빮�ڸ� �����Ǵ� �ҹ��ڷ� ġȯ
	for (int i = 0; i < str.size(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

string DeleteWord(string str)
{
	//2. ���ĺ� �ҹ���, ����, -, _, .�� ������ ���ڸ� ����
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
	// 3~4 ��ħǥ ó��
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
	// 5. ���ڿ� ó��
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
	//1. ��� �빮�ڸ� �����Ǵ� �ҹ��ڷ� ġȯ
	//2. ���ĺ� �ҹ���, ����, -, _, .�� ������ ���ڸ� ����
	//3. ��ħǥ�� �ι� �������� ������ �ϳ��� ����
	//4. ��ħǥ�� ó���̳� ���� ��ġ�ϸ� ����
	//5. �� ���ڿ� �̶�� a�� ����
	//6. 16�� �̻��̸� 15���� ���ڸ� ������ ������ ���ڸ� ����
	//6-2. ���ŵ� ������ �������� ��ħǥ��� ����
	//7. ���̵� ���̰� 2�� ���϶�� ������ ���ڸ� ���̵� ���̰� 3�� �ɶ����� �ݺ�
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