#include <iostream>

using namespace std;

// 반복문
int main()
{
	for (int i = 1; i <= 100; i++)
	{
		if (i % 2 == 0)
			cout << i << " ";
	}

	cout << endl;

	// 이중 반복문
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << "번째 :";
		for (int j = 0; j < 3; j++)
		{
				cout << "안녕";
		}
		cout << endl;
	}
	// 별찍기
// 1. 좌측 직각 삼각형
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// 2. 우측 직각 삼각형
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = i; j < 10; j++)
		{
			cout << " ";
		}
		for (j = 0; j < i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// 3. 뒤집어진 좌측 직각 삼각형
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = i; j < 10; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// 4. 뒤집어진 우측 직각 삼각형
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			cout << " ";
		}
		for (j = i; j < 10; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	int diamondNum;
	cout << "다이아 최대 크기 : ";
	cin >> diamondNum;
	int star = 1;
	int blank = diamondNum / 2;
	// 5. 다이아 찍기
	for (int i = 0; i < diamondNum; i++)
	{

		for (int j = 0; j < blank; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < star; j++)
		{
			cout << "*";
		}
		if (i < diamondNum / 2)
		{
			star += 2;
			blank -= 1;
		}
		else
		{
			star -= 2;
			blank += 1;
		}
		cout << endl;
	}
	return 0;
}

