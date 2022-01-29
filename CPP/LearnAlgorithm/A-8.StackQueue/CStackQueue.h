#pragma once
template <typename T>
class CMyQueue
{
private:
	T* pData;
	int m_index;

public:
	CMyQueue();
	~CMyQueue();
	void	push(T data);
	T		front();
	void	pop();
};

template <typename T>
class CMyStack
{
private:
	T* pData;

public:
	CMyStack();
	~CMyStack();
	void	push(T data);
	T		top();
	void	pop();
};

template<typename T>
inline CMyQueue<T>::CMyQueue()
{
}

template<typename T>
inline CMyQueue<T>::~CMyQueue()
{
}

template<typename T>
inline void CMyQueue<T>::push(T data)
{
}

template<typename T>
inline T CMyQueue<T>::front()
{
	return T();
}

template<typename T>
inline void CMyQueue<T>::pop()
{
}

template<typename T>
inline CMyStack<T>::CMyStack()
{
}

template<typename T>
inline CMyStack<T>::~CMyStack()
{
}

template<typename T>
inline void CMyStack<T>::push(T data)
{
}

template<typename T>
inline T CMyStack<T>::top()
{
	return T();
}

template<typename T>
inline void CMyStack<T>::pop()
{
}
