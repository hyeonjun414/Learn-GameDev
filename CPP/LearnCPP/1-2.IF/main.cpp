#include <iostream>

using namespace std;

// ���ǹ�
int main()
{
	int x = 1;

	if (x > 10)
	{
		cout << x << "�� 10���� ũ��" << endl;
	}
	else if (x > 5)
	{
		cout << x << "�� 5���� ũ��" << endl;
	}
	else
	{
		cout << x << "�� 5���� �۴�" << endl;
	}

	// 
	if (x > 0 && x < 10)
	{
		cout << x << "�� 10���� ũ��" << endl;
	}
	if (x == 0 || x == 10)
	{
		cout << x << "�� 0�̰ų� 10�̴�." << endl;

	}
	return 0;
}

