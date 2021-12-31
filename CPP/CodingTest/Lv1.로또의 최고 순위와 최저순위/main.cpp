#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums)
{
	vector<int> answer = {0, 0};
	vector<int>::iterator iter;

	for (iter=lottos.begin(); iter != lottos.end(); iter++)
	{
		// ���� �ζǹ�ȣ�� 0�̸� ������ �ְ������ ������ �ϳ��� ������.
		if (*iter == 0) answer[0]++;
		// ���� �ζǹ�ȣ�� ���� ��ȣ���� ã�Ƴ��� �ִٸ� �ְ�, ���������� �ϳ��� ������
		else if (find(win_nums.begin(), win_nums.end(), *iter) != win_nums.end())
		{
			answer[0]++;
			answer[1]++;
		}
	}
	// �´� ������ ���� ������ ����.
	for (int i = 0; i < answer.size(); i++)
	{
		switch(answer[i])
		{
		case 6: answer[i] = 1; break;
		case 5: answer[i] = 2; break;
		case 4: answer[i] = 3; break;
		case 3: answer[i] = 4; break;
		case 2: answer[i] = 5; break;
		default: answer[i] = 6; break;
		}
	}

	return answer;
}

int main()
{
	vector<int> lottos = { 44,1,0,0,31,25 };
	vector<int> win_nums = { 31,10,45,1,6,19 };

	vector<int> sln = solution(lottos, win_nums);

	vector<int>::iterator iter;
	for (iter = sln.begin(); iter != sln.end(); iter++)
	{
		cout << *iter << " ";
	}
	
	return 0;
}