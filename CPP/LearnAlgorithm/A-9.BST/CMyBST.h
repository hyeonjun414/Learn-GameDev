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
#pragma region BST 구현부분

template<typename T>
CMyBST<T>::CMyBST()
{
	m_pRootNode = nullptr;
	m_size = 0;
}

template<typename T>
CMyBST<T>::~CMyBST()
{
	clear(); // clear를 통해 남은 노드를 전부 비워줌.
}

template<typename T>
void CMyBST<T>::clear()
{
	iterator iter = begin();
	// 반복자를 트리의 처음부터 끝까지 돌면서 노드들을 제거해준다.
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
	// 예외처리,
	// 1. BST에 아무것도 없을떄, RootNode가 없을 때
	if (0 == m_size || nullptr == m_pRootNode)
	{
		cout << "BST에 데이터가 없습니다.";
		return;
	}
		
	cout << "BST Data : ";
	InOrder(m_pRootNode); // 루트 노드부터 중위순회 출력
	cout << endl;
}

template<typename T>
void CMyBST<T>::InOrder(BinaryNode<T>* pNode)
{
	// 중위 순회로 출력
	if (nullptr == pNode) return;
	InOrder(pNode->pLeft);
	cout << pNode->data << ", ";
	InOrder(pNode->pRight);
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::insert(const T& target)
{
	BinaryNode<T>* pCurrent = m_pRootNode;
	// 1. 처음에 데이터가 하나도 없었을때
	if (0 == m_size)
	{
		m_pRootNode = new BinaryNode<T>(target, nullptr, nullptr, nullptr);
		m_size++;
		return iterator(this, m_pRootNode);
	}

	// 탐색 중인 노드가 nullptr일떄까지 반복
	while (nullptr != pCurrent)
	{
		// 삽입되는 데이터가 현재 노드보다 작으면
		if (target < pCurrent->data)
		{
			// 현재 탐색 노드의 왼쪽 자식이 비어있다면 새로운 노드를 생성
			if (nullptr == pCurrent->pLeft)
			{
				pCurrent->pLeft = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this, pCurrent->pLeft);
			}
			// 비어있지 않다면 해당 노드로 이동.
			pCurrent = pCurrent->pLeft;
		}
		// 삽입되는 데이터가 현재 노드보다 크면
		else if (target > pCurrent->data)
		{
			// 현재 탐색 노드의 오른쪽 자식이 비어있다면 새로운 노드를 생성
			if (nullptr == pCurrent->pRight)
			{
				pCurrent->pRight = new BinaryNode<T>(target, pCurrent, nullptr, nullptr);
				m_size++;
				return iterator(this, pCurrent->pRight);
			}
			// 비어있지 않다면 해당 노드로 이동.
			pCurrent = pCurrent->pRight;
		}
		// 탐색 노드와 값이 같다면
		else // target == pCurrent->data
		{
			// 중복 데이터에 대한 bst의 반응은 무시.
			return iterator(this, pCurrent);
		}
	}
	return iterator();
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::find(const T& target)
{
	// 탐색 노드 생성
	BinaryNode<T>* pCurrent = m_pRootNode;

	// 예외1. 하나도 없었는데 find를 시도한 경우
	if (0 == m_size) // m_pRootNode == nullptr;
	{
		return end();
	}

	// 찾을때까지 반복
	while (true)
	{
		// 만약 탐색노드 값보다 찾는 값이 작으면
		if (target < pCurrent->data)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			// 왼쪽 자식으로 이동
			pCurrent = pCurrent->pLeft;
		}
		// 크면
		else if (target > pCurrent->data)
		{
			if (nullptr == pCurrent->pRight)
				break;
			// 오른쪽 자식으로 이동
			pCurrent = pCurrent->pRight;
		}
		// 같으면 
		else // 원하는 데이터를 찾았을때
		{
			// 해당 반복자를 반환
			return iterator(this, pCurrent);
		}
	}
	// 못찾으면 end iterator 반환
	return end();
}

template<typename T>
typename  CMyBST<T>::iterator CMyBST<T>::erase(const iterator& iter)
{ 
	// 0. 예외처리, 지우려는게 root 노드 일떄, 노드가 애초에 하나도 없었을 떄
	// 1. 자식이 없는 경우		- 그냥 삭제
	// 2. 자식이 하나인 경우		- 내위치에 내자식을 올린다.
	// 3. 자식이 둘인 경우		- 중위순회상 이전 노드나 이후 노드의 값으로 변경하고 그 노드를 지운다.
	if (0 == iter.m_pMyBST->size())
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = iter.m_pBinaryNode;

	// 자식이 없는 노드를 지울때
	if (nullptr == pCurrent->pLeft && nullptr == pCurrent->pRight)
	{
		m_size--;
		iterator next = iter;
		++next;
		// 현재 노드가 왼쪽 자식이라면
		if (pCurrent->isLeftChild())
		{
			// 현재 노드의 부모 노드의 왼쪽 자식을 nullptr로 만든다.
			pCurrent->pParent->pLeft = nullptr;
		}
		// 현재 노드가 오른쪽 자식이라면
		else if (pCurrent->isRightChild())
		{
			// 부모 노드의 오른쪽 자식을 nullptr로 만든다.
			pCurrent->pParent->pRight = nullptr;
		}
		// 현재 노드가 루트 노드라면
		else // if(pCurrent->isRoot())
		{
			// 루트노드를 nullptr로 만들어준다.
			m_pRootNode = nullptr;
			delete pCurrent;
			return end();
		}
		delete pCurrent;
		return next;
	}
	// 자식 노드가 하나 있을때
	else if((nullptr != pCurrent->pLeft && nullptr == pCurrent->pRight) || 
			(nullptr != pCurrent->pRight && nullptr == pCurrent->pLeft))
	{
		// 하나의 자식이 오른쪽일때
		if (nullptr != pCurrent->pRight)
		{
			m_size--;
			iterator next = iter;
			++next;
			// 현재 노드가 왼쪽 자식 노드라면
			if (pCurrent->isLeftChild())
			{
				// 현재노드의 오른쪽 자식 노드를 부모 노드의 왼쪽 자식 노드로 상호 연결한다.
				pCurrent->pParent->pLeft = pCurrent->pRight;
				pCurrent->pRight->pParent = pCurrent->pParent;
			}
			// 현재 노드가 오른쪽 자식 노드라면
			else if (pCurrent->isRightChild())
			{
				// 현재노드의 오른쪽 자식 노드를 부모 노드의 오른쪽 자식 노드로 상호 연결한다.
				pCurrent->pParent->pRight = pCurrent->pRight;
				pCurrent->pRight->pParent = pCurrent->pParent;
			}
			// 현재 노드가 루트 노드라면
			else // if(pCurrent->isRoot())
			{
				// 현재 노드의 오른쪽 자식 노드를 트리의 루트 노드로 지정함.
				m_pRootNode = pCurrent->pRight;
				// 오른쪽 자식 노드의 부모 노드를 nullptr로 만든다.
				pCurrent->pRight->pParent = nullptr;
			}
			// 현재 노드 메모리 해제
			delete pCurrent;
			return next;
		}
		// 하나의 자식이 왼쪽 일때
		else if (nullptr != pCurrent->pLeft)
		{
			m_size--;
			iterator next = iter;
			++next;
			// 현재 노드가 왼쪽 자식 노드라면
			if (pCurrent->isLeftChild())
			{
				// 현재 노드의 왼쪽 자식 노드를 부모 노드의 왼쪽 자식으로 상호 연결함.
				pCurrent->pParent->pLeft = pCurrent->pLeft;
				pCurrent->pLeft->pParent = pCurrent->pParent;
			}
			else if (pCurrent->isRightChild())
			{
				// 현재 노드의 왼쪽 자식 노드를 부모 노드의 오른쪽 자식으로 상호 연결함.
				pCurrent->pParent->pRight = pCurrent->pLeft;
				pCurrent->pLeft->pParent = pCurrent->pParent;
			}
			else // if(pCurrent->isRoot())
			{
				// 현재 노드의 왼쪽 자식 노드를 트리의 루트 노드로 지정함.
				m_pRootNode = pCurrent->pLeft;
				// 왼쪽 자식 노드의 부모 노드를 nullptr로 만든다.
				pCurrent->pLeft->pParent = nullptr;
			}
			delete pCurrent;
			return next;
		}
	}
	// 자식 노드가 두개 일때
	else if(nullptr != pCurrent->pLeft && nullptr != pCurrent->pRight)
	{
		iterator next = iter;
		++next;
		// 중위순회 기준으로 다음 노드의 데이터를 가져와 입력하고
		// 다음 노드를 삭제한다.
		pCurrent->data = next.m_pBinaryNode->data;
		erase(next);
		// 그리고 현재 노드의 iterator를 반환한다.
		return iterator(this, pCurrent);
	}
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::begin()
{
	BinaryNode<T>* pCurrent = m_pRootNode;

	// 트리가 비어있다면 end iterator를 반환
	if (0 == m_size)
	{
		return end();
	}

	// 가능한 왼쪽 노드, 즉 가장 작은 노드를 begin iterator로 지정한다.
	while (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}

	return iterator(this, pCurrent);
}

template<typename T>
typename CMyBST<T>::iterator CMyBST<T>::end()
{
	// end iterator는 nullptr을 가리킨다.
	return iterator(this, nullptr);
}
#pragma endregion

#pragma region 반복자 구현 부분
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
	// 0. 예외 처리, 하나도 없었을때, 이미 end() iterator 였을때
	if (nullptr == this->m_pMyBST->m_pRootNode || nullptr == m_pBinaryNode)
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. 오른쪽 자식이 있는 경우, 오른쪽 자식으로 가서 왼쪽 자식이 없을 때까지 내려감.
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
	// 2. 오른쪽 자식이 없는 경우, 부모로 가야하는데 왼쪽 자식일 떄까지 위로 감.
	else
	{
		while (true)
		{
			// 계속 따라 올라갔는데 부모가 없을 경우 == 처음 노드가 가장 큰 노드였다.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent == pCurrent->pParent->pLeft)
			{
				// 이때 부모가 자신의 다음 Node
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
	// 0. 예외 처리, 하나도 없었을때, 이미 begin() iterator 였을때
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}
	// 이미 end()를 가리켰을때,
	if (nullptr == m_pBinaryNode)
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;

		// 가장 오른쪽 즉, 가장 큰 노드를 찾아 반환한다.
		while (nullptr != pCurrent->pRight)
		{
			pCurrent = pCurrent->pRight;
		}
		m_pBinaryNode = pCurrent;
		return *this;
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;

	// 1. 왼쪽 자식이 있는 경우, 왼쪽 자식으로 가서 오른쪽 자식이 없을 때까지 내려감.
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
	// 2. 왼쪽 자식이 없는 경우, 부모로 가야하는데 오른쪽 자식일 때 까지 위로 감.
	else
	{
		while (true)
		{
			// 계속 따라 올라갔는데 부모가 없을 경우 == 처음 노드가 가장 큰 노드였다.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent == pCurrent->pParent->pRight)
			{
				// 이때 부모가 자신의 다음 Node
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

