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

// ��ü�����̶� : ���α׷��� �ʿ��� �����͸� �߻�ȭ���� ��ü�� �з��Ͽ� ������ ��ü�� �����Ͽ�
//				 ��ü ���� ��ȣ�ۿ��� ���� ���α׷��� ����� ��.
// ��ü���� 3���: ĸ��ȭ, ���, ������
// 1. ĸ��ȭ : ���� ������ ���� Ŭ���� �������� ���� ��ü�� ������ ����� ������.
// 2. ��� : ���뼺�� Ȯ�强�� ���� �Ӽ��� ����� ����ϴ� �θ� Ŭ������
//			 ����� ��ӹ޴� �ڽ� Ŭ������ �����Ѵ�.
// 3. ������ : �ϳ��� ��ü�� ���� ���¸� ���� �� �ִ� ������
//             �θ� Ŭ������ �Լ��� �������Ͽ� �ڽ� Ŭ�������� ����ϴ� �������̵���
//             ���� �Լ��� �Ű������� ���������̳� ������ �ٸ����Ͽ� �ٸ� ����� 
//             �����ϵ��� �ϴ� �����ε��� ���� �������� �����Ѵ�.

#pragma region ���� ����

int stageNum = 1; // �������� ���൵
int attackDelay = 500; // ���� ����
int infoDelay = 1000; // ���� Ȯ�� ����

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

	void ShowInfo() // ĳ���� ���� ���
	{
		cout << "********** " << name << " ***********" << endl;
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

public:
	Player()
	{
		name = "�׳ɿ��";
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

	void Rest(int point) // �޽�, point��ŭ ü��ȸ��
	{
		hp += point;
		cout << "�޽����� �÷��̾��� ü���� " << point << " ��ŭ ȸ���Ǿ����ϴ�." << endl;
	}

	void Reinforce(int stageNum) // ��ȭ, ���������� �ѹ� ����� �Ͽ� ĳ���͸� ��ȭ��Ų��.
	{
		cout << "����Ͽ� �������ϴ�. ��� ��ġ�� �����մϴ�." << endl;
		this->hp += 20 * stageNum;
		this->damage += 10 * stageNum;
		this->defense += 2 * stageNum;
	}
};
#pragma endregion

#pragma region ���� Ŭ����
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

#pragma region �ܺ� �Լ�

// ĳ���� ���� �Լ�
Player* MakeCharacter()
{
	//string name;
	//cout << "�÷��̾��� �̸��� �����ּ��� : ";
	//cin >> name;
	Player* player = new Player("���");
	player->ShowInfo();
	return player;
}
// ���� ���� �Լ�
vector<Monster*> GenerateMonsters(int stageNum)
{
	vector<Monster*> monsterList;
	cout << "\tSTAGE " << stageNum << endl;
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
		case 1: // ����
			AttackRoutine(player, monsterList);
			Sleep(attackDelay);
			break;
		case 2: // ���� Ȯ��
			player->ShowInfo();
			cout << "**********  ����  **********" << endl << endl;
			ShowMonsterInfo(monsterList);
			cout << "******************************" << endl;
			Sleep(infoDelay);
			break;
		case 3: // �ϳѱ�
			MonsterAttack(player, monsterList);
			Sleep(attackDelay);
			break;
		}
		system("cls");
	}
}

// �������� �߰� �޽� �ð�, �÷��̾� ���¿� �޽� ���, ��� ������ �� �ִ� �޴��� �����Ѵ�.
// �޽��� ������������ 1ȸ ����
void RestTime(Player* player)
{
	int restPoint = 1;
	int reinforcePoint = 1;
	int num;
	while (true)
	{
		system("cls");
		cout << " ���� �������� : STAGE " << stageNum + 1 << endl;
		cout << "******************************" << endl;
		cout << " 1. ���� ���� Ȯ�� " << endl;
		cout << " 2. �޽� ( ���� ���� �޽� Ƚ�� : " << restPoint << "ȸ )" << endl;
		cout << " 3. ��� ( ���� ���� ��� Ƚ�� : " << reinforcePoint << "ȸ)" << endl;
		cout << " 4. �޽� ����, ���� ������! " << endl;
		cout << "******************************" << endl;
		cout << "���ϴ� ������ �����ϼ��� : ";
		cin >> num;
		switch (num)
		{
		case 1: // ���� ���� Ȯ��
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
				cout << "�޽� Ƚ���� ���� ����߽��ϴ�." << endl;
			Sleep(infoDelay);
			break;
		case 3: // �� ��
			if (reinforcePoint > 0)
			{
				player->Reinforce(stageNum);
				reinforcePoint--;
			}
			else
				cout << "��� Ƚ���� ���� ����߽��ϴ�." << endl;
			Sleep(infoDelay);
			break;
		case 4: // ���� ����������
			cout << "���� ���������� �̵��մϴ�." << endl;
			stageNum++;
			Sleep(infoDelay);
			return;
			break;
		}
	}
}

void EndGame()
{
	cout << "������ Ŭ���� �߽��ϴ�. �����մϴ�!" << endl;
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
	1. ĳ���� ����
	2. stage1. ���� ���� -> Fight -> �¸� -> ���� ��������
	3. ���� �ð� ( �޽� �� ���(��ȭ) )
	4. stage2. ���� ���� -> Fight -> �¸� -> ���� ��������
	5. ���� �ð� ( �޽� �� ���(��ȭ) )
	6. stage3. ���� ���� -> Fight -> �¸� -> ��
	*/
	Player* player = MakeCharacter(); // ĳ���� ����
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
	_CrtDumpMemoryLeaks(); // �޸� �� Ȯ��
}