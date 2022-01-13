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


#pragma region ���� ����

int stageNum = 1; // �������� ���൵
int attackDelay = 500; // ���� ����
int infoDelay = 500; // ���� Ȯ�� ����
bool isEnd = false;
STAGE curSpace = TOWN;
FIELD curStage = Stage1;
#pragma endregion

#pragma region Ŭ���� �����
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

#pragma region ������ ���� Ŭ����
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

#pragma region ĳ���� Ŭ����, �÷��̾�� ������ �θ� Ŭ����
class Character
{
protected:
	string name; // �̸�
	int hp; // ü��
	int damage; // ���ݷ�
	int defense; // ����

public:

	virtual void ShowInfo() // ĳ���� ���� ���
	{
		cout << "********** ���� ***********" << endl;
		cout << " ü  �� : " << hp << endl;
		cout << " ���ݷ� : " << damage << endl;
		cout << " ���� : " << defense << endl;
		cout << "******************************" << endl;
	}
	void ShowSimpleInfo() // �����ϰ� ���� ���
	{
		cout << name << " ü��(" + to_string(this->hp) + ") ���ݷ�(" + to_string(this->damage) + ") ����(" + to_string(this->defense) + ")\n\n";
	}
	int Attack() // ���� �Լ�
	{
		return damage;
	}
	void Hit(int damage) // ��Ʈ �Լ�
	{
		// ���� ����Ͽ� ������ ����
		int resultDamage = damage - this->defense < 0 ? 0 : damage - this->defense;
		cout << this->name << " ��(��) " << resultDamage << "�� ���ظ� �Ծ����ϴ�." << endl;
		this->hp = this->hp - resultDamage < 0 ? 0 : this->hp - resultDamage;
	}

	bool Die() // �׾����� Ȯ��
	{
		if (this->hp == 0)
		{
			cout << name << "�� ü���� 0�� �Ǿ� ���������ϴ�." << endl;
			return true;
		}
		else
			return false;
	}
};
#pragma endregion

#pragma region �÷��̾� Ŭ����
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
			cout << "\t\t���� �������� �����ϴ�." << endl;
			return;
		}
		for (int i = 0; i < inventory.size(); i++)
		{
			inventory[i]->ShowItem();
		}
	}
	void ShowInfo() // ĳ���� ���� ���
	{
		cout << "********************* ĳ���� ���� ***********************" << endl;
		cout << "\t ü  �� : " << hp      << "\t\t��  �� : " << level << endl;
		cout << "\t ���ݷ� : " << damage  << "\t\t����ġ : " << exp << "/"<< maxExp << endl;
		cout << "\t ���� : " << defense << "\t\t������ : " << money <<" ���" << endl;
		cout << "----------------------- �κ��丮 ------------------------" << endl;
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
	void ShowInfo() // ĳ���� ���� ���
	{
		Player::ShowInfo();
		cout << "----------------------- ������� ------------------------" << endl;
		cout << "\t\t�Ŀ� ������" << endl;
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
	void ShowInfo() // ĳ���� ���� ���
	{
		Player::ShowInfo();
		cout << "----------------------- ������� ------------------------" << endl;
		cout << "\t\t�Ŀ� ������" << endl;
		cout << "********************************************************" << endl;
	}
};
#pragma endregion


#pragma region ���� ���� Ŭ����
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

#pragma region �ܺ� �Լ�
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
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		},
		{
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
		"�������������������������������������������������",
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
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	},
	{
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
	"�������������������������������������������������",
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
	Typing("�ȳ��ϼ���... ��翩..����� �̸��� �˷��ּ���..");
	cout << "�̸��� �Է��ϼ��� : ";
	cin >> name;
	Typing(name + "... ���� �̸��̱���.. �׷� ����� ������ �����ΰ���..?");
	cout << "1. ����\t2. �ü� \n���ڸ� �Է����ּ��� : ";
	cin >> selectNum;
	switch (selectNum)
	{
	case 1 :
		player = new Warrior(name);
		Typing("����� ���籺��! ����� �Ѹ��� ������ �Ϲ� ���ݺ��� 4�� ���� �Ŀ� �����ø� ����� �� �־��.");
		break;
	case 2 :
	default:
		player = new Archor(name);
		Typing("����� �ü�����! ��ó�� ���� ���� ��� ���� ������ �� �ִ� ��Ƽ���� ����� �� �־��.");
		break;
	}
	Sleep(infoDelay);
	player->ShowInfo();
	Typing("����� �ɷ�ġ�� ���� �ٿ� ���� ���� �ʹ� ���ؿ�..");
	Sleep(infoDelay);
	Typing("������ �ο�� �����ؼ� ������ �����ּ���..");

	system("pause");
	system("cls");

	return player;
}

// ���� ���� �Լ�
vector<Monster*> GenerateMonsters(int stageNum)
{
	vector<Monster*> monsterList;
	switch (stageNum)
	{
	case 1:
		cout << "������ 3������ ��Ÿ�����ϴ�." << endl;
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Monster(i + 1, "������", 10, 5, 5));
		break;
	case 2:
		cout << "���� 2������ ��Ÿ�����ϴ�." << endl;
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Monster(i + 1, "����", 30, 10, 10));
		break;
	case 3:
		cout << "�巡���� ����Ͽ����ϴ�." << endl;
		monsterList.push_back(new Monster("�巡��", 100, 30, 20));
		break;
	}
	return monsterList;
}
// Fight�Լ����� �ൿ�� �����ϴ� �Լ��̴�.
int SelectAction()
{
	int num;
	cout << "******************************\n" << endl;
	cout << " 1. ��       �� " << endl;
	cout << " 2. �� �� Ȯ �� " << endl;
	cout << " 3. �� �� �� �� \n" << endl;
	cout << "******************************" << endl;
	cout << "���ϴ� ������ �����ϼ��� : ";
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
	// �÷��̾� ����
	cout << "������ �����մϴ�. ������ �����Ͻðڽ��ϱ�? \n" << endl;
	for (int i = 0; i < monsterList.size(); i++)
	{
		cout << i + 1 << ". ";
		monsterList[i]->ShowSimpleInfo();
	}
	cout << "������ ��� : ";
	cin >> num;
	if (num < 1)
		num = 1;
	else if (num > monsterList.size())
		num = monsterList.size();
	Sleep(attackDelay);
	monsterList[num - 1]->Hit(player->Attack());

	// �÷��̾� ���ݿ� ���� ��� ó��
	for (int i = 0; i < monsterList.size();)
	{
		// ���� ���͸� �����Ѵ�.
		if (monsterList[i]->Die())
			monsterList.erase(monsterList.begin() + i);
		else
			i++;
	}

	// ���� ����, ���� ���� ���Ͱ� ������ ������ ����
	// ������ ������ ������ ���� ���������� �Ѿ��.
	if (!monsterList.empty())
	{
		MonsterAttack(player, monsterList);
	}
	else
	{
		cout << "�������� Ŭ���� !!" << endl;
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
	_CrtDumpMemoryLeaks(); // �޸� �� Ȯ��
}