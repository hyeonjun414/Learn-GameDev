#include <iostream>
#include <string>

using namespace std;

// ���� �Է� �� ���� ���� �Լ�
// ���� ó���� ū ���ڿ� ���� �����÷� ó���� �����Ѵ�.
void GetNumAndOperator(float& n1, float& n2, char& op)
{
	string str;
	cout << "���ϴ� ������ �����ÿ�(����, ������, ����), ������ ���ϸ� 0�� �Է��ϼ��� : ";
	getline(cin, str);
	if (str == "0")
	{
		cout << "���⸦ �����մϴ�." << endl;
		exit(0);
	}
	// ���� ���� ����
	if (find(str.begin(), str.end(), ' ') != str.end())
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
	}
	int i; // �������� �ε����� ���ϴ� ����
	for (i = 0; i < str.size(); i++)
	{
		if (str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/')
		{
			break;
		}
	}
	// �����ڸ� ���� ����1, ����2, �����ڸ� ���Ѵ�.
	string str_n1 = str.substr(0, i);
	string str_n2 = str.substr(i + 1);

	// �ʹ� �� ���ڸ� �Է½� �ڷ����� �ִ밪�� ���� �� �����Ƿ� �̸� �����Ѵ�.
	// float�� �ִ� ǥ�� ���� 3.4^38�� -> 38�ڰ� ������ ����.
	if (str_n1.length() >= 38 || str_n2.length() >= 38)
	{
		cout << "�ʹ� �� ���ڸ� �Է��ϼ̽��ϴ�. ���⸦ �����մϴ�." << endl;
		exit(0);
	}
	// �Ǽ������� ����ȯ�Ѵ�.
	n1 = stof(str_n1);
	n2 = stof(str_n2);
	op = str[i];
	


}
// ��Ģ���� �Լ���
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
	// 0���� ������ ��츦 �����Ѵ�.
	if (b == 0)
	{
		cout << "0���δ� ���� �� �����ϴ�. -1�� ��ȯ�մϴ�." << endl;
		return -1;
	}
	return a / b;
}

// �� ���ڿ� ���� ����� �����ϴ� �Լ�
float Calculate(float& n1, float& n2, char& op)
{
	// �����ڿ� ���� �� ���ڻ����� ������ �����Ͽ�
	// �˸´� �Լ��� ȣ���Ѵ�.
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

// �Լ��� �̿��� ���� �����
int main()
{
	// ���ڿ� ������ ���� ����
	float n1, n2;
	char op;

	// ����� �����ϰ��� �Ҷ����� ���� �ݺ�
	while (true)
	{
		GetNumAndOperator(n1, n2, op);
		float result = Calculate(n1, n2, op);
		cout << "��� ����� " << result << " �Դϴ�." << endl;
	}
	return 0;
}

