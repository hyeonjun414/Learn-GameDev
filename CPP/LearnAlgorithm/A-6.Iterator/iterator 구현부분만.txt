// CMyVector의 iterator 부분과 begin(), end() 함수 
class iterator
{
	friend CMyVector; // CMyVector 클래스가 iterator 클래스의 속성을 자유롭게 사용가능하다.
private:
	CMyVector* pVector;
	T* pData;
	int m_index;

public:
	// 선언부
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

...
...


// 구현부
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
