#pragma once

#include <assert.h>
#include <iostream>

using namespace std;
template <typename T>
struct BinaryNode
{
	T				data;
	BinaryNode<T>*	pParent;
	BinaryNode<T>*	pLeft;
	BinaryNode<T>*	pRight;

	BinaryNode<T>()
	{
		this->data = 0;
		this->pParent = nullptr;
		this->pLeft = nullptr;
		this->pRight = nullptr;
	}
	BinaryNode<T>(T data, BinaryNode<T>* pParent, BinaryNode<T>* pLeft, BinaryNode<T>* pRight)
	{
		this->data = data;
		this->pParent = pParent;
		this->pLeft = pLeft;
		this->pRight = pRight;
	}

};


template <typename T>
class CMyBST
{
	BinaryNode<T>*	m_pRootNode;
	unsigned int	m_size;

public:
	CMyBST();
	~CMyBST();
	void			clear();
	unsigned int	size();
	bool			empty();
	void			printAll();
	void			PreOrder(BinaryNode<T>* pNode);
	void			InOrder(BinaryNode<T>* pNode);
	void			PostOrder(BinaryNode<T>* pNode);

	class iterator
	{
		friend CMyBST;
	private:
		CMyBST<T>*		m_pMyBST;
		BinaryNode<T>*	m_pBinaryNode;

	public:
		iterator();
		iterator(CMyBST<T>* pBinaryBST, BinaryNode<T>* pNode);
		T&			operator*();
		iterator&	operator++();
		iterator	operator++(int);
		iterator&	operator--();
		iterator	operator--(int);
		bool		operator==(const iterator& _other);
		bool		operator!=(const iterator& _other);
	};

	iterator		insert(const T& target);
	iterator		find(const T& target);
	iterator		erase(iterator& iter);
	iterator		begin();
	iterator		end();

};

template<typename T>
CMyBST<T>::CMyBST()
{
	m_pRootNode = nullptr;
	m_size		= 0;
}

template<typename T>
CMyBST<T>::~CMyBST()
{
}

template<typename T>
void CMyBST<T>::clear()
{
	//TODO : ��Ʈ ������ �������� ���� ��带 ���� �����ֱ�
}

template<typename T>
unsigned int CMyBST<T>::size()
{
	return m_size;
}

template<typename T>
bool CMyBST<T>::empty()
{
	return m_size == 0;
}

template<typename T>
void CMyBST<T>::printAll()
{
	cout << "BST Data : ";
	InOrder(m_pRootNode);
	cout << endl;
}

template<typename T>
void CMyBST<T>::PreOrder(BinaryNode<T>* pNode)
{
}

template<typename T>
void CMyBST<T>::InOrder(BinaryNode<T>* pNode)
{
	if (nullptr == pNode) return;
	InOrder(pNode->pLeft);
	cout << pNode->data << ", ";
	InOrder(pNode->pRight);
}

template<typename T>
void CMyBST<T>::PostOrder(BinaryNode<T>* pNode)
{
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::insert(const T& target)
{
	BinaryNode<T>* pCurrent = m_pRootNode;
	// 1. ó���� �����Ͱ� �ϳ��� ��������
	if (0 == m_size)
	{
		m_pRootNode = new BinaryNode<T>(target, nullptr, nullptr, nullptr);
		m_size++;
		return iterator(this, m_pRootNode);
	}

	while (nullptr != pCurrent)
	{
		if (target < pCurrent->data)
		{
			if (nullptr == pCurrent->pLeft)
			{
				pCurrent->pLeft = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this,pCurrent->pLeft);
			}
			pCurrent = pCurrent->pLeft;
		}
		else if (target > pCurrent->data)
		{
			if (nullptr == pCurrent->pRight)
			{
				pCurrent->pRight = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this, pCurrent->pRight);
			}
			pCurrent = pCurrent->pRight;
		}
		else // target == pCurrent->data
		{
			
			// �ߺ� �����Ϳ� ���� bst�� ������ ����.
			return iterator(this, pCurrent);
		}
	}

	return iterator();
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::find(const T& target)
{
	BinaryNode<T>* pCurrent = m_pRootNode;

	// 1. �ϳ��� �����µ� find�� �õ��� ���
	if (0 == m_size) // m_pRootNode == nullptr;
	{
		return end();
	}

	while (true)
	{
		if (target < pCurrent->data)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		else if (target > pCurrent->data)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		else // ���ϴ� �����͸� ã������
		{
			return iterator(this, pCurrent);
		}
	}
	return end();
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::begin()
{
	BinaryNode<T>* pCurrent = m_pRootNode;

	
	if (0 == m_size)
	{
		return end();
	}

	while (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}

	return iterator(this, pCurrent);
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
CMyBST<T>::iterator::iterator()
{
	m_pMyBST = nullptr;
	m_pBinaryNode = nullptr;
}

template<typename T>
CMyBST<T>::iterator::iterator(CMyBST<T>* pBinaryBST, BinaryNode<T>* pNode)
{
	m_pMyBST = pBinaryBST;
	m_pBinaryNode = pNode;
}


template<typename T>
T& CMyBST<T>::iterator::operator*()
{
	return m_pBinaryNode->data;
}

template<typename T>
typename CMyBST<T>::iterator& CMyBST<T>::iterator::operator++()
{
	// 0. ���� ó��, �ϳ��� ��������, �̹� end() iterator ������
	if (nullptr == this->m_pMyBST->m_pRootNode || nullptr == m_pBinaryNode)
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. ������ �ڽ��� �ִ� ���, ������ �ڽ����� ���� ���� �ڽ��� ���� ������ ������.
	if (nullptr != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pBinaryNode = pCurrent;
		return *this;
	}
	// 2. ������ �ڽ��� ���� ���, �θ�� �����ϴµ� ���� �ڽ��� ������ ���� ��.
	else
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���� ��� == ó�� ��尡 ���� ū ��忴��.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent == pCurrent->pParent->pLeft)
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::iterator::operator++(int)
{
	// 0. ���� ó��, �ϳ��� ��������, �̹� end() iterator ������
	if (nullptr == this->m_pMyBST->m_pRootNode || nullptr == m_pBinaryNode)
	{
		assert(nullptr);
	}
	iterator temp(this->m_pMyBST, this->m_pBinaryNode);
	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. ������ �ڽ��� �ִ� ���, ������ �ڽ����� ���� ���� �ڽ��� ���� ������ ������.
	if (nullptr != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pBinaryNode = pCurrent;
		return temp;
	}
	// 2. ������ �ڽ��� ���� ���, �θ�� �����ϴµ� ���� �ڽ��� ������ ���� ��.
	else
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���� ��� == ó�� ��尡 ���� ū ��忴��.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return temp;
			}
			if (pCurrent == pCurrent->pParent->pLeft)
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pBinaryNode = pCurrent->pParent;
				return temp;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CMyBST<T>::iterator& CMyBST<T>::iterator::operator--()
{
	// 0. ���� ó��, �ϳ��� ��������
	if (nullptr == this->m_pMyBST->m_pRootNode)
	{
		assert(nullptr);
	}
	// �̹� end()�� ����������,
	if (nullptr == m_pBinaryNode)
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;

		while (nullptr != pCurrent->pRight)
		{
			pCurrent = pCurrent->pRight;
		}
		m_pBinaryNode = pCurrent;
		return *this;
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;

	// 1. ���� �ڽ��� �ִ� ���, ���� �ڽ����� ���� ������ �ڽ��� ���� ������ ������.
	if (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pBinaryNode = pCurrent;
		return *this;
	}
	// 2. ���� �ڽ��� ���� ���, �θ�� �����ϴµ� ������ �ڽ��� �� ���� ���� ��.
	else
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���� ��� == ó�� ��尡 ���� ū ��忴��.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent == pCurrent->pParent->pRight)
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::iterator::operator--(int)
{
	iterator temp(this->m_pMyBST, this->m_pBinaryNode);

	// 0. ���� ó��, �ϳ��� ��������
	if (nullptr == this->m_pMyBST->m_pRootNode)
	{
		assert(nullptr);
	}
	// �̹� end()�� ����������,
	if (nullptr == m_pBinaryNode)
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;

		while (nullptr != pCurrent->pRight)
		{
			pCurrent = pCurrent->pRight;
		}
		m_pBinaryNode = pCurrent;
		return temp;
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;

	// 1. ���� �ڽ��� �ִ� ���, ���� �ڽ����� ���� ������ �ڽ��� ���� ������ ������.
	if (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pBinaryNode = pCurrent;
		return temp;
	}
	// 2. ���� �ڽ��� ���� ���, �θ�� �����ϴµ� ������ �ڽ��� �� ���� ���� ��.
	else
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���� ��� == ó�� ��尡 ���� ū ��忴��.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return temp;
			}
			if (pCurrent == pCurrent->pParent->pRight)
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pBinaryNode = pCurrent->pParent;
				return temp;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
bool CMyBST<T>::iterator::operator==(const iterator& _other)
{
	if (this->m_pMyBST == _other.m_pMyBST &&
		this->m_pBinaryNode == _other.m_pBinaryNode)
		return true;
	return false;
}

template<typename T>
bool CMyBST<T>::iterator::operator!=(const iterator& _other)
{
	if (this->m_pMyBST == _other.m_pMyBST &&
		this->m_pBinaryNode == _other.m_pBinaryNode)
		return false;
	return true;
}

