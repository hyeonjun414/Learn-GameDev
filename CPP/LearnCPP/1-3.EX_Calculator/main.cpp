#include <iostream>

using namespace std;

// ������ ���� �����
int main()
{
	int n1, n2;
	char c;

	cout << "����, ��ȣ(+,-,*,/), ���� ������ �Է��Ͻÿ�(�����̽��ٷ� ����) : ";
	cin >> n1 >> c >> n2;

	if (c == '+')
	{
		cout << n1 << c << n2 << " = " << n1 + n2;
	}
	else if (c == '-')
	{
		cout << n1 << c << n2 << " = " << n1 - n2;
	}
	else if (c == '*')
	{
		cout << n1 << c << n2 << " = " << n1 * n2;
	}
	else if (c == '/')
	{
		if (n2 == 0)
			cout << "0���δ� ���� �� �����ϴ�.";
		else
			cout << n1 << c << n2 << " = " << (double)n1 / n2;
	}
	cout << endl;
	system("pause");

	return 0;
}

