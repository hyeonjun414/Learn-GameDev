#include <iostream>

using namespace std;

// �����
int main()
{
	int x, y; // x = 3, y = 5
	// ���� �ΰ� �Է¹޾Ƽ� �ϳ��� x��, �ϳ��� y�� ũ���� �簢���� ����ÿ�
	cout << "x��� y���� ũ�⸦ �Է��Ͻÿ� : ";
	cin >> x >> y;

	//x = 3; y = 5;

	//1��
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

	//2��
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

	//3��
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
	//4��
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

	//5��
	if (y % 2 == 0) y ++; // Ȧ���� �ƴҰ�� 1�� ���Ѵ�.
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

	//6��
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



