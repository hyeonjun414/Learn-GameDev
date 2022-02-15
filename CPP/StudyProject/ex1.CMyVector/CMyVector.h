#pragma once

#include <iostream>

using namespace std;

template <typename T>
class CMyVector
{
private:
    T* m_dataArray;
    unsigned int m_size;
    unsigned int m_capacity;

public:
    CMyVector();
    ~CMyVector();

private:
    void init_vector();                         // Vector�� ó�� ����������� �ʿ��� �ʱ�ȭ ����
    void re_allocate(unsigned int resize);      // Vector�� ����� ũ�⸦ ������

public:
    unsigned int size();                        // Vector�� ���� ����Ǿ� �ִ� ������ ��
    unsigned int capacity();                 // Vector�� ������ �ִ� �������� ��뷮
    void push_back(const T& data);    // Vector�� ���� �ڿ� ������ �߰�
    void pop_back();                            // vector�� ���� �ڿ� ������ ����

public:
	class iterator
	{
		friend CMyVector;
	private:
		CMyVector* pVector;
		T* pData;
		int			m_index;

	public:
		iterator()
		{
			pVector = nullptr;
			pData = nullptr;
			m_index = -1;
		}
		iterator(CMyVector* pVector, T* pData, int index)
		{
			this->pVector = pVector;
			this->pData = pData;
			this->m_index = index;
		}
		~iterator()
		{

		}

		T& operator*();
		iterator& operator++();	// ����	--(iterator)
		iterator  operator++(int);	// ���� (iterator)++
		iterator& operator--();	// ���� --(iterator)
		iterator  operator--(int);	// ���� (iterator)--
		bool	  operator==(const iterator& _other);	// �񱳿����� ==
		bool	  operator!=(const iterator& _other);	// �񱳿����� !=
	};

	iterator begin();	// ���� iterator
	iterator end();	// �� iterator
	iterator insert(const iterator& iter, const T& value);
	iterator erase(const iterator& iter);
	T& operator[](unsigned int index);          // ���� ������ ������
};

template<typename T>
inline CMyVector<T>::CMyVector()
{
    init_vector();
}

template<typename T>
inline CMyVector<T>::~CMyVector()
{
    delete[] m_dataArray;
}

template<typename T>
inline void CMyVector<T>::init_vector()
{
    m_size = 0;
    m_capacity = 5;
    m_dataArray = new T[m_capacity];
}

template<typename T>
inline void CMyVector<T>::re_allocate(unsigned int resize)
{
    T* tempArray = new T[resize];

    for (int i = 0; i < m_size; i++)
       tempArray[i] =  m_dataArray[i];

    delete[] m_dataArray;
    m_dataArray = tempArray;
    m_capacity = resize;

}

template<typename T>
inline unsigned int CMyVector<T>::size()
{
    return m_size;
}

template<typename T>
inline unsigned int CMyVector<T>::capacity()
{
    return m_capacity;
}

template<typename T>
inline void CMyVector<T>::push_back(const T& data)
{
    if (m_size + 1 >= m_capacity)
        re_allocate(m_capacity * 2);

    m_dataArray[m_size] = data;
    m_size++;
}

template<typename T>
inline void CMyVector<T>::pop_back()
{
    if (m_size-1 <= m_capacity / 2)
        re_allocate(m_capacity / 2);

    m_size--;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::begin()
{
	return CMyVector<T>::iterator(this, m_dataArray, 0);
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::end()
{
	return iterator(this, m_dataArray, m_size+1);
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::insert(const iterator& iter, const T& value)
{
	if (m_size + 1 >= m_capacity)
		re_allocate(m_capacity * 2);

	int i;

	for (i = m_size; i >= iter.m_index; i--)
	{
		m_dataArray[i + 1] = m_dataArray[i];
	}

	m_dataArray[i] = value;
	m_size++;

	return iterator(iter.pVector, iter.pData, i);
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::erase(const iterator& iter)
{
	if (m_size - 1 < m_capacity / 2)
		re_allocate(m_capacity / 2);

	for (int i = m_size-1; i >= iter.m_index; i--)
	{
		m_dataArray[i] = m_dataArray[i+1];
	}
	m_size--;
	return iterator(iter.pVector, iter.pData, iter.m_index);
}

template<typename T>
inline T& CMyVector<T>::operator[](unsigned int index)
{
    return m_dataArray[index];
}

template<typename T>
inline T& CMyVector<T>::iterator::operator*()
{
	return pData[m_index];
}

template<typename T>
typename CMyVector<T>::iterator& CMyVector<T>::iterator::operator++()
{
	if (m_index >= pVector->m_size) return iterator();

	iterator tempIter = *this;
	m_index++;

	return tempIter;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::iterator::operator++(int)
{
	if (m_index >= pVector->m_size) return iterator();

	m_index++;

	return *this;
}

template<typename T>
typename CMyVector<T>::iterator& CMyVector<T>::iterator::operator--()
{
	if (m_index == 0) return iterator();

	m_index--;

	return *this;
}

template<typename T>
typename CMyVector<T>::iterator CMyVector<T>::iterator::operator--(int)
{
	if (m_index == 0) return iterator();

	iterator tempIter = *this;
	m_index--;

	return tempIter;
}

template<typename T>
inline bool CMyVector<T>::iterator::operator==(const iterator& _other)
{
	if (this->pVector == _other.pVector &&
		this->m_index == _other.m_index)
		return true;
	return false;
}

template<typename T>
inline bool CMyVector<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}
