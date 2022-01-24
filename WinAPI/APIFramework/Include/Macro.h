// Macro.h
// 
// 메모리 해제 매크로
// 만약 메모리주소가 있을 경우 메모리를 해제하고 널 포인터로 바꿔준다.
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
// 동적할당의 경우
#define SAGE_DELETE_ARRAY(p) if(p) {delete[] p; p = NULL}

// 싱클톤 클래스를 자동으로 만들어주는 매크로
#define DECLARE_SINGLE(Type) \
private:\
	static Type* m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst) m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL;

#define GET_SINGLE(Type) Type::GetInst() // 싱글톤 객체 얻어옴.
#define DESTORY_SINGLE(Type) Type::DestroyInst() // 싱글톤 메모리를 해제.