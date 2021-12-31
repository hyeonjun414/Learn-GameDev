#include <iostream>

using namespace std;

// 간단한 계산기 만들기
int main()
{
	int n1, n2;
	char c;

	cout << "숫자, 부호(+,-,*,/), 숫자 순으로 입력하시오(스페이스바로 구분) : ";
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
			cout << "0으로는 나눌 수 없습니다.";
		else
			cout << n1 << c << n2 << " = " << (double)n1 / n2;
	}
	cout << endl;
	system("pause");

	return 0;
}

