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
		// 현재 로또번호가 0이면 가능한 최고순위의 개수에 하나를 더해줌.
		if (*iter == 0) answer[0]++;
		// 현재 로또번호를 정답 번호에서 찾아내서 있다면 최고, 최저순위에 하나씩 더해줌
		else if (find(win_nums.begin(), win_nums.end(), *iter) != win_nums.end())
		{
			answer[0]++;
			answer[1]++;
		}
	}
	// 맞는 개수에 따른 순위를 지정.
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