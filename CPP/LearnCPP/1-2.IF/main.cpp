#include <iostream>

using namespace std;

// 조건문
int main()
{
	int x = 1;

	if (x > 10)
	{
		cout << x << "는 10보다 크다" << endl;
	}
	else if (x > 5)
	{
		cout << x << "는 5보다 크다" << endl;
	}
	else
	{
		cout << x << "는 5보다 작다" << endl;
	}

	// 
	if (x > 0 && x < 10)
	{
		cout << x << "는 10보다 크다" << endl;
	}
	if (x == 0 || x == 10)
	{
		cout << x << "는 0이거나 10이다." << endl;

	}
	return 0;
}

