#include <iostream>

using namespace std;

const int MAX_COUNT = 3;

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int main()
{
	// ������ ���� : �ּҸ� ��� ����
	// ������ ���� ��´�.

	int num = 10;
	// ������ ������ ����
	int* numPtr;
	numPtr = &num;

	cout << "num�� �� : " << num << endl;
	cout << "num�� �� : " << &num << endl;
	cout << "numPtr�� : " << numPtr << endl;
	cout << "numPtr�� �ּ� : " << &numPtr << endl;
	cout << "numPtr�� ����Ű�� �� : " << *numPtr << endl;

	// ������ �����տ� �ٴ� *�����ڴ� �ش� �����ͺ����� ������ �ִ� �ּҾ��� ���� ��������
	int num1 = 10, num2 = 20;

	cout << "Swap ���� : " << num1 << ',' << num2 << endl;
	Swap(&num1, &num2);
	cout << "Swap ���� : " << num1 << ',' << num2 << endl;
	return 0;
}
