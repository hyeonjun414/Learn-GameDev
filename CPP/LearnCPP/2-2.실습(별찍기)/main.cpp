#include <iostream>

using namespace std;

// 별찍기
int main()
{
	int x, y; // x = 3, y = 5
	// 값을 두개 입력받아서 하나는 x축, 하나는 y축 크기의 사각형을 만드시오
	cout << "x축과 y축의 크기를 입력하시오 : ";
	cin >> x >> y;

	//x = 3; y = 5;

	//1번
	for (int i = 0; i < y; i++)
	{
		int j;
		for (j = 0; j < x; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	//2번
	for (int i = 0; i < y; i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	//3번
	for (int i = 0; i < y; i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			cout << " ";
		}
		for (j = i; j < y-1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	//4번
	for (int i = 0; i < y; i++)
	{
		int j;
		for (j = i; j < y-1; j++)
		{
			cout << " ";
		}
		for (j = 0; j < i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	//5번
	if (y % 2 == 0) y ++; // 홀수가 아닐경우 1을 더한다.
	int star = 1;
	int blank = y / 2;
	for (int i = 0; i < y/2+1; i++)
	{

		for (int j = 0; j < blank; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < star; j++)
		{
			cout << "*";
		}
		star += 2;
		blank -= 1;
		cout << endl;
	}
	cout << endl;

	//6번
	star = y;
	blank = 0;
	for (int i = 0; i < y / 2 + 1; i++)
	{

		for (int j = 0; j < blank; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < star; j++)
		{
			cout << "*";
		}
		star -= 2;
		blank += 1;
		cout << endl;
	}

	return 0;
}



