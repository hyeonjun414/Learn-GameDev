#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T		m_data;
	Node* pPrev;
	Node* pNext;

	Node()
	{
		pPrev = nullptr;
		pNext = nullptr;
	}
	Node(T _data, Node* _prev, Node* _next)
	{
		m_data = _data;
		pPrev = _prev;
		pNext = _next;
	}
};

template <typename T>
class CMyQueue
{
private:
	Node<T>* pHeadNode;
	Node<T>* pTailNode;
	int			m_size;   

public:
	CMyQueue();
	~CMyQueue();
	void	push(T data);
	T		front();
	void	pop();
	int		size();
	void	printAll();
};

template <typename T>
class CMyStack
{
private:
	Node<T>* pHeadNode; 
	Node<T>* pTailNode; 
	int			m_size;  

public:
	CMyStack();
	~CMyStack();
	void	push(T data);
	T		top();
	void	pop();
	int		size();
	void	printAll();

};

template<typename T>
CMyQueue<T>::CMyQueue()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}

template<typename T>
CMyQueue<T>::~CMyQueue()
{
	int tempSize = m_size;
	for (int i = 0; i < tempSize; i++)
		pop();

	pHeadNode = nullptr;
}

template<typename T>
void CMyQueue<T>::push(T data)
{
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, pHeadNode);
		pHeadNode->pPrev = newNode;
		pHeadNode = newNode;
	}
	else
	{
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}

	m_size++;
}

template<typename T>
T CMyQueue<T>::front()
{
	return pHeadNode->m_data;
}

template<typename T>
void CMyQueue<T>::pop()
{
	if (0 == m_size)
		return;

	Node<T>* newTailNode = pTailNode->pPrev;
	delete pTailNode;
	pTailNode = newTailNode;

	m_size--;
}

template<typename T>
int CMyQueue<T>::size()
{
	return m_size;
}

template<typename T>
void CMyQueue<T>::printAll()
{
	Node<T>* temp = pHeadNode;
	std::cout << "Queue Data : ";
	for (int i = 0; i < m_size; i++)
	{
		std::cout << temp->m_data << ", ";
		temp = temp->pNext;
	}
	cout << "\n\n";
}

template<typename T>
CMyStack<T>::CMyStack()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}

template<typename T>
CMyStack<T>::~CMyStack()
{
	int tempSize = m_size;
	for (int i = 0; i < tempSize; i++)
		pop();

	pHeadNode = nullptr;
}

template<typename T>
void CMyStack<T>::push(T data)
{
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, pHeadNode);
		pHeadNode->pPrev = newNode;
		pHeadNode = newNode;
	}
	else
	{
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}

	m_size++;
}

template<typename T>
T CMyStack<T>::top()
{
	return pHeadNode->m_data;
}

template<typename T>
void CMyStack<T>::pop()
{
	if (m_size == 0)
		return;

	Node<T>* newHeadNode = pHeadNode->pNext;
	delete pHeadNode;
	pHeadNode = newHeadNode;

	m_size--;
}

template<typename T>
int CMyStack<T>::size()
{
	return m_size;
}

template<typename T>
void CMyStack<T>::printAll()
{

	Node<T>* temp = pHeadNode;
	std::cout << "Stack Data : ";
	for (int i = 0; i < m_size; i++)
	{
		std::cout << temp->m_data << ", ";
		temp = temp->pNext;
	}
	cout << "\n\n";
}
