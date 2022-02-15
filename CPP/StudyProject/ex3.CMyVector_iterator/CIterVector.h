#pragma once
template <typename T>
class CMyVector
{
private:
	T* pDataArray;	// Vector�� �����͸� ��� ���� �迭�� �����Ҵ� �� �ּҰ�
	unsigned int	m_size;		// Vector ���� �迭�� �� �ִ� �������� ��
	unsigned int	m_capacity;	// Vector ���� �迭�� �� �� �ִ� ��뷮

public:
	CMyVector();
	~CMyVector();

	(����)

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
};
