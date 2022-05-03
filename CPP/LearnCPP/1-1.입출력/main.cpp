#include <iostream>

using namespace std;

//입출력
int main()
{
	//int n;

	//cout << "Hello World!" << endl << "숫자를 입력하세요 : ";
	//cin >> n;

	//cout << "입력 결과 : " << n << endl;

	//return 0;
	int* p = new int[5]{ 1,2,4,8,16 };
	int value1 = p[4] - p[1];
	int value2 = (p + 4) - (p + 1);
	int value3 = (long)(p + 4) - (long)(p + 1);

	cout << value1 + value2 + value3 << endl;
	cout << (p+4) - (p+2) << endl;
	cout << value1 << endl;
	cout << value2 << endl;
	cout << value3 << endl;

	int total = 0;

	for (size_t i = 1; i <= 10; i++)
	{
		if (i % 2) continue;
		for (size_t j = 1; j <= 10; j++)
		{
			for (size_t k = 0; k <=10; k++)
			{
				total += i == j && j == k ? i : 0;
			}
		}
	}
	cout << total;
}