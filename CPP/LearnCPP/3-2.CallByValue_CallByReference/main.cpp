#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// �ּ� ����
void SwapByReference(int& input1, int& input2)
{
	int temp;
	temp = input1;
	input1 = input2;
	input2 = temp;
}
void SwapByReference(vector<int>& vec)
{
	sort(vec.begin(), vec.end());
}
// �� ����
void SwapByValue(int input1, int input2)
{
	int temp;
	temp = input1;
	input1 = input2;
	input2 = temp;
}
void SwapByValue(vector<int> vec)
{
	sort(vec.begin(), vec.end());
}
void PrintInt(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}
int main()
{
	vector<int> vec = { 12,74,23,83,57,82,58,10,23 };
	int num1 = 10;
	int num2 = 20;
	int num3 = 10;
	int num4 = 20;

	SwapByValue(num1, num2);
	SwapByReference(num3, num4);
	cout << "num1�� ���� " << num1 << endl;
	cout << "num2�� ���� " << num2 << endl;
	cout << "num3�� ���� " << num3 << endl;
	cout << "num4�� ���� " << num4 << endl;

	SwapByValue(vec);
	PrintInt(vec);
	SwapByReference(vec);
	PrintInt(vec);
	return 0;
}
