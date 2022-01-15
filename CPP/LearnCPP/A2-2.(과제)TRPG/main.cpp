#pragma region 헤더, 디버그, using 관련
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__)
#endif

using namespace std;
#pragma endregion

#pragma region 전역 변수
enum STAGE {
	Town,
	Field,
};

int attackDelay = 500; // 공격 간격
int delayTime = 1000; // 대사 간격
bool isEnd = false; // 엔딩에 도달했는지
STAGE curSpace = Town; // 현재 위치
int curStage = 1; // 현재 진행 스테이지
#pragma endregion

#pragma region 클래스 선언부
class Character;
class Player;
class Warrior;
class Archor;
class Monster;
class Slime;
class Dragon;
class Item;
class Potion;
class Equip;
#pragma endregion

#pragma region 효과 및 시스템
void gotoxy(int x, int y) // 출력 커서 위치 변경
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Typing(string str) // 타이핑 효과
{
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
		Sleep(10);
	}
	cout << "\n\n";
}

void DestroyVector_Monster(vector<Monster*>& v) // 몬스터 동적할당 메모리 해제
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}
void DestroyVector_Item(vector<Item*>& v) // 아이템 동적할당 메모리 해제
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}
#pragma endregion

#pragma region 캐릭터 클래스, 플레이어와 몬스터의 부모 클래스
class Character
{
protected:
	string name; // 이름
	int maxHp; // 최대 체력
	int hp; // 체력
	int damage; // 공격력
	int defense; // 방어력

public:
	void SetDefense(int value)
	{
		defense += value;
	}
	int GetMaxHp()
	{
		return maxHp;
	}
	int GetHp()
	{
		return hp;
	}
	void SetHp(int value)
	{
		this->hp = this->hp + value > this->maxHp ? this->maxHp : this->hp + value;
		if (this->hp <= 0)
			Typing(this->name + "은 체력이 0이 되어 쓰러졌습니다.");
		if (value > 0)
			Typing(to_string(value) + "만큼의 체력을 회복하였습니다. 현재 체력 : " + to_string(this->hp));
		else
			Typing(to_string(value) + "만큼의 체력을 잃었습니다. 현재 체력 : " + to_string(hp));
	}
	virtual void ShowInfo() // 캐릭터 정보 출력
	{
		cout << "********** 정보 ***********" << endl;
		cout << " 체  력 : " << hp << endl;
		cout << " 공격력 : " << damage << endl;
		cout << " 방어력 : " << defense << endl;
		cout << "******************************" << endl;
	}
	void ShowSimpleInfo() // 간단하게 정보 출력
	{
		cout << "\t" << name << " 체력(" + to_string(this->hp) + ") 공격력(" + to_string(this->damage) + ") 방어력(" + to_string(this->defense) + ")\n\n";
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

#pragma region 아이템 관련 클래스
class Item
{
protected:
	string name;

public:
	string GetName()
	{
		return name;
	}
	void ShowItem()
	{
		cout << "\t" << this->name << endl;
	}
	virtual void Use(Character* player) = 0;
};

class Potion : public Item // 플레이어 체력 관련 아이템
{
	int value;

public:
	Potion(string name, int value)
	{
		this->name = name;
		this->value = value;
	}
	void Use(Character* player)
	{
		Typing("체력을 " + to_string(value) + " 만큼 회복합니다.");
		player->SetHp(value);
	}
};

class Equip : public Item // 캐릭터 방어력 관련 아이템
{
	int armor;
public :
	Equip(string name, int armor)
	{
		this->name = name;
		this->armor = armor;
	}
	void Use(Character* player)
	{
		Typing(name + "을 장착하여 방어력을 " + to_string(armor) + " 만큼 증가시킵니다.");
		player->SetDefense(armor);
	}
};
#pragma endregion



#pragma region 몬스터 관련 클래스
class Monster : public Character {
public:

	int exp;
	int gold;
	Monster(string name, int hp, int damage, int defense, int exp, int gold)
	{
		this->name = name;
		this->hp = hp;
		this->damage = damage;
		this->defense = defense;
		this->exp = exp;
		this->gold = gold;
	}
	Monster(int num, string name, int hp, int damage, int defense, int exp, int gold)
	{
		this->name = name + to_string(num);;
		this->hp = hp;
		this->damage = damage;
		this->defense = defense;
		this->exp = exp;
		this->gold = gold;
	}
};
#pragma endregion

void ShowMonsters(vector<Monster*> monsterList)
{
	cout << endl;
	for (int i = 0; i < monsterList.size(); i++)
	{
		cout << i + 1 << ". ";
		monsterList[i]->ShowSimpleInfo();
	}
	cout << endl;
}

#pragma region 플레이어 관련 클래스
class Player : public Character
{
protected:
	int level;
	int maxExp; // 최대 경험치
	int exp; // 현재 경험치
	int gold; // 현재 소지 골드
	

public :
	vector<Item*> inventory;
	
	void AddItem(Item* item) // 아이템 추가 함수
	{
		Typing(item->GetName() + " 을 가방에 추가하였습니다.");
		inventory.push_back(item);
	}

	int GetExp()
	{
		return exp;
	}
	void SetExp(int value)
	{
		exp += value;
		// 플레이어 레벨업 기능
		if (exp >= maxExp)
		{
			exp -= maxExp;
			maxExp *= 1.2;
			level++;
			maxHp += 5;
			hp += 5;
			damage += 5;
			defense += 2;
			Typing("플레이어가 레벨업 했습니다. 현재 레벨 : " + to_string(level));
		}
	}
	int GetGold()
	{
		return gold;
	}
	void SetGold(int value)
	{
		gold += value;
		if(value > 0)
			Typing(to_string(value) + "Gold를 습득했습니다. 현재 소지금 : " + to_string(gold) + " Gold");
		else
			Typing(to_string(value) + "Gold를 사용했습니다. 현재 소지금 : " + to_string(gold) + " Gold");
	}

	void ShowInventory() // 현재 인벤토리 상태를 보여준다.
	{
		if (inventory.empty())
		{
			cout << "\t\t현재 아이템이 없습니다." << endl;
			return;
		}
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << "\t" << i + 1 << ". ";
			inventory[i]->ShowItem();
		}
	}

	void UseInventoryItem(int index) // index에 맞는 인벤토리의 아이템을 사용한다.
	{
		inventory[index]->Use(this);
		inventory.erase(inventory.begin() + index);
	}

	void ShowInfo() // 캐릭터 정보 출력
	{
		cout << "******************** 캐릭터 정보 ***********************" << endl;
		cout << "\t 체  력 : " << hp      << "\t\t레  벨 : " << level << endl;
		cout << "\t 공격력 : " << damage  << "\t\t경험치 : " << exp << "/"<< maxExp << endl;
		cout << "\t 방어력 : " << defense << "\t\t보유금 : " << gold <<" Gold" << endl;
		cout << "---------------------- 인벤토리 ------------------------" << endl;
		ShowInventory();
		cout << "********************************************************" << endl;
	}
	
	virtual void Skill(vector<Monster*>& monsterList) = 0;
};
class Warrior : public Player
{
public :
	Warrior(string name)
	{
		this->name = name;
		this->maxHp = 100;
		this->hp = 100;
		this->damage = 10;
		this->defense = 10;
		this->level = 1;
		this->maxExp = 10;
		this->exp = 0;
		this->gold = 100;
	}
	void ShowInfo() // 캐릭터 정보 출력
	{
		Player::ShowInfo();
		cout << "---------------------- 보유기술 ------------------------" << endl;
		cout << "\t\t파워 슬래시" << endl;
		cout << "********************************************************" << endl;
	}
	void Skill(vector<Monster*>& monsterList)
	{
		int select;
		Typing("\t\t전사! 파워 슬래시!!!");
		ShowMonsters(monsterList);
		cout << "누구에게 스킬을 사용하시겠습니까? :";
		cin >> select;
		if (select < 1) select = 1;
		else if (select > monsterList.size()) select = monsterList.size();
		monsterList[select - 1]->Hit(Attack() * 2);
		cout << endl;
	}
};
class Archor : public Player
{
public :
	Archor(string name)
	{
		this->name = name;
		this->hp = 100;
		this->damage = 10;
		this->defense = 10;
		this->level = 1;
		this->maxExp = 10;
		this->exp = 0;
		this->gold = 100;
	}
	void ShowInfo() // 캐릭터 정보 출력
	{
		Player::ShowInfo();
		cout << "----------------------- 보유기술 ------------------------" << endl;
		cout << "\t\t멀티 샷" << endl;
		cout << "********************************************************" << endl;
	}
	void Skill(vector<Monster*>& monsterList)
	{
		Typing("\t\t궁수! 멀티 샷!!!");
		for (int i = 0; i < monsterList.size(); i++)
		{
			monsterList[i]->Hit(Attack());
			Sleep(attackDelay);
		}
		cout << endl;
	}
};
#pragma endregion



#pragma region 외부 함수
void OpeningScene()
{
	vector<vector<string>> str = { 
		{
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		},
		{
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
		"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■■□■■■■■■□■■■■■■■■■",
		"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■□■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■□□□□□□□■■■■■■■■■■■■■□■■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■□■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■■□■■■□■■■■■■■■■■■■□■■■□■■■■■■□□□□□■■■■■",
		"■■■■■□□□□□□□□□□□□□□□□■■■■■□■■■■■□■■■■■□■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■□■■■■■□■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
		"■■■■■■■■■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
		}

	};
	
	for (int i = 0; i < str.size(); i++)
	{
		gotoxy(0, 0);
		for(int j = 0; j < str[i].size(); j++)
			Typing(str[i][j]);
		Sleep(200);
	}
	Sleep(delayTime);
	system("cls");
}
void EndingScene()
{
	vector<vector<string>> str = {
	{
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	},
	{
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
	"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■■□■■■■■■□■■■■■■■■■",
	"■■■■■■■■□■■■■■■■□■■■■■■■■■■■■■□■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■□□□□□□□■■■■■■■■■■■■■□■■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■□■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■■□■■■□■■■■■■■■■■■■□■■■□■■■■■■□□□□□■■■■■",
	"■■■■■□□□□□□□□□□□□□□□□■■■■■□■■■■■□■■■■■□■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■□■■■■■□■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■",
	"■■■■■■■■■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	}

	};

	for (int i = 0; i < str.size(); i++)
	{
		gotoxy(0, 0);
		for (int j = 0; j < str[i].size(); j++)
			Typing(str[i][j]);
		Sleep(500);
	}
}

#pragma region 캐릭터 관련
Player* MakePlayer() // 캐릭터 생성 함수
{
	string name;
	int selectNum;
	Player* player;
	Typing("안녕하세요... 용사여..당신의 이름을 알려주세요..");
	cout << "이름을 입력하세요 : ";
	cin >> name;
	cout << endl;
	Typing(name + "... 좋은 이름이군요.. 그럼 당신의 직업은 무엇인가요..?");
	Typing("1. 전사\t2. 궁수");
	cout << "숫자를 입력해주세요 : ";
	cin >> selectNum;
	cout << endl;
	switch (selectNum)
	{
	case 1:
		player = new Warrior(name);
		Typing("당신은 전사군요! 전사는 한명의 적에게 일반 공격보다 4배 강한 파워 슬래시를 사용할 수 있어요.");
		break;
	case 2:
	default:
		player = new Archor(name);
		Typing("당신은 궁수군요! 아처는 전투 중인 모든 적을 공격할 수 있는 멀티샷을 사용할 수 있어요.");
		break;
	}
	Sleep(500);
	player->ShowInfo();
	cout << endl;
	Typing("당신의 능력치는 보는 바와 같이 아직 너무 약해요..");
	Sleep(500);
	Typing("열심히 싸우고 성장해서 세상을 구해주세요..");

	system("pause");
	system("cls");

	return player;
}
#pragma endregion

#pragma region 마을 관련
void GoShop(Player* player) // 상점 루틴
{
	int select1, select2;
	while (true)
	{
		system("cls");

		Typing("뭔가 쓸모없는게 많아 보이는 상점이다...");
		Typing("상점 주인 : 돈이 있으면 많이들 사가라고");
		cout << endl;
		Typing("당신은 무엇을 하고 싶은가? 현재 소지금 : " + to_string(player->GetGold()) + " Gold");
		Typing("1. 나의 상태를 확인한다.");
		Typing("2. 아이템을 구매한다.");
		Typing("3. 마을로 돌아간다.");
		cout << " 당신의 선택 : ";
		cin >> select1;
		cout << endl;
		switch (select1)
		{
		case 1: // 플레이어 상태 확인
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // 아이템 구매
			Typing("******************** 아이템 목록 ***********************");
			Typing("\t\t1. 회복포션 (소) : 15  Gold");
			Typing("\t\t2. 회복포션 (중) : 30  Gold");
			Typing("\t\t3.  티타늄 갑옷  : 150 Gold");
			cout << "어떤 아이템을 구매하시겠습니까? :";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1:
				if (player->GetGold() >= 15)
				{
					Typing("\t회복포션 (소) 을 구매하였습니다.");
					player->SetGold(-15);
					player->AddItem(new Potion("회복 포션 (소)", 10));
				}
				else
					Typing("돈이 부족해.");
				break;
			case 2:
				if (player->GetGold() >= 30)
				{
					Typing("\t회복포션 (중) 을 구매하였습니다.");
					player->SetGold(-30);
					player->AddItem(new Potion("회복 포션 (중)", 20));
				}
				else
					Typing("돈이 부족해.");
			case 3:
				if (player->GetGold() >= 150)
				{
					Typing("\t티타늄 갑옷 을 구매하였습니다.");
					player->SetGold(-150);
					player->AddItem(new Equip("티타늄 갑옷", 100));
				}
				else
					Typing("돈이 부족해.");
				break;
			}
			Sleep(delayTime);
			break;

		case 3: // 마을로 돌아가기.
			Typing("상점 주인 : 모험에 필요한게 있다면 또 오라고.");
			Sleep(delayTime);
			return;
			break;
		}
	}
}
void GoRest(Player* player) // 휴식(여관) 루틴
{
	int select;
	while (true)
	{
		system("cls");

		Typing("아늑해 보이는 여관이다...");
		Typing("여관 주인 : 피곤하면 조금 쉬고가라고 허허..");
		cout << endl;
		Typing("당신은 무엇을 하고 싶은가? 현재 소지금 : " + to_string(player->GetGold()) + " Gold");
		Typing("1. 나의 상태를 확인한다.");
		Typing("2. 휴식한다 ( 30 Gold )");
		Typing("3. 마을로 나간다.");
		cout << endl;
		cout << " 당신의 선택 : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // 플레이어 상태 확인
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // 휴식
			if (player->GetGold() < 30)
			{
				Typing("돈이 모자라구만, 다음에 다시오게나.");
			}
			else if (player->GetHp() < player->GetMaxHp())
			{
				Typing("잘가게나!");
				player->SetHp(30);
				player->SetGold(-30);
			}
			else
				Typing("이미 체력이 가득차있구만 휴식은 체력이 없을 때 하는거라네!");
			Sleep(delayTime);
			break;
		case 3: // 마을로 돌아가기.
			Typing("여관 주인 : 다음에 또 들려주시게.");
			Sleep(delayTime);
			return;
			break;
		}
	}
}

void GoTown(Player* player) // 마을 루틴
{
	int select;
	while (true)
	{
		system("cls");

		Typing("한적하고 평화로운 마을이다...");
		cout << endl;
		Typing("당신은 무엇을 하고 싶은가?");
		Typing("1. 나의 상태를 확인한다.");
		Typing("2. 아이템을 구매한다.");
		Typing("3. 여관에서 휴식한다.");
		Typing("4. 필드로 나간다.");
		cout << endl;
		cout << " 당신의 선택 : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // 플레이어 상태 확인
			player->ShowInfo(); Sleep(delayTime); break;
		case 2: // 아이템 구매
			GoShop(player); break;
		case 3: // 휴식하기
			GoRest(player); break;
		case 4: // 필드로 나가기
			curSpace = Field; return; break;
		}
	}

}
#pragma endregion

#pragma region 필드 관련
vector<Monster*> GenerateMonsters(int stageNum) // 몬스터 생성 함수
{
	vector<Monster*> monsterList;
	switch (stageNum)
	{
	case 1:
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Monster(i + 1, "슬라임", 10, 5, 5, 5, 10));
		break;
	case 2:
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Monster(i + 1, "좀비", 20, 15, 15, 7, 20));
		break;
	case 3:
		monsterList.push_back(new Monster("드래곤", 100, 120, 20, 20, 100));
		break;
	}
	return monsterList;
}

void MonsterAttack(Player* player, vector<Monster*>& monsterList) // 몬스터가 플레이어를 공격하는 함수
{
	// 플레이어 공격에 따른 결과 처리
	for (int i = 0; i < monsterList.size();)
	{
		// 죽은 몬스터를 삭제하고 해당 몬스터의 경험치와 골드만큼을 플레이어에 추가한다.
		if (monsterList[i]->Die())
		{
			player->SetExp(monsterList[i]->exp);
			player->SetGold(monsterList[i]->gold);
			monsterList.erase(monsterList.begin() + i);
			Sleep(attackDelay);
		}
		else
			i++;
	}
	// 남아 있는 몬스터는 플레이어에게 공격을 수행한다.
	for (int i = 0; i < monsterList.size(); i++)
	{
		Sleep(attackDelay);
		player->Hit(monsterList[i]->Attack());
	}
}

void GoBattle(Player* player) // 전투 루틴
{
	vector<Monster*> monsters = GenerateMonsters(curStage);
	int select1;
	int select2;
	int select3;
	while (true)
	{
		system("cls");
		// 등장한 몬스터를 모두 잡으면 전투를 마치고 필드로 돌아간다.
		if (monsters.empty())
		{
			Typing("모든 몬스터를 무찔렀다. 일단 마을 앞으로 돌아가자.");
			curStage++;
			if (curStage == 3)
			{
				Typing("마지막으로 남은 드래곤은 강력한 발톱을 가지고 있다고 한다.");
				Typing("가능하면 방어구를 맞추는게 좋을 것 같다.");
			}
			if(curStage == 4) isEnd = true;
			Sleep(delayTime);
			return;
		}
		Typing("\t\t몬스터 " + to_string(monsters.size()) + "마리가 당신의 앞에 서있다.");
		ShowMonsters(monsters);
		player->ShowInfo();
		cout << endl;
		Typing("당신은 무엇을 하고 싶은가?");
		Typing("1. 몬스터를 공격한다.");
		Typing("2. 아이템을 사용한다.");
		Typing("3. 도망간다. ( 50% )");
		cout << endl;
		cout << " 당신의 선택 : ";
		cin >> select1;
		cout << endl;
		switch (select1)
		{
		case 1: // 공격
			cout << endl;
			Typing("당신은 무엇을 하고 싶은가?");
			Typing("1. 일반공격");
			Typing("2. 스킬사용");
			Typing("3. 이전화면");
			cout << endl;
			cout << " 당신의 선택 : ";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1: // 일반 공격
				ShowMonsters(monsters);
				cout << "누구를 공격하시겠습니까? :";
				cin >> select3;
				cout << endl;
				if (select3 < 1) select3 = 1;
				else if (select3 > monsters.size()) select3 = monsters.size();
				monsters[select3-1]->Hit(player->Attack());
				MonsterAttack(player, monsters);
				Sleep(delayTime);
				break;
			case 2 : // 스킬 사용
				player->Skill(monsters);
				MonsterAttack(player, monsters);
				break;
			}
			Sleep(delayTime);
			break;
		case 2: // 아이템 사용
			Typing(" 플레이어의 인벤토리 ");
			player->ShowInventory();
			Typing("당신은 무엇을 하고 싶은가?");
			Typing("1. 아이템 사용");
			Typing("2. 이전 화면");
			cout << endl;
			cout << " 당신의 선택 : ";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1: 
				cout << "몇 번 슬롯의 아이템을 사용하시겠습니까? :";
				cin >> select3;
				cout << endl;
				if (select3 < 1) select3 = 1;
				else if (select3 > monsters.size()) select3 = monsters.size();
				if (select3 <= player->inventory.size())
					player->UseInventoryItem(select3-1);
				else
					Typing("해당 번호의 아이템이 없습니다.");
				Sleep(delayTime);
			}
			break;
		case 3: // 도망
			select3 = rand() % 2;
			if (select3 == 0)
			{
				Typing("몬스터의 추적에 도망에 실패했다.");
				MonsterAttack(player, monsters);
				Sleep(delayTime);
			}
			else
			{
				Typing("무사히 마을 앞까지 도망쳤다.");
				Sleep(delayTime);
				return;
			}
			break;
		}
	}
}
void GoField(Player* player) // 필드 루틴
{
	int select;
	while (true)
	{
		system("cls");
		if (curStage > 3) return;
		Typing("이번 스테이지 : STAGE " + to_string(curStage));
		Typing("마을 밖은 왠지 모를 불길한 분위기를 풍긴다...");
		cout << endl;
		Typing("당신은 무엇을 하고 싶은가?");
		Typing("1. 나의 상태를 확인한다.");
		Typing("2. 전투를 시작한다.");
		Typing("3. 마을로 돌아간다.");
		cout << endl;
		cout << " 당신의 선택 : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // 상태 확인
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // 전투
			GoBattle(player);
			break;
		case 3: // 마을로 돌아가기
			curSpace = Town;
			return;
			break;
		}
	}
}

#pragma endregion



void Routine()
{
	//OpeningScene();
	Player* player = MakePlayer();
	while (!isEnd)
	{
		system("cls");

		switch (curSpace)
		{
		case Town:
			GoTown(player);
			break;
		case Field:
			GoField(player);
			break;
		}
	}
	delete player;
	EndingScene();
}
int main()
{
	Routine();
	_CrtDumpMemoryLeaks(); // 메모리 릭 확인
}