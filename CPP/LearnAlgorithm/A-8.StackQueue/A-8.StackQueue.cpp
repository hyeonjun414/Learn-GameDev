// A-8.StackQueue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CStackQueue.h"

using namespace std;



int main()
{
	CMyStack<int> myStack;
	myStack.push(1);
	myStack.printAll();
	myStack.push(2);
	myStack.printAll();
	myStack.push(3);
	myStack.printAll();
	myStack.push(4);
	myStack.printAll();
	myStack.push(5);
	myStack.printAll();

	myStack.top();
	myStack.pop();
	myStack.printAll();
	myStack.pop();
	myStack.printAll();
	myStack.pop();
	myStack.printAll();
	myStack.pop();
	myStack.printAll(); 
	myStack.pop();
	myStack.printAll();

	CMyQueue<int> myQueue;
	myQueue.push(1);
	myQueue.printAll();
	myQueue.push(2);
	myQueue.printAll();
	myQueue.push(3);
	myQueue.printAll();
	myQueue.push(4);
	myQueue.printAll();
	myQueue.push(5);
	myQueue.printAll();

	myQueue.front();
	myQueue.pop();
	myQueue.printAll();
	myQueue.pop();
	myQueue.printAll();
	myQueue.pop();
	myQueue.printAll();
	myQueue.pop();
	myQueue.printAll();
	myQueue.pop();
	myQueue.printAll();


}
