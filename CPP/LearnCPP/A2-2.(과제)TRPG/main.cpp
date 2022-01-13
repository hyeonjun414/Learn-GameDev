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

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

enum STAGE {
	Town,
	Field,
};
enum TOWN {
	Shop,
	RestSpace,
};
enum FIELD {
	Stage1,
	Stage2,
	StageBoss,
};


#pragma region 전역 변수

int stageNum = 1; // 스테이지 진행도
int attackDelay = 500; // 공격 간격
int infoDelay = 500; // 정보 확인 간격
bool isEnd = false;
STAGE curSpace = TOWN;
FIELD curStage = Stage1;
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

#pragma region 아이템 관련 클래스
class Item
{
	string name;
public:
	void ShowItem()
	{
		cout << "\t\t" << this->name << endl;
	}
};
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
protected:
	int level;
	int maxExp;
	int exp;
	int money;
	vector<Item*> inventory;

public :
	void ShowInventory()
	{
		if (inventory.empty())
		{
			cout << "\t\t현재 아이템이 없습니다." << endl;
			return;
		}
		for (int i = 0; i < inventory.size(); i++)
		{
			inventory[i]->ShowItem();
		}
	}
	void ShowInfo() // 캐릭터 정보 출력
	{
		cout << "********************* 캐릭터 정보 ***********************" << endl;
		cout << "\t 체  력 : " << hp      << "\t\t레  벨 : " << level << endl;
		cout << "\t 공격력 : " << damage  << "\t\t경험치 : " << exp << "/"<< maxExp << endl;
		cout << "\t 방어력 : " << defense << "\t\t보유금 : " << money <<" 골드" << endl;
		cout << "----------------------- 인벤토리 ------------------------" << endl;
		ShowInventory();
		cout << "********************************************************" << endl;
	}
};

class Warrior : public Player
{
public :
	Warrior(string name)
	{
		this->name = name;
		this->hp = 100;
		this->damage = 10;
		this->defense = 10;
		this->level = 1;
		this->maxExp = 10;
		this->exp = 0;
		this->money = 100;
	}
	void ShowInfo() // 캐릭터 정보 출력
	{
		Player::ShowInfo();
		cout << "----------------------- 보유기술 ------------------------" << endl;
		cout << "\t\t파워 슬래시" << endl;
		cout << "********************************************************" << endl;
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
		this->money = 100;
	}
	void ShowInfo() // 캐릭터 정보 출력
	{
		Player::ShowInfo();
		cout << "----------------------- 보유기술 ------------------------" << endl;
		cout << "\t\t파워 슬래시" << endl;
		cout << "********************************************************" << endl;
	}
};
#pragma endregion


#pragma region 몬스터 관련 클래스
class Monster : public Character {
	int exp;
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
void Typing(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
		Sleep(10);
	}
	cout << endl;
}
void Typing(string str, float time)
{
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
		Sleep(time);
	}
	Sleep(100);
	cout << endl;
}

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
			Typing(str[i][j], 0);
		Sleep(500);
	}
	Sleep(1500);
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
			Typing(str[i][j], 0);
		Sleep(500);
	}
}

Player* MakePlayer()
{
	string name;
	int selectNum;
	Player* player;
	Typing("안녕하세요... 용사여..당신의 이름을 알려주세요..");
	cout << "이름을 입력하세요 : ";
	cin >> name;
	Typing(name + "... 종은 이름이군요.. 그럼 당신의 직업은 무엇인가요..?");
	cout << "1. 전사\t2. 궁수 \n숫자를 입력해주세요 : ";
	cin >> selectNum;
	switch (selectNum)
	{
	case 1 :
		player = new Warrior(name);
		Typing("당신은 전사군요! 전사는 한명의 적에게 일반 공격보다 4배 강한 파워 슬래시를 사용할 수 있어요.");
		break;
	case 2 :
	default:
		player = new Archor(name);
		Typing("당신은 궁수군요! 아처는 전투 중인 모든 적을 공격할 수 있는 멀티샷을 사용할 수 있어요.");
		break;
	}
	Sleep(infoDelay);
	player->ShowInfo();
	Typing("당신의 능력치는 보는 바와 같이 아직 너무 약해요..");
	Sleep(infoDelay);
	Typing("열심히 싸우고 성장해서 세상을 구해주세요..");

	system("pause");
	system("cls");

	return player;
}

// 몬스터 생성 함수
vector<Monster*> GenerateMonsters(int stageNum)
{
	vector<Monster*> monsterList;
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

void GoTown(Player* player)
{

}
void GoField(Player* player)
{

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
	OpeningScene();
	Player* player = MakePlayer();
	while (!isEnd)
	{
		switch (curStage)
		{
		case Town:
			GoTown(player);
			break;
		case Field:
			GoField(player);
			break;
		}
	}
}
int main()
{
	Routine();
	_CrtDumpMemoryLeaks(); // 메모리 릭 확인
}