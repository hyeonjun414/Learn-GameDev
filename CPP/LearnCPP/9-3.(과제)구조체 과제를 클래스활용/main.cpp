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
		name = "�׳ɿ��";
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
		cout << "******************** �÷��̾� ���� *******************" << endl;
		cout << "��  �� : " << name << endl;
		cout << "ü  �� : " << hp << " / " << maxHp << endl;
		cout << "���ݷ� : " << damage << endl;
		cout << "���� : " << defense << endl;
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
		cout << this->name << "��(��) " << this->damage << "�� ���ظ� �Ծ����ϴ�." << endl;
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
		name = "������" + to_string(number);;
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
		name = "����" + to_string(number);
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
		name = "�巡��";
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

#pragma region �ܺ� �Լ�

Player* MakeCharacter()
{
	string name;
	cout << "�÷��̾��� �̸��� �����ּ��� : ";
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
		cout << "������ 3������ �����Ǿ����ϴ�." << endl;
		for (int i = 0; i < 3; i++)
			monsterList.push_back(new Slime(i));
		break;
	case 2:
		cout << "���� 2������ �����Ǿ����ϴ�." << endl;
		for (int i = 0; i < 2; i++)
			monsterList.push_back(new Zombie(i));
		break;
	case 3:
		cout << "�巡���� ����Ͽ����ϴ�." << endl;
		monsterList.push_back(new Dragon());
		break;
	}
	return monsterList;

}
int SelectAction()
{
	int num;
	cout << "*****************************" << endl;
	cout << "���ϴ� ������ �����ϼ��� : " << endl;
	cout << "1. �� �� " << endl;
	cout << "2. �� ų " << endl;
	cout << "3. �� �� " << endl;
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
	1. ĳ���� ����
	2. stage1. ���� ���� -> Fight -> ����ǰ ȹ��(���� �ϳ��� Ȯ������ ����)
	3. ���� �ð� ( ���� ���� )
	4. stage2. ���� ���� -> Fight -> ����ǰ ȹ��(�� �ϳ��� Ȯ������ ����)
	5. ���� �ð� ( �� ���� )
	6. stage3. ���� ���� -> Fight -> �¸� -> ��
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