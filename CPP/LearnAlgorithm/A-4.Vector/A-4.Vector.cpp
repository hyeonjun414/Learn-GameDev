// A-4.Vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "CMyVector.h"

using namespace std;

template <typename T>
void print_vectorData(vector<T> vec)
{
	cout << "vector data : ";
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ", ";
	}
	cout << endl;
}
template <typename T>
void print_vectorData(CMyVector<T> vec)
{
	cout << "vector data : ";
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << ", ";
	}
	cout << endl;
}


int main()
{
	CMyVector<int> myVector;

	for (int i = 0; i < 100; i++)
	{
		myVector.push_back(i);
		cout << "vector : size, capacity : " << myVector.size() << ", " << myVector.capacity() << endl;
	}
	for (int i = 0; i < 100; i++)
	{
		myVector.pop_back();
		cout << "vector : size, capacity : " << myVector.size() << ", " << myVector.capacity() << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		myVector.push_back(i);
		cout << "vector : size, capacity : " << myVector.size() << ", " << myVector.capacity() << endl;
	}
	cout << myVector[5] << endl;
	cout << myVector.at(5) << endl;

	CMyVector<int> myVector2;
	myVector2 = myVector;
	CMyVector<int> myVector3 = myVector;

	if (myVector == myVector2)
	{
		cout << "같습니다." << endl;
	}
	else
		cout << "다릅니다." << endl;

	if (myVector == myVector3)
	{
		cout << "같습니다" << endl;
	}
	else
		cout << "다릅니다." << endl;
	
	print_vectorData(myVector);
	print_vectorData(myVector2);
	for (int i = 0; i < 10; i++)
	{
		myVector.push_back(i);
		cout << "vector : size, capacity : " << myVector.size() << ", " << myVector.capacity() << endl;
	}
	print_vectorData(myVector);
	print_vectorData(myVector2);

}
