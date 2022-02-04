// A-9.BST.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CMyBST.h"

using namespace std;

int main()
{
	CMyBST<int> myBST;
	myBST.insert(10);
	myBST.insert(2);
	myBST.insert(8);
	myBST.insert(17);
	myBST.insert(20);
	myBST.printAll();

	CMyBST<int>::iterator iter = myBST.begin();
	CMyBST<int>::iterator iterEnd = myBST.end();
	iter = myBST.erase(iter);
	iter = myBST.erase(iter);
	iter = myBST.erase(iter);
	myBST.printAll();
	iter = myBST.erase(iter);
	iter = myBST.erase(iter);
	myBST.printAll();
	//for (iter = myBST.begin(); iter != iterEnd;)
	//{
	//	iter = myBST.erase(iter);
	//}

}
