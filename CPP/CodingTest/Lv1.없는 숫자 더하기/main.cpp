#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> numbers) {
	int answer = 0;
	for (int i = 0; i < 10; i++)
	{
		if (find(numbers.begin(), numbers.end(), i) != numbers.end())
			continue;
		else
			answer += i;
	}
	return answer;
}

int main()
{
	vector<vector<int>> nums = { {1,2,3,4,6,7,8,0}, {5,8,4,0,6,7,9} };
	vector<vector<int>>::iterator iter;
	for (iter = nums.begin(); iter != nums.end(); iter++)
	{
		cout << solution(*iter) << endl;
	}
	return 0;
}