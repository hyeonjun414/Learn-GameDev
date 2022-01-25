// A-5.List.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <list>
#include <crtdbg.h>
#include "CMyList.h"

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__)
#endif

using namespace std;

int main()
{
	_CrtDumpMemoryLeaks(); // 메모리 릭 확인

	CMyList<int> myList;
	cout << "push_front(15) -> ";
	myList.push_front(15);
	myList.print_AllNode();
	cout << "push_back(10) -> ";
	myList.push_back(10);
	myList.print_AllNode();
	cout << "push_back(20) -> ";
	myList.push_back(20);
	myList.print_AllNode();
	cout << "push_back(30) -> ";
	myList.push_back(30);
	myList.print_AllNode();

	// 인덱스 테스트
	cout << myList[2] << endl;
	// 복사생성자 테스트
	CMyList<int> myList2(myList);
	myList2.print_AllNode();
	myList.print_AllNode();
	myList = myList + myList2;
	myList.print_AllNode();
	myList += myList2;
	myList.print_AllNode();
	cout << "pop_back()    -> ";
	myList.pop_back();
	myList.pop_back();
	myList.pop_back();
	myList.pop_back();
	myList.print_AllNode();
	cout << "pop_front()   -> ";
	myList.pop_front();
	myList.print_AllNode();
	cout << "push_front(100) -> ";
	myList.push_front(100);
	if (myList.empty())
		cout << "빈 리스트입니다." << endl;
	else
		myList.print_AllNode();
	cout << "myList.clear() 실행" << "\n\n";
	myList.clear();
	if (myList.empty())
		cout << "빈 리스트입니다. size : " << myList.size() << endl;
	else
		myList.print_AllNode();
	
}
