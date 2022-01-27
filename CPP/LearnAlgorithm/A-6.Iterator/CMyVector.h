#pragma once

#include<assert.h>

template <typename T> 
class CMyVector
{
private:
	T* pDataArray;
	unsigned int m_size; // 벡터의 사이즈
	unsigned int m_capacity; // 현재 벡터의 저장소를 더 늘리지 않는 선에서 할당가능한 수.

public:

	CMyVector();
	~CMyVector();

	// 매개변수로 const를 받는 것은 매개변수가 변경되지 않도록 방지하는 것이고,
	// 참조자를 사용하는 것은 값에 의한 호출이 일어나 쓸데없이 값이 복사되지 않도록 하기 위함이다.
	void push_back(const T& data);
	void pop_back(); // 실습2. pop_back 함수에 만약 size가 capacity / 8 보다 작을 경우
					//		  pData를 반으로 줄여 주는 기능을 구현하자.
	
	int size();// 값이 들어가있는 개수
	int capacity();// 값이 들어갈 수 있는 최대 개수

	T& operator[](int index);
	// 실습1. index에 있는 데이터 가져오는 at함수 구현
	T& at(int index);
	// 실습2. operator= 재정의 시도
	T& operator=(CMyVector& right);

	bool operator==(CMyVector& right);

	class iterator
	{
		friend CMyVector; // CMyVector 클래스가 iterator 클래스의 속성을 자유롭게 사용가능하다.
	private:
		CMyVector* pVector; //데이터를 벗어나는 
		T* pData;
		int m_index;

	public:
		iterator();
		iterator(CMyVector* pVector, T* pData, int m_index);
		T&			operator*();
		iterator&	operator++();
		iterator	operator++(int);
		iterator&	operator--();
		iterator	operator--(int);
		bool		operator==(const iterator& _other);
		bool		operator!=(const iterator& _other);

	};
	iterator begin();
	iterator end();
	
};

template<typename T>
CMyVector<T>::CMyVector()
{
	pDataArray = new T[100];
	m_size = 0;
	m_capacity = 100;
}

template<typename T>
CMyVector<T>::~CMyVector()
{
	//delete[] pData;
	m_size = 0;
	m_capacity = 0;
}

template<typename T>
void CMyVector<T>::push_back(const T& data)
{
	if (m_size >= m_capacity)
	{
		if (0 == m_capacity)
			m_capacity = 1;
		T* newData = new T[m_capacity * 2];
		for (int i = 0; i < m_size; i++)
		{
			newData[i] = pDataArray[i];
		}
		delete[] pDataArray;
		pDataArray = newData;
		m_capacity *= 2;
	}
	pDataArray[m_size] = data;
	m_size++;
}

// 실습 2
template<typename T>
void CMyVector<T>::pop_back()
{
	//1. push_back(0);
	//2. 만약에 data가 처음부터 없을때 pop_back();
	// size == 0
	if (m_size == 0)
		return;
	//pData[size-1] = NULL;
	// 뒤에 데이터가 들어있지만 모든 연산을 size까지만 조절한다면
	// 값을 무시해도 상관없다.
	m_size -= 1;
	if (m_size <= m_capacity / 2)
	{
		T* newData = new T[m_capacity / 2];
		for (int i = 0; i < m_size; i++)
		{
			newData[i] = pDataArray[i];
		}
		delete[] pDataArray;
		pDataArray = newData;
		m_capacity /= 2;
	}
}

template<typename T>
int CMyVector<T>::size()
{
	return m_size;
}

template<typename T>
int CMyVector<T>::capacity()
{
	return m_capacity;
}

template<typename T>
T& CMyVector<T>::operator[](int index)
{
	if (index >= m_size)
	{
		T* newDate = nullptr;
		return *newDate;
	}
	return pDataArray[index];
}

// 실습 1
template<typename T>
T& CMyVector<T>::at(int index)
{
	if (index >= m_size)
	{
		T* newDate = nullptr;
		return *newDate;
	}
	return pDataArray[index];
}

// 실습 3
// 생성과 동시에 =연산자를 사용하면 얕은 복사가 일어난다.
// 생성을 하고 대입을 다른 줄에 하면 깊은 복사가 일어난다.
template<typename T>
T& CMyVector<T>::operator=(CMyVector& right)
{
	T* newData = new T[right.capacity()];
	for (int i = 0; i < right.size(); i++)
	{
		newData[i] = right[i];
	}
	delete[] pDataArray;
	this->pDataArray = newData;
	this->m_size = right.size();
	this->m_capacity = right.capacity();

	return (T&)*this;
}

template<typename T>
bool CMyVector<T>::operator==(CMyVector& right)
{
	if(this->pDataArray == right.pDataArray)
		return true;
	return false;
}

template<typename T>
CMyVector<T>::iterator::iterator()
{
	this->pVector = nullptr;
	this->pData = nullptr;
	this->m_index = -1;
}

template<typename T>
CMyVector<T>::iterator::iterator(CMyVector* pVector, T* pData, int m_index)
{
	this->pVector = pVector;
	this->pData = pData;
	this->m_index = m_index;
}

template<typename T>
T& CMyVector<T>::iterator::operator*()
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우
	// 2. iterator가 가르키고 있는 곳에 데이터 아에 없는 경우
	// 3. iterator가 end() iterator일 때
	if (pVector->pDataArray != pData || pVector->m_size <= m_index || m_index == -1)
		assert(nullptr);

	return pData[m_index];
}

template<typename T>
typename CMyVector<T>::iterator& CMyVector<T>::iterator::operator++()
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우
	// 2. iterator가 마지막 데이터를 가리키고 있을 경우 : iterator end()로 만들어준다.
	// 3. iterator가 이미 end() iterator 였을 경우 : assert() 처리

	// 전위 연산자 (++iter)
	if ((pVector->pDataArray != pData) || -1 == m_index)
		assert(nullptr);

	if (pVector->size() - 1 == m_index)
	{
		m_index = -1;
	}
	else
	{
		m_index++;
	}
	return *this;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::iterator::operator++(int)
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우
	// 2. iterator가 이미 end() iterator였을 떄 assert();
	// 3. iterator가 마지막 데이터를 가리키고 있을 경우 : iterator end()로 만들어준다.

	// 후위 연산자 (iter++)
	// 전위 연산자와의 차이 : 현재 값을 가지는 임시 반복자를 만들고 해당 값을 반환한다.
	//						이때 내부의 코드는 전위 연산자와 같지만 이전의 값을 지닌 임시 반복자를 반환하므로
	//						증가된 값을 반환하지 않는다.
	iterator temp(pVector, pData, m_index);
	if ((pVector->pDataArray != this->pData) || -1 == m_index)
		assert(nullptr);

	if (pVector->size() - 1 == m_index)
	{
		m_index = -1;
	}
	else
	{
		m_index++;
	}

	return temp;
}

template<typename T>
typename CMyVector<T>::iterator& CMyVector<T>::iterator::operator--()
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우 
	// 2. iterator가 이미 begin() iterator였을 떄 assert()
	if ((pVector->pDataArray != this->pData) || 0 == m_index)
		assert(nullptr);

	m_index--;

	return *this;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::iterator::operator--(int)
{
	// 1. iterator가 Vector의 데이터 변경으로 잘못된 곳을 가르키고 있는 경우 
	// 2. iterator가 이미 begin() iterator였을 떄 assert()
	iterator temp(pVector, pData, m_index);
	if ((pVector->pDataArray != this->pData) || 0 == m_index)
		assert(nullptr);

	m_index--;

	return temp;
}

template<typename T>
bool CMyVector<T>::iterator::operator==(const iterator& _other)
{
	// 가리키는 벡터, 배열, 인덱스가 일치하면 true, 아니면 false
	if (this->pVector == _other.pVector &&
		this->pData == _other.pData &&
		this->m_index == _other.m_index)
		return true;
	return false;
}

template<typename T>
bool CMyVector<T>::iterator::operator!=(const iterator& _other)
{
	// 가리키는 벡터, 배열, 인덱스가 일치하면 false, 아니면 true
	if (this->pVector == _other.pVector &&
		this->pData == _other.pData &&
		this->m_index == _other.m_index)
		return false;
	return true;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::begin()
{
	iterator newIter(this, this->pDataArray, 0);
	return newIter;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::end()
{
	iterator newIter(this, this->pDataArray, -1);
	return newIter;
}
