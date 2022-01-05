#include <iostream>

using namespace std;

const int MAX_COUNT = 3;

// 배열
int main()
{
	// 배열 : 같은 데이터 타입의 집합이고 메모리상에서 연속적이다.
	// 정수형 배열
	int inputsA[MAX_COUNT]; // 1차원 배열
	// 2차원 배열
	int inputsB[3][3] = {{10,20,30},
						 {40,50,60},
	                     {70,80,90}, };
	int inputsC[5][5] = {
		{2,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,2} };

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (inputsC[y][x] == 0)
				cout << "  ";
			if (inputsC[y][x] == 1)
				cout << "■";
			if (inputsC[y][x] == 2)
				cout << "□";
		}
		cout << endl;
	}

	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i = 0; i < 10; i++)
	{
		cout << &(arr[i]) << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << *(arr + i) << endl;
	}
	cout << *arr << endl;

	int arr2[2][5] = {1,2,3,4,5,6,7,8,9,10};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << arr2[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i < 10; i++)
	{
		cout << **arr2 + i << " ";
	}

	cout << "arr : " << arr2 << endl;
	cout << &arr2[0] << endl;

	cout << "*arr : " << *arr2 << endl;
	cout << arr2[0] << endl;
	cout << &arr2[0][0] << endl;
	cout << "**arr : " << **arr2 << endl;
	cout << arr2[0][0] << endl; // 1

	cout << **arr2 + 7 << endl;
	cout << arr2[1][2] << endl;
	cout << *(*(arr2 + 1) + 2) << endl;

	// arr + 1은 주소가 20씩
	// *arr +1은 주소가 4씩

	return 0;
}
