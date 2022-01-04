#include <iostream>
#include <string>

using namespace std;

// 계산식 입력 및 숫자 분할 함수
// 공백 처리나 큰 숫자에 따른 오버플로 처리도 같이한다.
void GetNumAndOperator(float& n1, float& n2, char& op)
{
	string str;
	cout << "원하는 계산식을 적으시오(숫자, 연산자, 숫자), 나가길 원하면 0을 입력하세요 : ";
	getline(cin, str);
	if (str == "0")
	{
		cout << "계산기를 종료합니다." << endl;
		exit(0);
	}
	// 공백 포함 방지
	if (find(str.begin(), str.end(), ' ') != str.end())
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
	}
	int i; // 구분자의 인덱스를 구하는 변수
	for (i = 0; i < str.size(); i++)
	{
		if (str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/')
		{
			break;
		}
	}
	// 구분자를 통해 숫자1, 숫자2, 연산자를 구한다.
	string str_n1 = str.substr(0, i);
	string str_n2 = str.substr(i + 1);

	// 너무 긴 숫자를 입력시 자료형의 최대값을 넘을 수 있으므로 이를 방지한다.
	// float의 최대 표현 범위 3.4^38승 -> 38자가 넘으면 방지.
	if (str_n1.length() >= 38 || str_n2.length() >= 38)
	{
		cout << "너무 긴 숫자를 입력하셨습니다. 계산기를 종료합니다." << endl;
		exit(0);
	}
	// 실수형으로 형변환한다.
	n1 = stof(str_n1);
	n2 = stof(str_n2);
	op = str[i];
	


}
// 사칙연산 함수들
float Sum(float a, float b) {
	return a + b;
}
float Sub(float a, float b) {
	return a - b;
}
float Mul(float a, float b) {
	return a * b;
}
float Div(float a, float b) {
	// 0으로 나누는 경우를 방지한다.
	if (b == 0)
	{
		cout << "0으로는 나눌 수 없습니다. -1을 반환합니다." << endl;
		return -1;
	}
	return a / b;
}

// 두 숫자에 대한 계산을 수행하는 함수
float Calculate(float& n1, float& n2, char& op)
{
	// 연산자에 따라 두 숫자사이의 연산을 결정하여
	// 알맞는 함수를 호출한다.
	switch (op)
	{
	case '+': 
		return Sum(n1, n2);
		break;
	case '-': 
		return Sub(n1, n2);
		break;
	case '*': 
		return Mul(n1, n2);
		break;
	case '/': 
		return Div(n1, n2);
		break;
	}
}

// 함수를 이용한 계산기 만들기
int main()
{
	// 숫자와 연산자 변수 선언
	float n1, n2;
	char op;

	// 계산을 종료하고자 할때까지 무한 반복
	while (true)
	{
		GetNumAndOperator(n1, n2, op);
		float result = Calculate(n1, n2, op);
		cout << "계산 결과는 " << result << " 입니다." << endl;
	}
	return 0;
}

