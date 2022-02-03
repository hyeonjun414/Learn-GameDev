#pragma once

#include <iostream>

#include<assert.h>


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

	void printAll(); // 모든 노드를 출력하는 함수

	Node<T> at(int index); // 인덱스의 노드를 반환하는 함수
	// 리스트 [] 연산자
	T operator[](int n) const;
	CMyList<T>& operator=(const CMyList& _other);
	// 리스트의 끝과 다른 리스트의 처음을 연결한 리스트를 반환하는 +연산자 재정의
	CMyList<T> operator+(const CMyList& _other);
	// 리스트의 끝에 다른 리스트의 처음을 연결하는 += 연산자 재정의
	CMyList<T>& operator+=(const CMyList& _other);

	class iterator
	{
		friend CMyList; // CMyList 클래스가 iterator 클래스의 속성을 자유롭게 사용가능하다.
	private:
		CMyList*	pList; 
		Node<T>*	pNode;
		bool		isEnd;

	public:
		iterator();
		iterator(CMyList* pList, Node<T>* pNode);
		iterator(CMyList* pList, Node<T>* pNode, bool isEnd);
		T& operator*();
		iterator& operator++();
		iterator	operator++(int);
		iterator& operator--();
		iterator	operator--(int);
		bool		operator==(const iterator& _other);
		bool		operator!=(const iterator& _other);
		iterator& operator=(const iterator& _other);

	};
	iterator begin();
	iterator end();


	// +a 개인공부
	void insert(iterator& iter, const T& value);
	void erase(iterator& iter);
};

#pragma region List함수들
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

	for (int i = 0; i < target.size(); i++)
	{
		push_back(target[i]);
	}
}

template<typename T>
CMyList<T>::~CMyList()
{
	clear();
}

template<typename T>
void CMyList<T>::push_back(const T& data)
{
	// 1. 새로운 노드를 만들어서 data, 이전 노드로는 리스트의 끝노드,
	//    다음 노드로는 널포인트를 가리키도록 만든다.
	// 2. 리스트의 끝 노드의 다음 노드를 새로운 노드로 지정한다.
	// 3. 리스트의 끝 노드를 새로운 노드로 지정한다.
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, pTailNode, nullptr);

		pTailNode->pNext = newNode;
		pTailNode = newNode;
	}
	else
	{
		// 처음 들어가는 노드인 경우 해당 노드를
		// 리스트의 첫 노드와 끝 노드로 지정해준다.
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	// 리스트의 크기를 하나 늘려준다.
	m_size++;
}

template<typename T>
void CMyList<T>::pop_back()
{
	// 리스트에 데이터가 없다면 함수를 반환한다.
	if (0 == m_size)
		return;

	// 1. 새로운 노드를 만들고 리스트 끝 노드의 이전 노드를 받아준다.
	// 2. 끝 노드를 메모리 해제한다.
	// 3. 새로운 노드를 리스트의 끝 노드로 지정한다.
	Node<T>* newTailNode = pTailNode->pPrev;
	delete pTailNode;
	pTailNode = newTailNode;
	// 리스트 크기를 하나 줄여준다.
	m_size--;
}

template<typename T>
void CMyList<T>::push_front(const T& data)
{
	// 1. 새로운 노드를 만들어서 data, 이전 노드로는 널포인트를,
	//    다음 노드로는 리스트의 처음 노드를 가리키도록 만든다.
	// 2. 리스트의 첫 노드의 이전 노드를 새로운 노드로 지정한다.
	// 3. 리스트의 첫 노드를 새로운 노드로 지정한다.
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, pHeadNode);
		pHeadNode->pPrev = newNode;
		pHeadNode = newNode;
	}
	else
	{
		// push_back을 처음 실행할때와 동일하게
		// 처음 노드가 들어가는 상황이라며 새로운 노드를
		// 리스트의 첫 노드와 끝 노드로 지정한다.
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	// 리스트의 크기를 증가시킨다.
	m_size++;
}

template<typename T>
void CMyList<T>::pop_front()
{
	// 리스트에 데이터가 없다면 함수를 중단하고 반환한다.
	if (m_size == 0)
		return;
	// 1. 새로운 노드를 만들고 리스트의 첫노드의 다음 노드를 대입한다.
	// 2. 리스트의 첫 노드를 메모리 해제 한다.
	// 3. 새로운 노드를 리스트의 첫 노드로 지정한다.
	Node<T>* newHeadNode = pHeadNode->pNext;
	delete pHeadNode;
	pHeadNode = newHeadNode;
	// 리스트의 크기를 감소시킨다.
	m_size--;
}

template<typename T>
int CMyList<T>::size() const
{
	// 크기를 반환한다.
	// 이런 방식으로 하기위해서는 m_size에 대한 신뢰성이 높아야한다.
	return m_size;
}

template<typename T>
bool CMyList<T>::empty()
{
	// 마찬가지로 m_size에 대한 신뢰성이 높아야한다.
	// m_size가 0이면 ture, 아니면 false가 반환된다.
	return m_size == 0;
}

template<typename T>
void CMyList<T>::clear()
{
	// 1. 현재 m_size의 값을 저장한다.
	// 2. 저장한 m_size의 값만큼 pop_back을 수행한다.
	// 3. 남아있는 첫 노드의 주소를 널포인트로 지정해준다.
	int tempSize = m_size;
	for (int i = 0; i < tempSize; i++)
		pop_back();

	pHeadNode = nullptr;
}

template<typename T>
void CMyList<T>::printAll()
{
	// 1. 임시 노드에 리스트의 첫 노드를 불러온다.
	// 2. 리스트의 크기만큼 아래 작업을 수행한다.
	// 2-1. 임시 노드의 데이터를 출력한다.
	// 2-2. 임시 노드에 임시 노드의 다음 노드를 불러온다.
	Node<T>* temp = pHeadNode;
	std::cout << "List Data : ";
	for (int i = 0; i < m_size; i++)
	{
		std::cout << temp->m_data << ", ";
		temp = temp->pNext;
	}
	std::cout << "\tsize : " << m_size << "\n\n";
}

template<typename T>
Node<T> CMyList<T>::at(int index)
{
	// 1. 임시 노드에 리스트의 첫 노드를 불러온다.
	// 2. 리스트의 크기만큼 아래 작업을 수행한다.
	// 2-1. i가 찾고자 하는 인덱스와 일치하면 해당 노드를 반환한다.
	// 2-2. 아니라면 임시노드에 임시노드의 다음 노드를 불러온다.
	Node<T>* temp = pHeadNode;
	for (int i = 0; i < m_size; i++)
	{
		if (i == index)
			return *temp;
		else
			temp = temp->pNext;
	}
}

template<typename T>
T CMyList<T>::operator[](int n) const
{
	// 1. 임시 노드에 리스트의 첫 노드를 불러온다.
	// 2. 리스트의 크기만큼 아래 작업을 수행한다.
	// 2-1. n번째 노드에 도달하면 해당 노드의 데이터를 반환한다.
	// 2-2. 아니라면 임시노드에 임시노드의 다음 노드를 불러온다.
	Node<T>* temp = pHeadNode;
	for (int i = 0; i < m_size; i++)
	{
		if (i == n)
			return temp->m_data;
		else
			temp = temp->pNext;
	}
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& _other)
{
	// 1. 복사생성자를 통해 동적할당으로 생성한다.
	// 2. 현재 가지고 있는 데이터를 해제한다.
	// 3. other의 정보를 this에 옮긴다.
	// 4. 현재 리스트를 반환한다.
	CMyList<T>* other = new CMyList<T>(_other);
	clear();
	this->m_size = other->m_size;
	this->pHeadNode = other->pHeadNode;
	this->pTailNode = other->pTailNode;
	return *this;
}

template<typename T>
CMyList<T> CMyList<T>::operator+(const CMyList& _other)
{
	// 1. 복사생성자를 통해 동적할당으로 생성한다.
	// 2. 현재 리스트의 끝 노드의 다음 노드를 other의 첫 노드로 지정한다.
	// 3. other의 첫 노드의 이전 노드를 현재 리스트의 끝 노드로 지정한다.
	// 4. 두 리스트의 크기를 합산하여 저장한다.
	// 5. other의 끝 노드를 현재 리스트의 끝 노드로 지정한다.
	// 6. 현재 리스트를 반환한다.
	CMyList<T>* other = new CMyList<T>(_other);
	pTailNode->pNext = other->pHeadNode;
	other->pHeadNode->pPrev = pTailNode;
	other->m_size += this->m_size;
	other->pHeadNode = pHeadNode;
	return *other;
}

template<typename T>
CMyList<T>& CMyList<T>::operator+=(const CMyList& _other)
{
	// 1. 복사생성자를 통해 동적할당으로 생성한다.
	// 2. 현재 리스트의 끝 노드의 다음 노드를 other의 첫 노드로 지정한다.
	// 3. other의 첫 노드의 이전 노드를 현재 리스트의 끝 노드로 지정한다.
	// 4. 두 리스트의 크기를 합산하여 저장한다.
	// 5. other의 끝 노드를 현재 리스트의 끝 노드로 지정한다.
	// 6. 현재 리스트를 반환한다.
	CMyList<T>* other = new CMyList<T>(_other);
	pTailNode->pNext = other->pHeadNode;
	other->pHeadNode->pPrev = pTailNode;
	this->m_size += other->m_size;
	pTailNode = other->pTailNode;
	return *this;
}

#pragma endregion

template<typename T>
CMyList<T>::iterator::iterator()
{
	this->pList = nullptr;
	this->pNode = nullptr;
	this->isEnd = false;
}

template<typename T>
CMyList<T>::iterator::iterator(CMyList* pList, Node<T>* pNode)
{
	this->pList = pList;
	this->pNode = pNode;
	this->isEnd = false;
}
template<typename T>
CMyList<T>::iterator::iterator(CMyList* pList, Node<T>* pNode, bool isEnd)
{
	this->pList = pList;
	this->pNode = pNode;
	this->isEnd = isEnd;
}

template<typename T>
T& CMyList<T>::iterator::operator*()
{
	// 1. iterator가 가리키는 노드가 nullptr일 때
	if (pNode == nullptr || isEnd)
		assert(nullptr);

	return pNode->m_data;
}

template<typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator++()
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우
	// 2. iterator가 마지막 데이터를 가리키고 있을 경우 : iterator end()로 만들어준다.
	// 3. iterator가 이미 end() iterator 였을 경우 : assert() 처리

	// 전위 연산자 (++iter)
	if (pNode == nullptr || isEnd)
		assert(nullptr);

	if (pList->pTailNode == pNode)
	{
		isEnd = true;
	}
	else
	{
		pNode = pNode->pNext;
	}
	return *this;
}

template<typename T>
typename CMyList<T>::iterator CMyList<T>::iterator::operator++(int)
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우
	// 2. iterator가 이미 end() iterator였을 떄 assert();
	// 3. iterator가 마지막 데이터를 가리키고 있을 경우 : iterator end()로 만들어준다.

	// 후위 연산자 (iter++)
	// 전위 연산자와의 차이 : 현재 값을 가지는 임시 반복자를 만들고 해당 값을 반환한다.
	//						이때 내부의 코드는 전위 연산자와 같지만 이전의 값을 지닌 임시 반복자를 반환하므로
	//						증가된 값을 반환하지 않는다.
	iterator temp(pList, pNode);
	if (pNode == nullptr || isEnd)
		assert(nullptr);

	if (pList->pTailNode == pNode)
	{
		isEnd = true;
	}
	else
	{
		pNode = pNode->pNext;
	}
	return temp;
}

template<typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator--()
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우 
	// 2. iterator가 이미 begin() iterator였을 떄 assert()
	if (pNode == nullptr)
		assert(nullptr);

	if (pList->pHeadNode == pNode)
	{
		pNode = nullptr;
	}
	else
	{
		isEnd = false;
		pNode = pNode->pPrev;
	}
	return *this;
}

template<typename T>
typename CMyList<T>::iterator CMyList<T>::iterator::operator--(int)
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우 
	// 2. iterator가 이미 begin() iterator였을 떄 assert()
	iterator temp(pList, pNode);

	if (pNode == nullptr)
		assert(nullptr);

	if (pList->pHeadNode == pNode)
	{
		pNode = nullptr;
	}
	else
	{
		isEnd = false;
		pNode = pNode->pPrev;
	}
	return temp;
}

template<typename T>
bool CMyList<T>::iterator::operator==(const iterator& _other)
{
	// 가리키는 벡터, 배열, 인덱스가 일치하면 true, 아니면 false
	if (this->pList == _other.pList &&
		this->pNode == _other.pNode &&
		this->isEnd == _other.isEnd)
		return true;
	return false;
}

template<typename T>
bool CMyList<T>::iterator::operator!=(const iterator& _other)
{
	// 가리키는 벡터, 배열, 인덱스가 일치하면 false, 아니면 true
	if (this->pList == _other.pList &&
		this->pNode == _other.pNode &&
		this->isEnd == _other.isEnd)
		return false;
	return true;
}

template<typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator=(const iterator& _other)
{
	this->pList = _other.pList;
	this->pNode = _other.pNode;

	return *this;
}

template<typename T>
typename CMyList<T>::iterator CMyList<T>::begin()
{
	iterator newIter(this, pHeadNode);
	return newIter;
}

template<typename T>
typename CMyList<T>::iterator CMyList<T>::end()
{
	iterator newIter(this, pTailNode, true);
	return newIter;
}

template<typename T>
void CMyList<T>::insert(iterator& iter, const T& value)
{
	// 제약사항
	// 1. 리스트의 크기가 0일때

	if (pHeadNode == iter.pNode)
	{
		Node<T>* tempNode = new Node<T>(value, nullptr, pHeadNode);
		pHeadNode->pPrev = tempNode;
		pHeadNode = tempNode;
	}
	else if (pTailNode == iter.pNode)
	{
		Node<T>* tempNode = new Node<T>(value, pTailNode, nullptr);
		pTailNode->pNext = tempNode;
		pTailNode = tempNode;
	}
	else
	{
		Node<T>* nextNode = iter.pNode->pNext;
		Node<T>* tempNode = new Node<T>(value, iter.pNode, nextNode);
		iter.pNode->pNext = tempNode;
		nextNode->pPrev = tempNode;
	}


	m_size++;
}

template<typename T>
void CMyList<T>::erase(iterator& iter)
{
	if (0 == m_size)
		return;

	if (pHeadNode == iter.pNode) pHeadNode = iter.pNode->pNext;
	else if (pTailNode == iter.pNode) pTailNode = iter.pNode->pPrev;
	iter.pNode->pNext->pPrev = iter.pNode->pPrev;
	iter.pNode->pPrev->pNext = iter.pNode->pNext;
	delete iter.pNode;
	m_size--;
}
