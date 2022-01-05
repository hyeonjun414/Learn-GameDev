#include <iostream>

using namespace std;

// �迭 �ʱ�ȭ �Լ�
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
// �迭 ��� �Լ�
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
// ������ ����
void Snail(int x, int y)
{
	cout << "************** ������ ���� **************\n\n";
	// �Է��� ��ġ�� ���� 2���� �迭�� �����Ҵ��Ѵ�.
	int** arr = new int* [y];
	for (int i = 0; i < y; i++)
		arr[i] = new int[x];
	InitArr(arr, x, y); // �迭 �ʱ�ȭ

	int dir = 0;
	// 0 : ������, 1 : �Ʒ���, 2 : ������, 3 : ����
	int maxY = y-1, maxX = x; // ���� �ִ�Ƚ��
	int curY = 0, curX = 0; // ���� ����������� ���ư� Ƚ��
	int indexX=0, indexY=0; // ���� �������� �ε���
	for (int i = 0; i < y*x; i++)
	{
		// �� ���⸶�� ���� ����� �Ѵ�.
		// 1. ���� �ε����� ���ڸ� �ִ´�.
		// 2. ���� ����������� ���ư� Ƚ���� �ø���
		// 2-1.����Ƚ���� �ִ�Ƚ���� �����ϸ� ī��Ʈ ���� ������ �ʱ�ȭ�ϰ� �ִ�Ƚ���� �ϳ� ���δ�.
		//     ������ ���� �������� �ٲ��ص� �ߺ� ������ �����ϱ� ���� ���� ���������� �ε����� �ϳ� �ø���.
		// 2-2. �׷��� �ʴٸ�, ���� �������� �ε����� �ϳ� �ø���.
		switch (dir)
		{
		case 0 : // ���������� ����
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

		case 1 : // �Ʒ������� ����
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

		case 2: // �������� ����
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

		case 3: // �������� ����
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
//�� ������ ����
void ReverseSnail(int x, int y)
{
	//������ �������� �̵������� ������ ���� ����� �����Ѵ�.
	cout << "************** �� ������ ���� **************\n\n";
	// �Է��� ��ġ�� ���� 2���� �迭�� �����Ҵ��ϰ� �ʱ�ȭ�Ѵ�.
	int** arr = new int* [y];
	for (int i = 0; i < y; i++)
		arr[i] = new int[x];
	InitArr(arr, x, y); // �迭 �ʱ�ȭ

	int dir = 0; // 0 : �Ʒ���, 1 : ������, 2 : ����, 3 : ����
	
	int maxY = y, maxX = x-1; // ���� �ִ�Ƚ��
	int curY = 0, curX = 0; // ���� ����������� ���ư� Ƚ��
	int indexX = 0, indexY = 0; // ���� �ε���

	for (int i = 0; i < y * x; i++)
	{
		// �� ���⸶�� ���� ����� �Ѵ�.
		// 1. ���� �ε����� ���ڸ� �ִ´�.
		// 2. ���� ����������� ���ư� Ƚ���� �ø���
		// 2-1.����Ƚ���� �ִ�Ƚ���� �����ϸ� ī��Ʈ ���� ������ �ʱ�ȭ�ϰ� �ִ�Ƚ���� �ϳ� ���δ�.
		//     ������ ���� �������� �ٲ��ص� �ߺ� ������ �����ϱ� ���� ���� ���������� �ε����� �ϳ� �ø���.
		// 2-2. �׷��� �ʴٸ�, ���� �������� �ε����� �ϳ� �ø���.
		switch (dir)
		{
		case 0: // �Ʒ���
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
		case 1: // ������
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

		case 2: // ����
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

		case 3: // ����
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
	cout << "������ �迭�� ũ�⸦ �Է��Ͻÿ�(X, Y) : ";
	cin >> inputX >> inputY;

	Snail(inputX, inputY); // ������ �Լ�
	ReverseSnail(inputX, inputY); // �� ������ �Լ�
	return 0;
}
