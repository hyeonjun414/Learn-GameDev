#include <iostream>

using namespace std;

// �ݺ���
int main()
{
	for (int i = 1; i <= 100; i++)
	{
		if (i % 2 == 0)
			cout << i << " ";
	}

	cout << endl;

	// ���� �ݺ���
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << "��° :";
		for (int j = 0; j < 3; j++)
		{
				cout << "�ȳ�";
		}
		cout << endl;
	}
	// �����
// 1. ���� ���� �ﰢ��
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// 2. ���� ���� �ﰢ��
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
	// 3. �������� ���� ���� �ﰢ��
	for (int i = 0; i < 10; i++)
	{
		int j;
		for (j = i; j < 10; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// 4. �������� ���� ���� �ﰢ��
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
	cout << "���̾� �ִ� ũ�� : ";
	cin >> diamondNum;
	int star = 1;
	int blank = diamondNum / 2;
	// 5. ���̾� ���
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

