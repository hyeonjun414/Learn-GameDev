// A5-1.클래스복습.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

#include "CDragon.h"

using namespace std;


class MyClass
{

// private : 사적 - 클래스 내부에서만 사용이 가능하다.
private :
// protected : 보호 - 클래스와 상속에 관여되는 클래스에서 사용이 가능하다.
protected:
// public : 공공 - 클래스 외부에서 사용이 가능하다.
public :
	int id;
	int GetId() { return id; }
};

class Dragon {
	unsigned int hp;
	unsigned int damage;
	unsigned int armor;

	int CalculateCombat() {
		return hp - (damage - armor);
	}

public:
	unsigned int GetHp()	 { return hp;	  }
	unsigned int GetDamage() { return damage; }
	unsigned int GetArmor()	 { return armor;  }

	// private로 선언된 함수를 이용해서 전투 결과를 얻을 수 있다.
	unsigned int ResultCombatHp() { return CalculateCombat(); }
	
};

int main()
{
	
	MyClass myClass;
	myClass.id;
	myClass.GetId();

	string str = "aaaa";

	Dragon dragon;
	dragon.GetHp(); // public으로 선언된 함수를 이용해서 private로 선언된 변수에 접근할 수 있다.

	CGun gun;
	gun.attack();

}
