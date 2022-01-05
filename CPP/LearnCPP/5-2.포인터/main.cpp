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
	// 포인터 변수 : 주소를 담는 변수
	// 변수는 값을 담는다.

	int num = 10;
	// 포인터 변수의 선언
	int* numPtr;
	numPtr = &num;

	cout << "num의 값 : " << num << endl;
	cout << "num의 값 : " << &num << endl;
	cout << "numPtr값 : " << numPtr << endl;
	cout << "numPtr의 주소 : " << &numPtr << endl;
	cout << "numPtr가 가리키는 값 : " << *numPtr << endl;

	// 포인터 변수앞에 붙는 *연산자는 해당 포인터변수가 가지고 있는 주소안의 값을 가져오라
	int num1 = 10, num2 = 20;

	cout << "Swap 이전 : " << num1 << ',' << num2 << endl;
	Swap(&num1, &num2);
	cout << "Swap 이후 : " << num1 << ',' << num2 << endl;
	return 0;
}
