#pragma region ���, �����, using ����
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

#pragma region ���� ����
enum STAGE {
	Town,
	Field,
};

int attackDelay = 500; // ���� ����
int delayTime = 1000; // ��� ����
bool isEnd = false; // ������ �����ߴ���
STAGE curSpace = Town; // ���� ��ġ
int curStage = 1; // ���� ���� ��������
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

#pragma region ȿ�� �� �ý���
void gotoxy(int x, int y) // ��� Ŀ�� ��ġ ����
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Typing(string str) // Ÿ���� ȿ��
{
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
		Sleep(10);
	}
	cout << "\n\n";
}

void DestroyVector_Monster(vector<Monster*>& v) // ���� �����Ҵ� �޸� ����
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}
void DestroyVector_Item(vector<Item*>& v) // ������ �����Ҵ� �޸� ����
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}
#pragma endregion

#pragma region ĳ���� Ŭ����, �÷��̾�� ������ �θ� Ŭ����
class Character
{
protected:
	string name; // �̸�
	int maxHp; // �ִ� ü��
	int hp; // ü��
	int damage; // ���ݷ�
	int defense; // ����

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
			Typing(this->name + "�� ü���� 0�� �Ǿ� ���������ϴ�.");
		if (value > 0)
			Typing(to_string(value) + "��ŭ�� ü���� ȸ���Ͽ����ϴ�. ���� ü�� : " + to_string(this->hp));
		else
			Typing(to_string(value) + "��ŭ�� ü���� �Ҿ����ϴ�. ���� ü�� : " + to_string(hp));
	}
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
		cout << "\t" << name << " ü��(" + to_string(this->hp) + ") ���ݷ�(" + to_string(this->damage) + ") ����(" + to_string(this->defense) + ")\n\n";
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

#pragma region ������ ���� Ŭ����
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

class Potion : public Item // �÷��̾� ü�� ���� ������
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
		Typing("ü���� " + to_string(value) + " ��ŭ ȸ���մϴ�.");
		player->SetHp(value);
	}
};

class Equip : public Item // ĳ���� ���� ���� ������
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
		Typing(name + "�� �����Ͽ� ������ " + to_string(armor) + " ��ŭ ������ŵ�ϴ�.");
		player->SetDefense(armor);
	}
};
#pragma endregion



#pragma region ���� ���� Ŭ����
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

#pragma region �÷��̾� ���� Ŭ����
class Player : public Character
{
protected:
	int level;
	int maxExp; // �ִ� ����ġ
	int exp; // ���� ����ġ
	int gold; // ���� ���� ���
	

public :
	vector<Item*> inventory;
	
	void AddItem(Item* item) // ������ �߰� �Լ�
	{
		Typing(item->GetName() + " �� ���濡 �߰��Ͽ����ϴ�.");
		inventory.push_back(item);
	}

	int GetExp()
	{
		return exp;
	}
	void SetExp(int value)
	{
		exp += value;
		// �÷��̾� ������ ���
		if (exp >= maxExp)
		{
			exp -= maxExp;
			maxExp *= 1.2;
			level++;
			maxHp += 5;
			hp += 5;
			damage += 5;
			defense += 2;
			Typing("�÷��̾ ������ �߽��ϴ�. ���� ���� : " + to_string(level));
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
			Typing(to_string(value) + "Gold�� �����߽��ϴ�. ���� ������ : " + to_string(gold) + " Gold");
		else
			Typing(to_string(value) + "Gold�� ����߽��ϴ�. ���� ������ : " + to_string(gold) + " Gold");
	}

	void ShowInventory() // ���� �κ��丮 ���¸� �����ش�.
	{
		if (inventory.empty())
		{
			cout << "\t\t���� �������� �����ϴ�." << endl;
			return;
		}
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << "\t" << i + 1 << ". ";
			inventory[i]->ShowItem();
		}
	}

	void UseInventoryItem(int index) // index�� �´� �κ��丮�� �������� ����Ѵ�.
	{
		inventory[index]->Use(this);
		inventory.erase(inventory.begin() + index);
	}

	void ShowInfo() // ĳ���� ���� ���
	{
		cout << "******************** ĳ���� ���� ***********************" << endl;
		cout << "\t ü  �� : " << hp      << "\t\t��  �� : " << level << endl;
		cout << "\t ���ݷ� : " << damage  << "\t\t����ġ : " << exp << "/"<< maxExp << endl;
		cout << "\t ���� : " << defense << "\t\t������ : " << gold <<" Gold" << endl;
		cout << "---------------------- �κ��丮 ------------------------" << endl;
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
	void ShowInfo() // ĳ���� ���� ���
	{
		Player::ShowInfo();
		cout << "---------------------- ������� ------------------------" << endl;
		cout << "\t\t�Ŀ� ������" << endl;
		cout << "********************************************************" << endl;
	}
	void Skill(vector<Monster*>& monsterList)
	{
		int select;
		Typing("\t\t����! �Ŀ� ������!!!");
		ShowMonsters(monsterList);
		cout << "�������� ��ų�� ����Ͻðڽ��ϱ�? :";
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
	void ShowInfo() // ĳ���� ���� ���
	{
		Player::ShowInfo();
		cout << "----------------------- ������� ------------------------" << endl;
		cout << "\t\t��Ƽ ��" << endl;
		cout << "********************************************************" << endl;
	}
	void Skill(vector<Monster*>& monsterList)
	{
		Typing("\t\t�ü�! ��Ƽ ��!!!");
		for (int i = 0; i < monsterList.size(); i++)
		{
			monsterList[i]->Hit(Attack());
			Sleep(attackDelay);
		}
		cout << endl;
	}
};
#pragma endregion



#pragma region �ܺ� �Լ�
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
			Typing(str[i][j]);
		Sleep(500);
	}
}

#pragma region ĳ���� ����
Player* MakePlayer() // ĳ���� ���� �Լ�
{
	string name;
	int selectNum;
	Player* player;
	Typing("�ȳ��ϼ���... ��翩..����� �̸��� �˷��ּ���..");
	cout << "�̸��� �Է��ϼ��� : ";
	cin >> name;
	cout << endl;
	Typing(name + "... ���� �̸��̱���.. �׷� ����� ������ �����ΰ���..?");
	Typing("1. ����\t2. �ü�");
	cout << "���ڸ� �Է����ּ��� : ";
	cin >> selectNum;
	cout << endl;
	switch (selectNum)
	{
	case 1:
		player = new Warrior(name);
		Typing("����� ���籺��! ����� �Ѹ��� ������ �Ϲ� ���ݺ��� 4�� ���� �Ŀ� �����ø� ����� �� �־��.");
		break;
	case 2:
	default:
		player = new Archor(name);
		Typing("����� �ü�����! ��ó�� ���� ���� ��� ���� ������ �� �ִ� ��Ƽ���� ����� �� �־��.");
		break;
	}
	Sleep(500);
	player->ShowInfo();
	cout << endl;
	Typing("����� �ɷ�ġ�� ���� �ٿ� ���� ���� �ʹ� ���ؿ�..");
	Sleep(500);
	Typing("������ �ο�� �����ؼ� ������ �����ּ���..");

	system("pause");
	system("cls");

	return player;
}
#pragma endregion

#pragma region ���� ����
void GoShop(Player* player) // ���� ��ƾ
{
	int select1, select2;
	while (true)
	{
		system("cls");

		Typing("���� ������°� ���� ���̴� �����̴�...");
		Typing("���� ���� : ���� ������ ���̵� �簡���");
		cout << endl;
		Typing("����� ������ �ϰ� ������? ���� ������ : " + to_string(player->GetGold()) + " Gold");
		Typing("1. ���� ���¸� Ȯ���Ѵ�.");
		Typing("2. �������� �����Ѵ�.");
		Typing("3. ������ ���ư���.");
		cout << " ����� ���� : ";
		cin >> select1;
		cout << endl;
		switch (select1)
		{
		case 1: // �÷��̾� ���� Ȯ��
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // ������ ����
			Typing("******************** ������ ��� ***********************");
			Typing("\t\t1. ȸ������ (��) : 15  Gold");
			Typing("\t\t2. ȸ������ (��) : 30  Gold");
			Typing("\t\t3.  ƼŸ�� ����  : 150 Gold");
			cout << "� �������� �����Ͻðڽ��ϱ�? :";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1:
				if (player->GetGold() >= 15)
				{
					Typing("\tȸ������ (��) �� �����Ͽ����ϴ�.");
					player->SetGold(-15);
					player->AddItem(new Potion("ȸ�� ���� (��)", 10));
				}
				else
					Typing("���� ������.");
				break;
			case 2:
				if (player->GetGold() >= 30)
				{
					Typing("\tȸ������ (��) �� �����Ͽ����ϴ�.");
					player->SetGold(-30);
					player->AddItem(new Potion("ȸ�� ���� (��)", 20));
				}
				else
					Typing("���� ������.");
			case 3:
				if (player->GetGold() >= 150)
				{
					Typing("\tƼŸ�� ���� �� �����Ͽ����ϴ�.");
					player->SetGold(-150);
					player->AddItem(new Equip("ƼŸ�� ����", 100));
				}
				else
					Typing("���� ������.");
				break;
			}
			Sleep(delayTime);
			break;

		case 3: // ������ ���ư���.
			Typing("���� ���� : ���迡 �ʿ��Ѱ� �ִٸ� �� �����.");
			Sleep(delayTime);
			return;
			break;
		}
	}
}
void GoRest(Player* player) // �޽�(����) ��ƾ
{
	int select;
	while (true)
	{
		system("cls");

		Typing("�ƴ��� ���̴� �����̴�...");
		Typing("���� ���� : �ǰ��ϸ� ���� ������� ����..");
		cout << endl;
		Typing("����� ������ �ϰ� ������? ���� ������ : " + to_string(player->GetGold()) + " Gold");
		Typing("1. ���� ���¸� Ȯ���Ѵ�.");
		Typing("2. �޽��Ѵ� ( 30 Gold )");
		Typing("3. ������ ������.");
		cout << endl;
		cout << " ����� ���� : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // �÷��̾� ���� Ȯ��
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // �޽�
			if (player->GetGold() < 30)
			{
				Typing("���� ���ڶ󱸸�, ������ �ٽÿ��Գ�.");
			}
			else if (player->GetHp() < player->GetMaxHp())
			{
				Typing("�߰��Գ�!");
				player->SetHp(30);
				player->SetGold(-30);
			}
			else
				Typing("�̹� ü���� �������ֱ��� �޽��� ü���� ���� �� �ϴ°Ŷ��!");
			Sleep(delayTime);
			break;
		case 3: // ������ ���ư���.
			Typing("���� ���� : ������ �� ����ֽð�.");
			Sleep(delayTime);
			return;
			break;
		}
	}
}

void GoTown(Player* player) // ���� ��ƾ
{
	int select;
	while (true)
	{
		system("cls");

		Typing("�����ϰ� ��ȭ�ο� �����̴�...");
		cout << endl;
		Typing("����� ������ �ϰ� ������?");
		Typing("1. ���� ���¸� Ȯ���Ѵ�.");
		Typing("2. �������� �����Ѵ�.");
		Typing("3. �������� �޽��Ѵ�.");
		Typing("4. �ʵ�� ������.");
		cout << endl;
		cout << " ����� ���� : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // �÷��̾� ���� Ȯ��
			player->ShowInfo(); Sleep(delayTime); break;
		case 2: // ������ ����
			GoShop(player); break;
		case 3: // �޽��ϱ�
			GoRest(player); break;
		case 4: // �ʵ�� ������
			curSpace = Field; return; break;
		}
	}

}
#pragma endregion

#pragma region �ʵ� ����
vector<Monster*> GenerateMonsters(int stageNum) // ���� ���� �Լ�
{
	vector<Monster*> monsterList;
	switch (stageNum)
	{
	case 1:
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Monster(i + 1, "������", 10, 5, 5, 5, 10));
		break;
	case 2:
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Monster(i + 1, "����", 20, 15, 15, 7, 20));
		break;
	case 3:
		monsterList.push_back(new Monster("�巡��", 100, 120, 20, 20, 100));
		break;
	}
	return monsterList;
}

void MonsterAttack(Player* player, vector<Monster*>& monsterList) // ���Ͱ� �÷��̾ �����ϴ� �Լ�
{
	// �÷��̾� ���ݿ� ���� ��� ó��
	for (int i = 0; i < monsterList.size();)
	{
		// ���� ���͸� �����ϰ� �ش� ������ ����ġ�� ��常ŭ�� �÷��̾ �߰��Ѵ�.
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
	// ���� �ִ� ���ʹ� �÷��̾�� ������ �����Ѵ�.
	for (int i = 0; i < monsterList.size(); i++)
	{
		Sleep(attackDelay);
		player->Hit(monsterList[i]->Attack());
	}
}

void GoBattle(Player* player) // ���� ��ƾ
{
	vector<Monster*> monsters = GenerateMonsters(curStage);
	int select1;
	int select2;
	int select3;
	while (true)
	{
		system("cls");
		// ������ ���͸� ��� ������ ������ ��ġ�� �ʵ�� ���ư���.
		if (monsters.empty())
		{
			Typing("��� ���͸� ���񷶴�. �ϴ� ���� ������ ���ư���.");
			curStage++;
			if (curStage == 3)
			{
				Typing("���������� ���� �巡���� ������ ������ ������ �ִٰ� �Ѵ�.");
				Typing("�����ϸ� ���� ���ߴ°� ���� �� ����.");
			}
			if(curStage == 4) isEnd = true;
			Sleep(delayTime);
			return;
		}
		Typing("\t\t���� " + to_string(monsters.size()) + "������ ����� �տ� ���ִ�.");
		ShowMonsters(monsters);
		player->ShowInfo();
		cout << endl;
		Typing("����� ������ �ϰ� ������?");
		Typing("1. ���͸� �����Ѵ�.");
		Typing("2. �������� ����Ѵ�.");
		Typing("3. ��������. ( 50% )");
		cout << endl;
		cout << " ����� ���� : ";
		cin >> select1;
		cout << endl;
		switch (select1)
		{
		case 1: // ����
			cout << endl;
			Typing("����� ������ �ϰ� ������?");
			Typing("1. �Ϲݰ���");
			Typing("2. ��ų���");
			Typing("3. ����ȭ��");
			cout << endl;
			cout << " ����� ���� : ";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1: // �Ϲ� ����
				ShowMonsters(monsters);
				cout << "������ �����Ͻðڽ��ϱ�? :";
				cin >> select3;
				cout << endl;
				if (select3 < 1) select3 = 1;
				else if (select3 > monsters.size()) select3 = monsters.size();
				monsters[select3-1]->Hit(player->Attack());
				MonsterAttack(player, monsters);
				Sleep(delayTime);
				break;
			case 2 : // ��ų ���
				player->Skill(monsters);
				MonsterAttack(player, monsters);
				break;
			}
			Sleep(delayTime);
			break;
		case 2: // ������ ���
			Typing(" �÷��̾��� �κ��丮 ");
			player->ShowInventory();
			Typing("����� ������ �ϰ� ������?");
			Typing("1. ������ ���");
			Typing("2. ���� ȭ��");
			cout << endl;
			cout << " ����� ���� : ";
			cin >> select2;
			cout << endl;
			switch (select2)
			{
			case 1: 
				cout << "�� �� ������ �������� ����Ͻðڽ��ϱ�? :";
				cin >> select3;
				cout << endl;
				if (select3 < 1) select3 = 1;
				else if (select3 > monsters.size()) select3 = monsters.size();
				if (select3 <= player->inventory.size())
					player->UseInventoryItem(select3-1);
				else
					Typing("�ش� ��ȣ�� �������� �����ϴ�.");
				Sleep(delayTime);
			}
			break;
		case 3: // ����
			select3 = rand() % 2;
			if (select3 == 0)
			{
				Typing("������ ������ ������ �����ߴ�.");
				MonsterAttack(player, monsters);
				Sleep(delayTime);
			}
			else
			{
				Typing("������ ���� �ձ��� �����ƴ�.");
				Sleep(delayTime);
				return;
			}
			break;
		}
	}
}
void GoField(Player* player) // �ʵ� ��ƾ
{
	int select;
	while (true)
	{
		system("cls");
		if (curStage > 3) return;
		Typing("�̹� �������� : STAGE " + to_string(curStage));
		Typing("���� ���� ���� �� �ұ��� �����⸦ ǳ���...");
		cout << endl;
		Typing("����� ������ �ϰ� ������?");
		Typing("1. ���� ���¸� Ȯ���Ѵ�.");
		Typing("2. ������ �����Ѵ�.");
		Typing("3. ������ ���ư���.");
		cout << endl;
		cout << " ����� ���� : ";
		cin >> select;
		cout << endl;
		switch (select)
		{
		case 1: // ���� Ȯ��
			player->ShowInfo();
			Sleep(delayTime);
			break;
		case 2: // ����
			GoBattle(player);
			break;
		case 3: // ������ ���ư���
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
	_CrtDumpMemoryLeaks(); // �޸� �� Ȯ��
}