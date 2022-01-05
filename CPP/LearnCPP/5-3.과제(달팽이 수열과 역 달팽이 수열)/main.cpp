#include <iostream>

using namespace std;

// 배열 초기화 함수
void InitArr(int** arr, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			arr[i][j] = 0;
		}
	}
}
// 배열 출력 함수
void PrintArr(int** arr, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl << endl;
	}
	cout << endl;
}
// 달팽이 수열
void Snail(int x, int y)
{
	cout << "************** 달팽이 수열 **************\n\n";
	// 입력한 수치에 따라 2차원 배열을 동적할당한다.
	int** arr = new int* [y];
	for (int i = 0; i < y; i++)
		arr[i] = new int[x];
	InitArr(arr, x, y); // 배열 초기화

	int dir = 0;
	// 0 : 오른쪽, 1 : 아래쪽, 2 : 오른쪽, 3 : 위쪽
	int maxY = y-1, maxX = x; // 진행 최대횟수
	int curY = 0, curX = 0; // 현재 진행방향으로 나아간 횟수
	int indexX=0, indexY=0; // 현재 진행중인 인덱스
	for (int i = 0; i < y*x; i++)
	{
		// 각 방향마다 같은 기능을 한다.
		// 1. 현재 인덱스에 숫자를 넣는다.
		// 2. 현재 진행방향으로 나아간 횟수를 늘리고
		// 2-1.진행횟수가 최대횟수에 도달하면 카운트 관련 변수를 초기화하고 최대횟수를 하나 줄인다.
		//     방향을 다음 방향으로 바꿔준뒤 중복 대입을 방지하기 위해 다음 방향쪽으로 인덱스를 하나 늘린다.
		// 2-2. 그렇지 않다면, 현재 방향으로 인덱스를 하나 늘린다.
		switch (dir)
		{
		case 0 : // 오른쪽으로 진행
			arr[indexY][indexX] = i + 1;
			curX++;
			if (curX == maxX)
			{
				curX = 0;
				maxX--;
				++dir %= 4;
				indexY++;
			}
			else
				indexX++;
			break;

		case 1 : // 아래쪽으로 진행
			arr[indexY][indexX] = i + 1;
			curY++;
			if (curY == maxY)
			{
				curY = 0;
				maxY--;
				++dir %= 4;
				indexX--;
			}
			else
				indexY++;
			break;

		case 2: // 왼쪽으로 진행
			arr[indexY][indexX] = i + 1;
			curX++;
			if (curX == maxX)
			{
				curX = 0;
				maxX--;
				++dir %= 4;
				indexY--;
			}
			else
				indexX--;
			break;

		case 3: // 위쪽으로 진행
			arr[indexY][indexX] = i + 1;
			curY++;
			if (curY == maxY)
			{
				curY = 0;
				maxY--;
				++dir %= 4;
				indexX++;
			}
			else
				indexY--;
			break;

		}
	}
	PrintArr(arr, x, y);
	delete arr;
}
//역 달팽이 수열
void ReverseSnail(int x, int y)
{
	//달팽이 수열에서 이동순서와 개수를 세는 방법만 변경한다.
	cout << "************** 역 달팽이 수열 **************\n\n";
	// 입력한 수치에 따라 2차원 배열을 동적할당하고 초기화한다.
	int** arr = new int* [y];
	for (int i = 0; i < y; i++)
		arr[i] = new int[x];
	InitArr(arr, x, y); // 배열 초기화

	int dir = 0; // 0 : 아래쪽, 1 : 오른쪽, 2 : 위쪽, 3 : 왼쪽
	
	int maxY = y, maxX = x-1; // 진행 최대횟수
	int curY = 0, curX = 0; // 현재 진행방향으로 나아간 횟수
	int indexX = 0, indexY = 0; // 현재 인덱스

	for (int i = 0; i < y * x; i++)
	{
		// 각 방향마다 같은 기능을 한다.
		// 1. 현재 인덱스에 숫자를 넣는다.
		// 2. 현재 진행방향으로 나아간 횟수를 늘리고
		// 2-1.진행횟수가 최대횟수에 도달하면 카운트 관련 변수를 초기화하고 최대횟수를 하나 줄인다.
		//     방향을 다음 방향으로 바꿔준뒤 중복 대입을 방지하기 위해 다음 방향쪽으로 인덱스를 하나 늘린다.
		// 2-2. 그렇지 않다면, 현재 방향으로 인덱스를 하나 늘린다.
		switch (dir)
		{
		case 0: // 아래쪽
			arr[indexY][indexX] = i + 1;
			curY++;
			if (curY == maxY)
			{
				curY = 0;
				maxY--;
				++dir %= 4;
				indexX++;
			}
			else
				indexY++;
			break;
		case 1: // 오른쪽
			arr[indexY][indexX] = i + 1;
			curX++;
			if (curX == maxX)
			{
				curX = 0;
				maxX--;
				++dir %= 4;
				indexY--;
			}
			else
				indexX++;
			break;

		case 2: // 위쪽
			arr[indexY][indexX] = i + 1;
			curY++;
			if (curY == maxY)
			{
				curY = 0;
				maxY--;
				++dir %= 4;
				indexX--;
			}
			else
				indexY--;
			break;

		case 3: // 왼쪽
			arr[indexY][indexX] = i + 1;
			curX++;
			if (curX == maxX)
			{
				curX = 0;
				maxX--;
				++dir %= 4;
				indexY++;
			}
			else
				indexX--;
			break;

		}
	}
	PrintArr(arr, x, y);
	delete arr;
}

int main()
{
	int inputX, inputY;
	cout << "달팽이 배열의 크기를 입력하시오(X, Y) : ";
	cin >> inputX >> inputY;

	Snail(inputX, inputY); // 달팽이 함수
	ReverseSnail(inputX, inputY); // 역 달팽이 함수
	return 0;
}
