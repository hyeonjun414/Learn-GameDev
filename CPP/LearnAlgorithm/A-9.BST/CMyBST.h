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

	bool isRoot()
	{
		return nullptr == pParent;
	}
	bool isLeftChild()
	{
		if (isRoot())
			return false;

		return pParent->pLeft == this;
	}
	bool isRightChild()
	{
		if (isRoot())
			return false;

		return pParent->pRight == this;
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
	void			InOrder(BinaryNode<T>* pNode);

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
	iterator		erase(const iterator& iter);
	iterator		begin();
	iterator		end();

};
#pragma region BST �����κ�

template<typename T>
CMyBST<T>::CMyBST()
{
	m_pRootNode = nullptr;
	m_size = 0;
}

template<typename T>
CMyBST<T>::~CMyBST()
{
	clear(); // clear�� ���� ���� ��带 ���� �����.
}

template<typename T>
void CMyBST<T>::clear()
{
	iterator iter = begin();
	// �ݺ��ڸ� Ʈ���� ó������ ������ ���鼭 ������ �������ش�.
	while (iter != end())
	{
		iter = erase(iter);
	}
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
	// ����ó��,
	// 1. BST�� �ƹ��͵� ������, RootNode�� ���� ��
	if (0 == m_size || nullptr == m_pRootNode)
	{
		cout << "BST�� �����Ͱ� �����ϴ�.";
		return;
	}
		
	cout << "BST Data : ";
	InOrder(m_pRootNode); // ��Ʈ ������ ������ȸ ���
	cout << endl;
}

template<typename T>
void CMyBST<T>::InOrder(BinaryNode<T>* pNode)
{
	// ���� ��ȸ�� ���
	if (nullptr == pNode) return;
	InOrder(pNode->pLeft);
	cout << pNode->data << ", ";
	InOrder(pNode->pRight);
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

	// Ž�� ���� ��尡 nullptr�ϋ����� �ݺ�
	while (nullptr != pCurrent)
	{
		// ���ԵǴ� �����Ͱ� ���� ��庸�� ������
		if (target < pCurrent->data)
		{
			// ���� Ž�� ����� ���� �ڽ��� ����ִٸ� ���ο� ��带 ����
			if (nullptr == pCurrent->pLeft)
			{
				pCurrent->pLeft = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this, pCurrent->pLeft);
			}
			// ������� �ʴٸ� �ش� ���� �̵�.
			pCurrent = pCurrent->pLeft;
		}
		// ���ԵǴ� �����Ͱ� ���� ��庸�� ũ��
		else if (target > pCurrent->data)
		{
			// ���� Ž�� ����� ������ �ڽ��� ����ִٸ� ���ο� ��带 ����
			if (nullptr == pCurrent->pRight)
			{
				pCurrent->pRight = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this, pCurrent->pRight);
			}
			// ������� �ʴٸ� �ش� ���� �̵�.
			pCurrent = pCurrent->pRight;
		}
		// Ž�� ���� ���� ���ٸ�
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
	// Ž�� ��� ����
	BinaryNode<T>* pCurrent = m_pRootNode;

	// ����1. �ϳ��� �����µ� find�� �õ��� ���
	if (0 == m_size) // m_pRootNode == nullptr;
	{
		return end();
	}

	// ã�������� �ݺ�
	while (true)
	{
		// ���� Ž����� ������ ã�� ���� ������
		if (target < pCurrent->data)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			// ���� �ڽ����� �̵�
			pCurrent = pCurrent->pLeft;
		}
		// ũ��
		else if (target > pCurrent->data)
		{
			if (nullptr == pCurrent->pRight)
				break;
			// ������ �ڽ����� �̵�
			pCurrent = pCurrent->pRight;
		}
		// ������ 
		else // ���ϴ� �����͸� ã������
		{
			// �ش� �ݺ��ڸ� ��ȯ
			return iterator(this, pCurrent);
		}
	}
	// ��ã���� end iterator ��ȯ
	return end();
}

template<typename T>
typename  CMyBST<T>::iterator CMyBST<T>::erase(const iterator& iter)
{ 
	// 0. ����ó��, ������°� root ��� �ϋ�, ��尡 ���ʿ� �ϳ��� ������ ��
	// 1. �ڽ��� ���� ���		- �׳� ����
	// 2. �ڽ��� �ϳ��� ���		- ����ġ�� ���ڽ��� �ø���.
	// 3. �ڽ��� ���� ���		- ������ȸ�� ���� ��峪 ���� ����� ������ �����ϰ� �� ��带 �����.
	if (0 == iter.m_pMyBST->size())
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = iter.m_pBinaryNode;

	// �ڽ��� ���� ��带 ���ﶧ
	if (nullptr == pCurrent->pLeft && nullptr == pCurrent->pRight)
	{
		m_size--;
		iterator next = iter;
		++next;
		// ���� ��尡 ���� �ڽ��̶��
		if (pCurrent->isLeftChild())
		{
			// ���� ����� �θ� ����� ���� �ڽ��� nullptr�� �����.
			pCurrent->pParent->pLeft = nullptr;
		}
		// ���� ��尡 ������ �ڽ��̶��
		else if (pCurrent->isRightChild())
		{
			// �θ� ����� ������ �ڽ��� nullptr�� �����.
			pCurrent->pParent->pRight = nullptr;
		}
		// ���� ��尡 ��Ʈ �����
		else // if(pCurrent->isRoot())
		{
			// ��Ʈ��带 nullptr�� ������ش�.
			m_pRootNode = nullptr;
			delete pCurrent;
			return end();
		}
		delete pCurrent;
		return next;
	}
	// �ڽ� ��尡 �ϳ� ������
	else if((nullptr != pCurrent->pLeft && nullptr == pCurrent->pRight) || 
			(nullptr != pCurrent->pRight && nullptr == pCurrent->pLeft))
	{
		// �ϳ��� �ڽ��� �������϶�
		if (nullptr != pCurrent->pRight)
		{
			m_size--;
			iterator next = iter;
			++next;
			// ���� ��尡 ���� �ڽ� �����
			if (pCurrent->isLeftChild())
			{
				// �������� ������ �ڽ� ��带 �θ� ����� ���� �ڽ� ���� ��ȣ �����Ѵ�.
				pCurrent->pParent->pLeft = pCurrent->pRight;
				pCurrent->pRight->pParent = pCurrent->pParent;
			}
			// ���� ��尡 ������ �ڽ� �����
			else if (pCurrent->isRightChild())
			{
				// �������� ������ �ڽ� ��带 �θ� ����� ������ �ڽ� ���� ��ȣ �����Ѵ�.
				pCurrent->pParent->pRight = pCurrent->pRight;
				pCurrent->pRight->pParent = pCurrent->pParent;
			}
			// ���� ��尡 ��Ʈ �����
			else // if(pCurrent->isRoot())
			{
				// ���� ����� ������ �ڽ� ��带 Ʈ���� ��Ʈ ���� ������.
				m_pRootNode = pCurrent->pRight;
				// ������ �ڽ� ����� �θ� ��带 nullptr�� �����.
				pCurrent->pRight->pParent = nullptr;
			}
			// ���� ��� �޸� ����
			delete pCurrent;
			return next;
		}
		// �ϳ��� �ڽ��� ���� �϶�
		else if (nullptr != pCurrent->pLeft)
		{
			m_size--;
			iterator next = iter;
			++next;
			// ���� ��尡 ���� �ڽ� �����
			if (pCurrent->isLeftChild())
			{
				// ���� ����� ���� �ڽ� ��带 �θ� ����� ���� �ڽ����� ��ȣ ������.
				pCurrent->pParent->pLeft = pCurrent->pLeft;
				pCurrent->pLeft->pParent = pCurrent->pParent;
			}
			else if (pCurrent->isRightChild())
			{
				// ���� ����� ���� �ڽ� ��带 �θ� ����� ������ �ڽ����� ��ȣ ������.
				pCurrent->pParent->pRight = pCurrent->pLeft;
				pCurrent->pLeft->pParent = pCurrent->pParent;
			}
			else // if(pCurrent->isRoot())
			{
				// ���� ����� ���� �ڽ� ��带 Ʈ���� ��Ʈ ���� ������.
				m_pRootNode = pCurrent->pLeft;
				// ���� �ڽ� ����� �θ� ��带 nullptr�� �����.
				pCurrent->pLeft->pParent = nullptr;
			}
			delete pCurrent;
			return next;
		}
	}
	// �ڽ� ��尡 �ΰ� �϶�
	else if(nullptr != pCurrent->pLeft && nullptr != pCurrent->pRight)
	{
		iterator next = iter;
		++next;
		// ������ȸ �������� ���� ����� �����͸� ������ �Է��ϰ�
		// ���� ��带 �����Ѵ�.
		pCurrent->data = next.m_pBinaryNode->data;
		erase(next);
		// �׸��� ���� ����� iterator�� ��ȯ�Ѵ�.
		return iterator(this, pCurrent);
	}
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::begin()
{
	BinaryNode<T>* pCurrent = m_pRootNode;

	// Ʈ���� ����ִٸ� end iterator�� ��ȯ
	if (0 == m_size)
	{
		return end();
	}

	// ������ ���� ���, �� ���� ���� ��带 begin iterator�� �����Ѵ�.
	while (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}

	return iterator(this, pCurrent);
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::end()
{
	// end iterator�� nullptr�� ����Ų��.
	return iterator(this, nullptr);
}
#pragma endregion

#pragma region �ݺ��� ���� �κ�
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
	iterator temp(this->m_pMyBST, this->m_pBinaryNode);
	++(*this);
	return temp;
}

template<typename T>
typename CMyBST<T>::iterator& CMyBST<T>::iterator::operator--()
{
	// 0. ���� ó��, �ϳ��� ��������, �̹� begin() iterator ������
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}
	// �̹� end()�� ����������,
	if (nullptr == m_pBinaryNode)
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;

		// ���� ������ ��, ���� ū ��带 ã�� ��ȯ�Ѵ�.
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
	--(*this);
	return temp;
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
	return !(*this == _other);
}

#pragma endregion

