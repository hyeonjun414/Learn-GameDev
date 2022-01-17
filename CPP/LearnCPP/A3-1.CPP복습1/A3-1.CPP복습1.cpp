// A3-1.CPP복습1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


// # : 전처리 키워드
#include <iostream>

// #define : 앞에 키워드를 뒤에 식으로 그대로 변경된다.
// 그대로 변경되기 때문에 괄호처리를 해주는 것이 안전하다.
#define MAX 10;
#define SUM(A,B) A+B

using namespace std;

int main()
{
    cout << "기사가 드래곤을 쳤다." << endl;
// #ifdef은 앞에 정의된 키워드가 있을때 활성화된다.
// #ifndef로 디버그 반대로도 할수 있다.
// 디버그할때 내부의 확인을 위한 코드를 출력해야할때 유용하다.
#ifndef _DEBUG
    cout << "기사의 칼 데미지 13" << endl;
    cout << "드래곤의 방어력 3" << endl;
    cout << "13 - 3 = 10" << endl;
#endif
    cout << "기사가 드래곤에게 10데미지를 주었다." << endl;

    std::cout << "Hello World!\n";
}
