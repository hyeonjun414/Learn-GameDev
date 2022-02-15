// ex1.CMyVector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CMyVector.h"

using namespace std;

int main()
{
	CMyVector<int> vec;

	for (int i = 0; i < 20; i++)
	{
		vec.push_back(i);
	}

	CMyVector<int>::iterator iter;
	for (iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << endl;
	}
}
