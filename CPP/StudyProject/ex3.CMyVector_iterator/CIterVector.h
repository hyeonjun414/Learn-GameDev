#pragma once
template <typename T>
class CMyVector
{
private:
	T* pDataArray;	// Vector가 데이터를 담기 위한 배열을 동적할당 한 주소값
	unsigned int	m_size;		// Vector 동적 배열에 들어가 있는 데이터의 수
	unsigned int	m_capacity;	// Vector 동적 배열에 들어갈 수 있는 허용량

public:
	CMyVector();
	~CMyVector();

	(생략)

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
		iterator& operator++();	// 전위	--(iterator)
		iterator  operator++(int);	// 후위 (iterator)++
		iterator& operator--();	// 전위 --(iterator)
		iterator  operator--(int);	// 후위 (iterator)--
		bool	  operator==(const iterator& _other);	// 비교연산자 ==
		bool	  operator!=(const iterator& _other);	// 비교연산자 !=
	};

	iterator begin();	// 시작 iterator
	iterator end();	// 끝 iterator
	iterator insert(const iterator& iter, const T& value);
	iterator erase(const iterator& iter);
};
