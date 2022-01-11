#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__)
#endif
using namespace std;

// 객체지향이란 : 프로그램에 필요한 데이터를 추상화시켜 객체로 분류하여 각각의 객체를 정의하여
//				 객체 간의 상호작용을 통해 프로그램을 만드는 것.
// 객체지향 3요소: 캡슐화, 상속, 다형성
// 1. 캡슐화 : 정보 은닉을 위해 클래스 내에서의 사용과 객체가 수행할 기능을 나눈다.
// 2. 상속 : 재사용성과 확장성을 위해 속성과 기능을 상속하는 부모 클래스와
//			 기능을 상속받는 자식 클래스가 존재한다.
// 3. 다형성 : 하나의 객체가 여러 형태를 가질 수 있는 것으로
//             부모 클래스의 함수를 재정의하여 자식 클래스에서 사용하는 오버라이딩과
//             같은 함수를 매개변수의 데이터형이나 개수를 다르게하여 다른 기능을 
//             수행하도록 하는 오버로딩을 통해 다형성을 실현한다.


class Player
{
private:
	string name;
	int maxHp;
	int hp;
	int damage;
	int defense;

public:
	Player()
	{
		name = "그냥용사";
		maxHp = hp = 100;
		damage = 10;
		defense = 10;
	}
	Player(string name)
	{
		this->name = name;
		this->maxHp = this->hp = 100;
		damage = 10;
		defense = 10;
	}
	void ShowInfo()
	{
		cout << "******************** 플레이어 정보 *******************" << endl;
		cout << "이  름 : " << name << endl;
		cout << "체  력 : " << hp << " / " << maxHp << endl;
		cout << "공격력 : " << damage << endl;
		cout << "방어력 : " << defense << endl;
		cout << "******************************************************" << endl;
	}

	int Attack()
	{
		return damage;
	}
	void Hit(int damage)
	{

	}
	void EquipWeapon()
	{

	}

};

class Monster
{
protected:
	string name;
	int hp;
	int damage;
	int defense;

public:
	void Attack(Player* player)
	{
	}
	void Skill(Player* player)
	{
	}
	void Hit(int damage)
	{
		cout << this->name << "은(는) " << this->damage << "의 피해를 입었습니다." << endl;
		this->hp = this->hp - damage < 0 ? 0 : this->hp - damage;
		if (this->hp == 0) Die();
	}
	bool Die()
	{
		if (this->hp == 0)
			return true;
		else
			return false;
	}
};
class Slime : public Monster
{
public :
	Slime(int number)
	{
		name = "슬라임" + to_string(number);;
		hp = 10;
		damage = 5;
		defense = 5;
	}
};
class Zombie : public Monster
{
public :
	Zombie(int number)
	{
		name = "좀비" + to_string(number);
		hp = 30;
		damage = 5;
		defense = 10;
	}
};
class Dragon : public Monster
{
public :
	Dragon()
	{
		name = "드래곤";
		hp = 50;
		damage = 10;
		defense = 10;
	}
};

class item
{

};
class Weapon : public item
{

};
class Armor : public item
{

};

#pragma region 외부 함수

Player* MakeCharacter()
{
	string name;
	cout << "플레이어의 이름을 정해주세요 : ";
	cin >> name;
	Player* player = new Player(name);
	player->ShowInfo();
	return player;
}
vector<Monster*> GenerateMonsters(int stageNum)
{
	vector<Monster*> monsterList;
	switch (stageNum)
	{
	case 1:
		cout << "슬라임 3마리가 생성되었습니다." << endl;
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Slime(i));
		break;
	case 2:
		cout << "좀비 2마리가 생성되었습니다." << endl;
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Zombie(i));
		break;
	case 3:
		cout << "드래곤이 출몰하였습니다." << endl;
		monsterList.push_back(new Dragon());
		break;
	}
	return monsterList;

}
int SelectAction()
{
	int num;
	cout << "*****************************" << endl;
	cout << "원하는 동작을 선택하세요 : " << endl;
	cout << "1. 공 격 " << endl;
	cout << "2. 스 킬 " << endl;
	cout << "3. 도 망 " << endl;
	cout << "*****************************" << endl;
	cin >> num;
	return num;
}

#pragma endregion
void WindowClear()
{
	int temp;
	cin >> temp;
	system("cls");
}



void Routine()
{
	/*
	1. 캐릭터 생성
	2. stage1. 몬스터 생성 -> Fight -> 전리품 획득(무기 하나가 확정으로 나옴)
	3. 정비 시간 ( 무기 장착 )
	4. stage2. 몬스터 생성 -> Fight -> 전리품 획득(방어구 하나가 확정으로 나옴)
	5. 정비 시간 ( 방어구 장착 )
	6. stage3. 몬스터 생성 -> Fight -> 승리 -> 끝
	*/
	// 1
	Player* player = MakeCharacter();
	int stageNum = 1;
	while (true)
	{
		vector<Monster*> monsterList = GenerateMonsters(stageNum);
		
		WindowClear();
	}
}
int main()
{
	Routine();
}