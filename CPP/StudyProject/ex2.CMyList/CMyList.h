#pragma once
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
	~Node()
	{

	}
};

template <typename T>
class CMyList
{
	Node<T>* pHeadNode;
	Node<T>* pTailNode;
	int			m_size;

public:
	CMyList();
	~CMyList();

	void push_back(const T& data);		// List�� ���� �ڿ� ������ �߰�
	void pop_back();					// List�� ���� �ڿ� ������ ����
	void push_front(const T& data);		// List�� ���� �տ� ������ �߰�
	void pop_front();					// List�� ���� �ڿ� ������ ����

	int size() const;					// List�� ���� ����Ǿ� �ִ� ������ ��
	bool empty();						// List�� ������� �� true ��ȯ
	void clear();						// List�� ��� ������ ����
};

template<typename T>
inline CMyList<T>::CMyList()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}

template<typename T>
inline CMyList<T>::~CMyList()
{
	clear();
}

template<typename T>
inline void CMyList<T>::push_back(const T& data)
{
	if (0 == m_size)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	else
	{
		Node<T>* newNode = new Node<T>(data, pTailNode, nullptr);
		pTailNode->pNext = newNode;
		pTailNode = newNode;
	}

	m_size++;
}

template<typename T>
inline void CMyList<T>::pop_back()
{
	if (1 == m_size)
	{
		delete pTailNode;
		pTailNode = nullptr;
		pHeadNode = nullptr;
	}
	else
	{
		Node<T>* deleteNode = pTailNode;
		pTailNode = pTailNode->pPrev;
		pTailNode->pNext = nullptr;
		delete deleteNode;
	}

	m_size--;
}

template<typename T>
inline void CMyList<T>::push_front(const T& data)
{
	if (0 == m_size)
	{
		Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
		pHeadNode = newNode;
		pTailNode = newNode;
	}
	else
	{
		Node<T>* newNode = new Node<T>(data, nullptr, pHeadNode);
		pHeadNode->pPrev = newNode;
		pHeadNode = newNode;
	}

	m_size++;
}

template<typename T>
inline void CMyList<T>::pop_front()
{
	if (1 == m_size)
	{
		delete pHeadNode;
		pTailNode = nullptr;
		pHeadNode = nullptr;
	}
	else
	{
		Node<T>* deleteNode = pHeadNode;
		pHeadNode = pHeadNode->pNext;
		pHeadNode->pPrev = nullptr;
		delete deleteNode;
	}

	m_size--;
}

template<typename T>
inline int CMyList<T>::size() const
{
	return m_size;
}

template<typename T>
inline bool CMyList<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
inline void CMyList<T>::clear()
{
	while (m_size != 0)
		pop_back();
}
