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



