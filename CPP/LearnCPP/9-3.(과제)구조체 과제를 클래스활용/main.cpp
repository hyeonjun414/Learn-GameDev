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

#pragma region 전역 변수

int stageNum = 1; // 스테이지 진행도
int attackDelay = 500; // 공격 간격
int infoDelay = 1000; // 정보 확인 간격

#pragma endregion

#pragma region 캐릭터 클래스, 플레이어와 몬스터의 부모 클래스
class Character
{
protected:
	string name; // 이름
	int hp; // 체력
	int damage; // 공격력
	int defense; // 방어력

public:

	void ShowInfo() // 캐릭터 정보 출력
	{
		cout << "********** " << name << " ***********" << endl;
		cout << " 체  력 : " << hp << endl;
		cout << " 공격력 : " << damage << endl;
		cout << " 방어력 : " << defense << endl;
		cout << "******************************" << endl;
	}
	void ShowSimpleInfo() // 간단하게 정보 출력
	{
		cout << name << " 체력(" + to_string(this->hp) + ") 공격력(" + to_string(this->damage) + ") 방어력(" + to_string(this->defense) + ")\n\n";
	}
	int Attack() // 공격 함수
	{
		return damage;
	}
	void Hit(int damage) // 히트 함수
	{
		// 방어력 고려하여 데미지 적용
		int resultDamage = damage - this->defense < 0 ? 0 : damage - this->defense;
		cout << this->name << " 은(는) " << resultDamage << "의 피해를 입었습니다." << endl;
		this->hp = this->hp - resultDamage < 0 ? 0 : this->hp - resultDamage;
	}

	bool Die() // 죽었는지 확인
	{
		if (this->hp == 0)
		{
			cout << name << "이 체력이 0이 되어 쓰러졌습니다." << endl;
			return true;
		}
		else
			return false;
	}
};
#pragma endregion

#pragma region 플레이어 클래스
class Player : public Character
{

public:
	Player()
	{
		name = "그냥용사";
		hp = 100;
		damage = 10;
		defense = 2;
	}
	Player(string name)
	{
		this->name = name;
		this->hp = 100;
		damage = 10;
		defense = 2;
	}

	void Rest(int point) // 휴식, point만큼 체력회복
	{
		hp += point;
		cout << "휴식으로 플레이어의 체력이 " << point << " 만큼 회복되었습니다." << endl;
	}

	void Reinforce(int stageNum) // 강화, 스테이지당 한번 명상을 하여 캐릭터를 강화시킨다.
	{
		cout << "명상하여 강해집니다. 모든 수치가 증가합니다." << endl;
		this->hp += 20 * stageNum;
		this->damage += 10 * stageNum;
		this->defense += 2 * stageNum;
	}
};
#pragma endregion

#pragma region 몬스터 클래스
class Monster : public Character {
public:
	Monster(string name, int hp, int damage, int defense)
	{
		this->name = name;
		this->hp = hp;
		this->damage = damage;
		this->defense = defense;
	}
	Monster(int num, string name, int hp, int damage, int defense)
	{
		this->name = name + to_string(num);;
		this->hp = hp;
		this->damage = damage;
		this->defense = defense;
	}
};
#pragma endregion

#pragma region 외부 함수

// 캐릭터 생성 함수
Player* MakeCharacter()
{
	//string name;
	//cout << "플레이어의 이름을 정해주세요 : ";
	//cin >> name;
	Player* player = new Player("용사");
	player->ShowInfo();
	return player;
}
// 몬스터 생성 함수
vector<Monster*> GenerateMonsters(int stageNum)
{
	vector<Monster*> monsterList;
	cout << "\tSTAGE " << stageNum << endl;
	switch (stageNum)
	{
	case 1:
		cout << "슬라임 3마리가 나타났습니다." << endl;
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Monster(i + 1, "슬라임", 10, 5, 5));
		break;
	case 2:
		cout << "좀비 2마리가 나타났습니다." << endl;
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Monster(i + 1, "좀비", 30, 10, 10));
		break;
	case 3:
		cout << "드래곤이 출몰하였습니다." << endl;
		monsterList.push_back(new Monster("드래곤", 100, 30, 20));
		break;
	}
	return monsterList;
}
// Fight함수에서 행동을 선택하는 함수이다.
int SelectAction()
{
	int num;
	cout << "******************************\n" << endl;
	cout << " 1. 공       격 " << endl;
	cout << " 2. 상 태 확 인 " << endl;
	cout << " 3. 턴 넘 기 기 \n" << endl;
	cout << "******************************" << endl;
	cout << "원하는 동작을 선택하세요 : ";
	cin >> num;
	return num;
}
// 
void MonsterAttack(Player* player, vector<Monster*>& monsterList)
{
	for (int i = 0; i < monsterList.size(); i++)
	{
		Sleep(attackDelay);
		player->Hit(monsterList[i]->Attack());
	}
}

void AttackRoutine(Player* player, vector<Monster*>& monsterList)
{
	int num;
	// 플레이어 차례
	cout << "공격을 진행합니다. 누구를 공격하시겠습니까? \n" << endl;
	for (int i = 0; i < monsterList.size(); i++)
	{
		cout << i + 1 << ". ";
		monsterList[i]->ShowSimpleInfo();
	}
	cout << "공격할 대상 : ";
	cin >> num;
	if (num < 1)
		num = 1;
	else if (num > monsterList.size())
		num = monsterList.size();
	Sleep(attackDelay);
	monsterList[num - 1]->Hit(player->Attack());

	// 플레이어 공격에 따른 결과 처리
	for (int i = 0; i < monsterList.size();)
	{
		// 죽은 몬스터를 제외한다.
		if (monsterList[i]->Die())
			monsterList.erase(monsterList.begin() + i);
		else
			i++;
	}

	// 몬스터 차례, 만약 남은 몬스터가 있으면 공격을 진행
	// 없으면 전투를 끝내며 다음 스테이지로 넘어간다.
	if (!monsterList.empty())
	{
		MonsterAttack(player, monsterList);
	}
	else
	{
		cout << "스테이지 클리어 !!" << endl;
		return;
	}
}

void ShowMonsterInfo(vector<Monster*> monster)
{
	for (int i = 0; i < monster.size(); i++)
	{
		monster[i]->ShowInfo();
	}
}

void Fight(Player* player, vector<Monster*> monsterList)
{
	while (!(player->Die() || monsterList.size() == 0))
	{
		switch (SelectAction())
		{
		case 1: // 공격
			AttackRoutine(player, monsterList);
			Sleep(attackDelay);
			break;
		case 2: // 상태 확인
			player->ShowInfo();
			cout << "**********  몬스터  **********" << endl << endl;
			ShowMonsterInfo(monsterList);
			cout << "******************************" << endl;
			Sleep(infoDelay);
			break;
		case 3: // 턴넘김
			MonsterAttack(player, monsterList);
			Sleep(attackDelay);
			break;
		}
		system("cls");
	}
}

// 스테이지 중간 휴식 시간, 플레이어 상태와 휴식 기능, 장비를 장착할 수 있는 메뉴를 제공한다.
// 휴식은 스테이지마다 1회 제공
void RestTime(Player* player)
{
	int restPoint = 1;
	int reinforcePoint = 1;
	int num;
	while (true)
	{
		system("cls");
		cout << " 다음 스테이지 : STAGE " << stageNum + 1 << endl;
		cout << "******************************" << endl;
		cout << " 1. 현재 상태 확인 " << endl;
		cout << " 2. 휴식 ( 현재 남은 휴식 횟수 : " << restPoint << "회 )" << endl;
		cout << " 3. 명상 ( 현재 남은 명상 횟수 : " << reinforcePoint << "회)" << endl;
		cout << " 4. 휴식 종료, 다음 전투로! " << endl;
		cout << "******************************" << endl;
		cout << "원하는 동작을 선택하세요 : ";
		cin >> num;
		switch (num)
		{
		case 1: // 현재 상태 확인
			player->ShowInfo();
			Sleep(infoDelay);
			break;
		case 2:
			if (restPoint > 0)
			{
				player->Rest(10);
				restPoint--;
			}
			else
				cout << "휴식 횟수를 전부 사용했습니다." << endl;
			Sleep(infoDelay);
			break;
		case 3: // 명 상
			if (reinforcePoint > 0)
			{
				player->Reinforce(stageNum);
				reinforcePoint--;
			}
			else
				cout << "명상 횟수를 전부 사용했습니다." << endl;
			Sleep(infoDelay);
			break;
		case 4: // 다음 스테이지로
			cout << "다음 스테이지로 이동합니다." << endl;
			stageNum++;
			Sleep(infoDelay);
			return;
			break;
		}
	}
}

void EndGame()
{
	cout << "게임을 클리어 했습니다. 축하합니다!" << endl;
}

void destroy_vector(vector<Monster*>& v)
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}

#pragma endregion

void Routine()
{
	/*
	1. 캐릭터 생성
	2. stage1. 몬스터 생성 -> Fight -> 승리 -> 다음 스테이지
	3. 정비 시간 ( 휴식 및 명상(강화) )
	4. stage2. 몬스터 생성 -> Fight -> 승리 -> 다음 스테이지
	5. 정비 시간 ( 휴식 및 명상(강화) )
	6. stage3. 몬스터 생성 -> Fight -> 승리 -> 끝
	*/
	Player* player = MakeCharacter(); // 캐릭터 생성
	Sleep(infoDelay);
	while (stageNum < 4)
	{
		system("cls");
		vector<Monster*> monsterList = GenerateMonsters(stageNum);
		Fight(player, monsterList);
		RestTime(player);
		destroy_vector(monsterList);
	}
	EndGame();
	delete player;
}
int main()
{
	Routine();
	_CrtDumpMemoryLeaks(); // 메모리 릭 확인
}