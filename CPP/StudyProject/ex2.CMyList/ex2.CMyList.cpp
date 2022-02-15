// ex2.CMyList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CMyList.h"

using namespace std;

int main()
{
	CMyList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.push_back(50);

	list.push_front(10);
	list.push_front(20);
	list.push_front(30);
	list.push_front(40);
	list.push_front(50);

	list.clear();
}
