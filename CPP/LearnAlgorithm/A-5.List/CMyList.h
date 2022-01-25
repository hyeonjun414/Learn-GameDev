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

	void print_AllNode(); // ��� ��带 ����ϴ� �Լ�

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

	// 1. ��� �����Ҵ�
	// 2. ���ο� ��忡 �����Ϳ� pPrev�� ������ ��忡 ����
	// 3. ������ ����� pNext�� ���ο� ��忡 ����
	// 4. ���ο� ��带 ������ ���� ����
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
	// TODO: ���⿡ return ���� �����մϴ�.
	return (CMyList<T>)*this;
}
