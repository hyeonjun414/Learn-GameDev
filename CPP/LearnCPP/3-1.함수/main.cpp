#include <iostream>

using namespace std;

// 함수의 선언과 정의
// 함수는 반환타입, 함수명, 매개변수로 구성된다.
void Func1()
{
	cout << "함수 테스트" << endl;
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
