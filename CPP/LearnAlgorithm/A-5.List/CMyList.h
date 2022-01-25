#pragma once

#include <iostream>


template <typename T>
struct Node
{
	T		m_data;
	Node*	pPrev;
	Node*	 pNext;

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
class CMyList
{
	Node<T>*	pHeadNode; // 노드의 첫번째 주소값
	Node<T>*	pTailNode; // 노드의 마지막 주소값
	int			m_size;    // 리스트에 몇개의 데이터가 들어있는지에 대한 데이터

public:
	CMyList();
	// 복사생성자
	CMyList(const CMyList& target);
	~CMyList();

	void push_back(const T& data); //뒤에 노드를 삽입
	void pop_back(); // 뒤의 노드를 삭제
	void push_front(const T& data); // 앞에 노드를 삽입
	void pop_front(); // 앞의 노드를 삭제

	int size() const; // 크기 반환
	bool empty(); // 리스트가 비어있는지 확인
	void clear(); // 리스트를 비우는 함수

	void print_AllNode(); // 모든 노드를 출력하는 함수

	Node<T> at(int index); // 인덱스의 노드를 반환하는 함수
	// 리스트 [] 연산자
	T operator[](int n) const;
	CMyList<T>& operator=(const CMyList& _other);
	// 리스트의 끝과 다른 리스트의 처음을 연결한 리스트를 반환하는 +연산자 재정의
	CMyList<T> operator+(const CMyList& _other);
	// 리스트의 끝에 다른 리스트의 처음을 연결하는 += 연산자 재정의
	CMyList<T>& operator+=(const CMyList& _other);
};

template<typename T>
CMyList<T>::CMyList()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}
template<typename T>
CMyList<T>::CMyList(const CMyList& target)
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
	Node<T>* temp = target.pHeadNode;
	for (int i = 0; i < target.size(); i++)
	{
		push_back(target[i]);
	}
}

template<typename T>
CMyList<T>::~CMyList()
{
}

template<typename T>
void CMyList<T>::push_back(const T& data)
{

	// 1. 노드 동적할당
	// 2. 새로운 노드에 데이터와 pPrev를 마지막 노드에 연결
	// 3. 마지막 노드의 pNext를 새로운 노드에 연결
	// 4. 새로운 노드를 마지막 노드로 지정
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, pTailNode, nullptr);

		pTailNode->pNext = newNode;
		pTailNode = newNode;
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
void CMyList<T>::pop_back()
{
	if (0 == m_size)
		return;
	else
	{
		Node<T>* newTailNode = pTailNode->pPrev;
		delete pTailNode;
		pTailNode = newTailNode;
	}
	m_size--;
}

template<typename T>
void CMyList<T>::push_front(const T& data)
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
void CMyList<T>::pop_front()
{
	if (m_size == 0)
		return;
	Node<T>* newHeadNode = pHeadNode->pNext;
	delete pHeadNode;
	pHeadNode = newHeadNode;
	m_size--;
}

template<typename T>
int CMyList<T>::size() const
{
	return m_size;
}

template<typename T>
bool CMyList<T>::empty()
{
	return m_size == 0;
}

template<typename T>
void CMyList<T>::clear()
{
	while (pHeadNode != pTailNode)
	{
		pop_back();
	}
	pop_back();
	pHeadNode = nullptr;
}

template<typename T>
void CMyList<T>::print_AllNode()
{
	Node<T>* temp = pHeadNode;
	std::cout << "List Data : ";
	for (int i = 0; i < m_size; i++)
	{
		std::cout << temp->m_data << ", ";
		temp = temp->pNext;
	}
	std::cout << "\tsize : "<< m_size << "\n\n";
}

template<typename T>
Node<T> CMyList<T>::at(int index)
{
	Node<T>* temp = pHeadNode;
	for (int i = 0; i < m_size; i++)
	{
		if (i == index)
		{
			return *temp;
		}
		else
		{
			temp = temp->pNext;
		}
	}
}

template<typename T>
T CMyList<T>::operator[](int n) const
{
	Node<T>* temp = pHeadNode;
	for (int i = 0; i < m_size; i++)
	{
		if (i == n)
		{
			return temp->m_data;
		}
		else
		{
			temp = temp->pNext;
		}
	}
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& _other)
{
	CMyList<T> other(_other);
	return other;
}

template<typename T>
CMyList<T> CMyList<T>::operator+(const CMyList& _other)
{
	CMyList<T> other(_other);
	pTailNode->pNext = other.pHeadNode;
	other.pHeadNode->pPrev = pTailNode;
	this->m_size += other.m_size;
	pTailNode = other.pTailNode;
	return (CMyList<T>)*this;
}

template<typename T>
CMyList<T>& CMyList<T>::operator+=(const CMyList& _other)
{
	CMyList<T> other(_other);
	pTailNode->pNext = other.pHeadNode;
	other.pHeadNode->pPrev = pTailNode;
	this->m_size += other.m_size;
	pTailNode = other.pTailNode;
	// TODO: 여기에 return 문을 삽입합니다.
	return (CMyList<T>)*this;
}
