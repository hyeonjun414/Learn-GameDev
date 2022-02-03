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
	//newTailNode->pNext = nullptr;
	delete pTailNode;
	pTailNode = newTailNode;
	// ����Ʈ ũ�⸦ �ϳ� �ٿ��ش�.
	m_size--;
	//pTailNode->pNext = nullptr;
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
	//pHeadNode->pPrev = nullptr;
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
	std::cout << "\tsize : "<< m_size << "\n\n";
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
