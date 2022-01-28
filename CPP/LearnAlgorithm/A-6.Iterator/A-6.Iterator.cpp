// A-6.Iterator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include "CMyVector.h"

using namespace std;

int main()
{
#pragma region iterTest
	//vector<int> stlVector;
//stlVector.push_back(10);
//stlVector.push_back(20);
//stlVector.push_back(30);
//stlVector.push_back(40);
//stlVector.push_back(50);

//cout << "vetor data : ";
//for (int i = 0; i < stlVector.size(); i++)
//{
//	cout << stlVector[i] << ", ";
//}
//cout << endl;

//list<int> stlList;
//stlList.push_back(10);
//stlList.push_back(20);
//stlList.push_back(30);
//stlList.push_back(40);
//stlList.push_back(50);
//cout << "vetor data : ";
//list<int>::iterator listIter;
//for (listIter = stlList.begin(); listIter != stlList.end(); listIter++)
//{
//	cout << *listIter << ", ";
//}
//cout << endl;
//// 1. 자료구조의 데이터를 가르키고 있다.
//// 2. 자료구조의 데이터를 가르키고 있는데, --, ++을 통해서 이전의 데이터나 이후의 데이터에 접근한다.
//// 3. 같은 자료를 가르키는 iterator는 같은 iterator라고 본다.
//// 4. iterator가 가르키고 있는 데이터를 * 역참조로 가져올 수 있다.

//set<int> stlSet;
//stlSet.insert(10);
//stlSet.insert(20);
//stlSet.insert(30);
//stlSet.insert(40);
//stlSet.insert(50);
//stlSet.insert(60);
//stlSet.insert(70);
//stlSet.insert(80);
//stlSet.insert(90);
//stlSet.insert(100);
//cout << "set data : ";
//set<int>::iterator setIter;
//for (setIter = stlSet.begin(); setIter != stlSet.end(); setIter++)
//{
//	cout << *setIter << ", ";
//}
//cout << endl;

//map<int, int> stlMap;
//stlMap.insert(make_pair(10, 10));
//stlMap.insert(make_pair(20, 20));
//stlMap.insert(make_pair(30, 30));
//stlMap.insert(make_pair(40, 40));
//stlMap.insert(make_pair(50, 50));
//cout << "set data : ";
//map<int, int>::iterator mapIter;
//for (mapIter = stlMap.begin(); mapIter != stlMap.end(); mapIter++)
//{
//	cout << mapIter->first << ", ";
//}
//cout << endl;
#pragma endregion

	CMyVector<int> myVector;

	for (int i = 0; i < 10; i++)
	{
		myVector.push_back(i);
		cout << myVector[i] << ", " ;
		cout << "vector : size, capacity : " << myVector.size() << ", " << myVector.capacity() << endl;
	}

	CMyVector<int>::iterator iter = myVector.begin();
	cout << "myVector.begin() 으로 시작" << endl;
	cout << "iter == iter : " << (iter == iter) << endl;
	cout << "iter != iter : " << (iter != iter) << endl;
	cout << "iter == iter++ : " << (iter == iter++) << endl;
	cout << "iter != iter++ : " << (iter != iter++) << endl;
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.insert(iter, 10);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	myVector.erase(iter);
	cout << "myVector Data : ";
	for (iter=myVector.begin(); iter != myVector.end(); iter++)
	{
		cout << *iter << ", ";
	}
	cout << endl;
	myVector.insert(iter, 10);
	CMyVector<int>::iterator iter2 = iter;
	cout << "iter == iter2 : " << (iter == iter2) << endl;
}
