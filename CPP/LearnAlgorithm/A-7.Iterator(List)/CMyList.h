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
	Node<T>*	pHeadNode; // ����� ù��° �ּҰ�
	Node<T>*	pTailNode; // ����� ������ �ּҰ�
	int			m_size;    // ����Ʈ�� ��� �����Ͱ� ����ִ����� ���� ������

public:
	CMyList();
	// ���������
	CMyList(const CMyList& target);
	~CMyList();

	void push_back(const T& data); //�ڿ� ��带 ����
	void pop_back(); // ���� ��带 ����
	void push_front(const T& data); // �տ� ��带 ����
	void pop_front(); // ���� ��带 ����

	int size() const; // ũ�� ��ȯ
	bool empty(); // ����Ʈ�� ����ִ��� Ȯ��
	void clear(); // ����Ʈ�� ���� �Լ�

	void printAll(); // ��� ��带 ����ϴ� �Լ�

	Node<T> at(int index); // �ε����� ��带 ��ȯ�ϴ� �Լ�
	// ����Ʈ [] ������
	T operator[](int n) const;
	CMyList<T>& operator=(const CMyList& _other);
	// ����Ʈ�� ���� �ٸ� ����Ʈ�� ó���� ������ ����Ʈ�� ��ȯ�ϴ� +������ ������
	CMyList<T> operator+(const CMyList& _other);
	// ����Ʈ�� ���� �ٸ� ����Ʈ�� ó���� �����ϴ� += ������ ������
	CMyList<T>& operator+=(const CMyList& _other);

	class iterator
	{
		friend CMyList; // CMyList Ŭ������ iterator Ŭ������ �Ӽ��� �����Ӱ� ��밡���ϴ�.
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


	// +a ���ΰ���
	void insert(iterator& iter, const T& value);
	void erase(iterator& iter);
};

#pragma region List�Լ���
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
	// 1. ���ο� ��带 ���� data, ���� ���δ� ����Ʈ�� �����,
	//    ���� ���δ� ������Ʈ�� ����Ű���� �����.
	// 2. ����Ʈ�� �� ����� ���� ��带 ���ο� ���� �����Ѵ�.
	// 3. ����Ʈ�� �� ��带 ���ο� ���� �����Ѵ�.
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, pTailNode, nullptr);

		pTailNode->pNext = newNode;
		pTailNode = newNode;
	}
	else
	{
		// ó�� ���� ����� ��� �ش� ��带
		// ����Ʈ�� ù ���� �� ���� �������ش�.
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	// ����Ʈ�� ũ�⸦ �ϳ� �÷��ش�.
	m_size++;
}

template<typename T>
void CMyList<T>::pop_back()
{
	// ����Ʈ�� �����Ͱ� ���ٸ� �Լ��� ��ȯ�Ѵ�.
	if (0 == m_size)
		return;

	// 1. ���ο� ��带 ����� ����Ʈ �� ����� ���� ��带 �޾��ش�.
	// 2. �� ��带 �޸� �����Ѵ�.
	// 3. ���ο� ��带 ����Ʈ�� �� ���� �����Ѵ�.
	Node<T>* newTailNode = pTailNode->pPrev;
	delete pTailNode;
	pTailNode = newTailNode;
	// ����Ʈ ũ�⸦ �ϳ� �ٿ��ش�.
	m_size--;
}

template<typename T>
void CMyList<T>::push_front(const T& data)
{
	// 1. ���ο� ��带 ���� data, ���� ���δ� ������Ʈ��,
	//    ���� ���δ� ����Ʈ�� ó�� ��带 ����Ű���� �����.
	// 2. ����Ʈ�� ù ����� ���� ��带 ���ο� ���� �����Ѵ�.
	// 3. ����Ʈ�� ù ��带 ���ο� ���� �����Ѵ�.
	if (m_size > 0)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, pHeadNode);
		pHeadNode->pPrev = newNode;
		pHeadNode = newNode;
	}
	else
	{
		// push_back�� ó�� �����Ҷ��� �����ϰ�
		// ó�� ��尡 ���� ��Ȳ�̶�� ���ο� ��带
		// ����Ʈ�� ù ���� �� ���� �����Ѵ�.
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	// ����Ʈ�� ũ�⸦ ������Ų��.
	m_size++;
}

template<typename T>
void CMyList<T>::pop_front()
{
	// ����Ʈ�� �����Ͱ� ���ٸ� �Լ��� �ߴ��ϰ� ��ȯ�Ѵ�.
	if (m_size == 0)
		return;
	// 1. ���ο� ��带 ����� ����Ʈ�� ù����� ���� ��带 �����Ѵ�.
	// 2. ����Ʈ�� ù ��带 �޸� ���� �Ѵ�.
	// 3. ���ο� ��带 ����Ʈ�� ù ���� �����Ѵ�.
	Node<T>* newHeadNode = pHeadNode->pNext;
	delete pHeadNode;
	pHeadNode = newHeadNode;
	// ����Ʈ�� ũ�⸦ ���ҽ�Ų��.
	m_size--;
}

template<typename T>
int CMyList<T>::size() const
{
	// ũ�⸦ ��ȯ�Ѵ�.
	// �̷� ������� �ϱ����ؼ��� m_size�� ���� �ŷڼ��� ���ƾ��Ѵ�.
	return m_size;
}

template<typename T>
bool CMyList<T>::empty()
{
	// ���������� m_size�� ���� �ŷڼ��� ���ƾ��Ѵ�.
	// m_size�� 0�̸� ture, �ƴϸ� false�� ��ȯ�ȴ�.
	return m_size == 0;
}

template<typename T>
void CMyList<T>::clear()
{
	// 1. ���� m_size�� ���� �����Ѵ�.
	// 2. ������ m_size�� ����ŭ pop_back�� �����Ѵ�.
	// 3. �����ִ� ù ����� �ּҸ� ������Ʈ�� �������ش�.
	int tempSize = m_size;
	for (int i = 0; i < tempSize; i++)
		pop_back();

	pHeadNode = nullptr;
}

template<typename T>
void CMyList<T>::printAll()
{
	// 1. �ӽ� ��忡 ����Ʈ�� ù ��带 �ҷ��´�.
	// 2. ����Ʈ�� ũ�⸸ŭ �Ʒ� �۾��� �����Ѵ�.
	// 2-1. �ӽ� ����� �����͸� ����Ѵ�.
	// 2-2. �ӽ� ��忡 �ӽ� ����� ���� ��带 �ҷ��´�.
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
	// 1. �ӽ� ��忡 ����Ʈ�� ù ��带 �ҷ��´�.
	// 2. ����Ʈ�� ũ�⸸ŭ �Ʒ� �۾��� �����Ѵ�.
	// 2-1. i�� ã���� �ϴ� �ε����� ��ġ�ϸ� �ش� ��带 ��ȯ�Ѵ�.
	// 2-2. �ƴ϶�� �ӽó�忡 �ӽó���� ���� ��带 �ҷ��´�.
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
	// 1. �ӽ� ��忡 ����Ʈ�� ù ��带 �ҷ��´�.
	// 2. ����Ʈ�� ũ�⸸ŭ �Ʒ� �۾��� �����Ѵ�.
	// 2-1. n��° ��忡 �����ϸ� �ش� ����� �����͸� ��ȯ�Ѵ�.
	// 2-2. �ƴ϶�� �ӽó�忡 �ӽó���� ���� ��带 �ҷ��´�.
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
	// 1. ��������ڸ� ���� �����Ҵ����� �����Ѵ�.
	// 2. ���� ������ �ִ� �����͸� �����Ѵ�.
	// 3. other�� ������ this�� �ű��.
	// 4. ���� ����Ʈ�� ��ȯ�Ѵ�.
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
	// 1. ��������ڸ� ���� �����Ҵ����� �����Ѵ�.
	// 2. ���� ����Ʈ�� �� ����� ���� ��带 other�� ù ���� �����Ѵ�.
	// 3. other�� ù ����� ���� ��带 ���� ����Ʈ�� �� ���� �����Ѵ�.
	// 4. �� ����Ʈ�� ũ�⸦ �ջ��Ͽ� �����Ѵ�.
	// 5. other�� �� ��带 ���� ����Ʈ�� �� ���� �����Ѵ�.
	// 6. ���� ����Ʈ�� ��ȯ�Ѵ�.
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
	// 1. ��������ڸ� ���� �����Ҵ����� �����Ѵ�.
	// 2. ���� ����Ʈ�� �� ����� ���� ��带 other�� ù ���� �����Ѵ�.
	// 3. other�� ù ����� ���� ��带 ���� ����Ʈ�� �� ���� �����Ѵ�.
	// 4. �� ����Ʈ�� ũ�⸦ �ջ��Ͽ� �����Ѵ�.
	// 5. other�� �� ��带 ���� ����Ʈ�� �� ���� �����Ѵ�.
	// 6. ���� ����Ʈ�� ��ȯ�Ѵ�.
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
	// 1. iterator�� ����Ű�� ��尡 nullptr�� ��
	if (pNode == nullptr || isEnd)
		assert(nullptr);

	return pNode->m_data;
}

template<typename T>
typename CMyList<T>::iterator& CMyList<T>::iterator::operator++()
{
	// 1. iterator�� Vector�� ������ �������� �߸��� ���� ����Ű�� �ִ� ���
	// 2. iterator�� ������ �����͸� ����Ű�� ���� ��� : iterator end()�� ������ش�.
	// 3. iterator�� �̹� end() iterator ���� ��� : assert() ó��

	// ���� ������ (++iter)
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
	// 1. iterator�� Vector�� ������ �������� �߸��� ���� ����Ű�� �ִ� ���
	// 2. iterator�� �̹� end() iterator���� �� assert();
	// 3. iterator�� ������ �����͸� ����Ű�� ���� ��� : iterator end()�� ������ش�.

	// ���� ������ (iter++)
	// ���� �����ڿ��� ���� : ���� ���� ������ �ӽ� �ݺ��ڸ� ����� �ش� ���� ��ȯ�Ѵ�.
	//						�̶� ������ �ڵ�� ���� �����ڿ� ������ ������ ���� ���� �ӽ� �ݺ��ڸ� ��ȯ�ϹǷ�
	//						������ ���� ��ȯ���� �ʴ´�.
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
	// 1. iterator�� Vector�� ������ �������� �߸��� ���� ����Ű�� �ִ� ��� 
	// 2. iterator�� �̹� begin() iterator���� �� assert()
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
	// 1. iterator�� Vector�� ������ �������� �߸��� ���� ����Ű�� �ִ� ��� 
	// 2. iterator�� �̹� begin() iterator���� �� assert()
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
	// ����Ű�� ����, �迭, �ε����� ��ġ�ϸ� true, �ƴϸ� false
	if (this->pList == _other.pList &&
		this->pNode == _other.pNode &&
		this->isEnd == _other.isEnd)
		return true;
	return false;
}

template<typename T>
bool CMyList<T>::iterator::operator!=(const iterator& _other)
{
	// ����Ű�� ����, �迭, �ε����� ��ġ�ϸ� false, �ƴϸ� true
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
	// �������
	// 1. ����Ʈ�� ũ�Ⱑ 0�϶�

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
