#pragma once

#include<assert.h>

template <typename T> 
class CMyVector
{
private:
	T* pDataArray;
	unsigned int m_size; // ������ ������
	unsigned int m_capacity; // ���� ������ ����Ҹ� �� �ø��� �ʴ� ������ �Ҵ簡���� ��.

public:

	CMyVector();
	~CMyVector();

	// �Ű������� const�� �޴� ���� �Ű������� ������� �ʵ��� �����ϴ� ���̰�,
	// �����ڸ� ����ϴ� ���� ���� ���� ȣ���� �Ͼ �������� ���� ������� �ʵ��� �ϱ� �����̴�.
	void push_back(const T& data);
	void pop_back(); // �ǽ�2. pop_back �Լ��� ���� size�� capacity / 8 ���� ���� ���
					//		  pData�� ������ �ٿ� �ִ� ����� ��������.
	
	int size();// ���� ���ִ� ����
	int capacity();// ���� �� �� �ִ� �ִ� ����

	T& operator[](int index);
	// �ǽ�1. index�� �ִ� ������ �������� at�Լ� ����
	T& at(int index);
	// �ǽ�2. operator= ������ �õ�
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

// �ǽ� 2
template<typename T>
void CMyVector<T>::pop_back()
{
	//1. push_back(0);
	//2. ���࿡ data�� ó������ ������ pop_back();
	// size == 0
	if (m_size == 0)
		return;
	//pData[size-1] = NULL;
	// �ڿ� �����Ͱ� ��������� ��� ������ size������ �����Ѵٸ�
	// ���� �����ص� �������.
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

// �ǽ� 1
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

// �ǽ� 3
// ������ ���ÿ� =�����ڸ� ����ϸ� ���� ���簡 �Ͼ��.
// ������ �ϰ� ������ �ٸ� �ٿ� �ϸ� ���� ���簡 �Ͼ��.
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



