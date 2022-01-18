// A4-1.비트연산자.modepp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define MODE_FULLSCREEN (1 << 0)
#define MODE_MAXIMAZE	(1 << 1)
#define MODE_MINIMIZE	(1 << 2)

using namespace std;

int main()
{
	// &&, ||, ! 관계 연산자
	
	int i = 1;
	// 시프트 연산자 : << , >>
	// 비트는 그대로 통째로 옮기는 기능
	i = i << 8;

	// &, | : and, or
	int left = 0x0011; // 0000 0000 0001 0001
	int right = 0x0010; // 0000 0000 0001 0000

	char a = left & right; // 0001 0000
	char b = left | right; // 0001 0001

	// ~ : not
	char mode = 0x00; //  0000 0001 - 풀스크린만 활성화

	// 특정 플래그 활성화
	mode = mode | MODE_FULLSCREEN;	// 0000 0000
									// 0000 0001
									// 0000 0001
	// 특정 플래그 비활성화
	mode = mode ^ MODE_FULLSCREEN;  // 0000 0001
									// 0000 0001
									// 0000 0000

	// \ : 전처리기에서 다음줄까지 받아들이도록 한다.

	cout << mode << endl;
}
