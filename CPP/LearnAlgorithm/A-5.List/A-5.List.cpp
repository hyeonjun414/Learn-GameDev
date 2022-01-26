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
	myList.printAll();
	cout << "push_back(10) -> ";
	myList.push_back(10);
	myList.printAll();
	cout << "push_back(20) -> ";
	myList.push_back(20);
	myList.printAll();
	cout << "push_back(30) -> ";
	myList.push_back(30);
	myList.printAll();

	// 인덱스 테스트
	cout << "myList[2] -> ";
	cout << myList[2] << "\n\n";
	// 복사생성자 테스트
	cout << "myList 복사생성 -> ";

	CMyList<int> myList2(myList);
	cout << "myList -> ";
	myList.printAll();
	cout << "myList2 -> ";
	myList2.printAll();
	cout << "myList = myList + myList2 -> ";
	myList = myList + myList2;
	myList.printAll();
	cout << "myList += myList2 ->";
	myList += myList2;

	myList.printAll();
	cout << "pop_back() * 4    -> ";
	myList.pop_back();
	myList.pop_back();
	myList.pop_back();
	myList.pop_back();
	myList.printAll();
	cout << "pop_front()   -> ";
	myList.pop_front();
	myList.printAll();
	cout << "push_front(100) -> ";
	myList.push_front(100);
	if (myList.empty())
		cout << "빈 리스트입니다." << endl;
	else
		myList.printAll();
	cout << "myList.clear() 실행" << "\n\n";
	myList.clear();
	if (myList.empty())
		cout << "빈 리스트입니다. size : " << myList.size() << endl;
	else
		myList.printAll();
	
}
