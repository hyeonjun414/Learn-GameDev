#include <iostream>

using namespace std;

// �Լ��� ����� ����
// �Լ��� ��ȯŸ��, �Լ���, �Ű������� �����ȴ�.
void Func1()
{
	cout << "�Լ� �׽�Ʈ" << endl;
}

int Sum(int input1, int input2)
{
	return input1 + input2;
}
float Sum(float input1, float input2)
{
	return input1 + input2;
}



void DrawStar(int input = 1)
{
	for (int i = 0; i < input; i++)
	{
		cout << "*";
	}
	cout << endl;
}
int main()
{
	Sum(115, 23);
	Func1();

	DrawStar(50);
	DrawStar();

	return 0;
}
