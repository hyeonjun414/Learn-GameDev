#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

//��������
struct Player
{
	string name; // �÷��̾� �̸�
	int maxhp; // �ִ� ü��
	int hp; //ü��
	int damage; // ���ݷ�
	int skillDamage; // ��ų ������
	int isCasting; // ��ų ���������� ����
	int curAction; // ���� ���ϰ��ִ� �ൿ

	void init(string _name) // ����ü �ʱ�ȭ �Լ�
	{
		name = _name;
		maxhp = 15;
		hp = 15;
		damage = 1;
		skillDamage = 3;
		isCasting = false;
		curAction = 0;
	}
	int Attack() // ���� �Լ�, ���ݷ��� ��ȯ�Ѵ�.
	{
		cout << name << "�� �����մϴ�. (���� ü�� : " << hp << ")" << endl;
		return damage;
	}
	void Hit(int _damage) // ��Ʈ �Լ�, _damage ��ŭ ���ظ� �Դ´�.
	{
		hp = hp - _damage < 0 ? 0 : hp - _damage;
		cout << name << "�� " << _damage << "�� ���ظ� �Ծ����ϴ�. (���� ü�� : " << hp << ")" << endl;
	}
	void Guard() // ��� �Լ�
	{
		cout << name << "�� �� �����߽��ϴ�. (���� ü�� : " << hp << ")" << endl;
	}
	void Casting() // ��ų ���� �Լ�
	{
		cout << name << "�� �⸦ ������ �ֽ��ϴ�. (���� ü�� : " << hp << ")" << endl;
		isCasting = true;
	}
	int Skill() // ��ų ��� �Լ�
	{
		cout << name << "�� ��ų�� ����մϴ�. (���� ü�� : " << hp << ")" << endl;
		isCasting = false;
		return skillDamage;
	}

	void RandomAction() // �̹� �ൿ�� �����ϴ� �Լ�
	{
		// srand�� �ൿ�� �����Ҷ����� �ٸ� �ൿ�� �ϵ��� �����.
		Sleep(1);
		srand(GetTickCount());
		curAction = rand() % 3;
	}
};

void NoAction(Player* players) // �� �÷��̾ ���� �ƹ� ������ ���������� ���ȴ�.
{
	cout << "�ƹ��ϵ� �������ϴ�. ���� ü�� : " << players[0].name + "(" + to_string(players[0].hp) + ")  "
											  << players[1].name + "(" + to_string(players[1].hp) + ")" << endl;
}

// �� �÷��̾��� �ൿ�� ���� ������ �����Ѵ�.
void Fight(Player *players)
{
	// �ൿ ����
	for (int i = 0; i < 2; i++)
	{
		players[i].RandomAction();
		// �÷��̾��� ���� �ൿ�� ����Ѵ�.
		switch (players[i].curAction)
		{
		case 0: // ����
			cout << "Player " << i + 1 << " : ��     ��\t\t";
			break;
		case 1: // ���
			cout << "Player " << i + 1 << " : ��     ��\t\t";
			break;
		case 2: // ��ų
			if (players[i].isCasting)
				cout << "Player " << i + 1 << " : ��ų ���\t\t";
			else
				cout << "Player " << i + 1 << " : �� ������\t\t";
			break;
		}
		cout << endl;
	}
	cout << endl;

	// ���� �κ�
	if (players[0].curAction == 0) // 1p : ����
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : ����
			// ���� �Ϲ� �������� �Դ´�.
			players[1].Hit(players[0].Attack());
			players[0].Hit(players[1].Attack());
			break;
		case 1: // 2p : ���
			// 2p�� �� �����Ѵ�.
			players[1].Guard();
			break;
		case 2: // 2p : ��ų
			if (players[1].isCasting) // 2p : ��ų ���
			{
				// 1p�� ��ų ������,
				// 2p�� �Ϲ� �������� �Դ´�.
				players[0].Hit(players[1].Skill());
				players[1].Hit(players[0].Attack());
			}
			else // 2p : ��ų ����
			{
				// 2p�� ��ų�� �����ϰ� �Ϲ� �������� �Դ´�.
				players[1].Casting();
				players[1].Hit(players[0].Attack());
			}
		}
	}
	else if (players[0].curAction == 1) // 1p : ���
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : ����
			// 1p�� �� �����Ѵ�.
			players[0].Guard();
			break;
		case 1: // 2p : ���
			// �ƹ��ϵ� �Ͼ�� �ʴ´�.
			NoAction(players);
			break;
		case 2: // 2p : ��ų
			if (players[1].isCasting) // 2p
			{
				// 1p�� ��ų �������� �Դ´�.
				players[0].Hit(players[1].Skill());
			}
			else
			{
				// 2p�� ��ų ������ �Ѵ�.
				players[1].Casting();
			}
		}
	}
	else // 1p : ��ų
	{
		if (players[0].isCasting) // 1p : ��ų ���
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : ����
				// 1p�� �Ϲ� ��������,
				// 2p�� ��ų �������� �Դ´�.
				players[1].Hit(players[0].Skill());
				players[0].Hit(players[1].Attack());
				break;
			case 1: // 2p : ���
				// 2p�� ��ų �������� �Դ´�.
				players[1].Hit(players[0].Skill());
				break;
			case 2: // 2p : ��ų
				if (players[1].isCasting) // 2p
				{
					// ���� ��ų �������� �Դ´�.
					players[0].Hit(players[1].Skill());
					players[1].Hit(players[0].Skill());
				}
				else
				{
					// 2p�� ��ų �������� �԰� ��ų�� �����Ѵ�.
					players[1].Casting();
					players[1].Hit(players[0].Skill());
				}
			}
		}
		else // 1p : ��ų ����
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : ����
				// 1p�� �Ϲ� �������� �԰� ��ų�� �����Ѵ�.
				players[0].Hit(players[1].Attack());
				players[0].Casting();
				break;
			case 1: // 2p : ���
				// 1p�� ��ų�� �����Ѵ�.
				players[0].Casting();
				break;
			case 2: // 2p : ��ų
				if (players[1].isCasting) // 2p
				{
					// 1p�� ��ų �������� �ް� ��ų�� �����Ѵ�.
					players[0].Hit(players[1].Skill());
					players[0].Casting();
				}
				else
				{ // �� �÷��̾�� ��ų�� �����Ѵ�.
					players[0].Casting();
					players[1].Casting();
				}
			}
		}
	}
	cout << endl;
	// �� �÷��̾��� ���� ü�»��¸� ǥ���Ѵ�.
	for (int i = 0; i < 2; i++)
		cout << "Player " + to_string(i+1) + " ü�� ( " + to_string(players[i].hp) + " / " +
														  to_string(players[i].maxhp) + " )\n";


}
// ȭ�� ��� �Լ� ( Call 
void PrintArr(int arr[][40])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				cout << "��";
				break;
			case 1:
				cout << "��";
				break;
			}
		}
		cout << endl;
	}
}
// ȭ���� ü���� �����ϴ� �Լ�
void UpdateHp(int arr[][40], Player *players)
{
	int displayGap = 3;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players[i].maxhp; j++)
		{
			if (j + 1 <= players[i].hp)
				arr[2][j + displayGap] = 1;
			else
				arr[2][j + displayGap] = 0;
		}
		displayGap += 20;
	}
}

// � �÷��̾ �̰���� �Ǵ��ϴ� �Լ�
bool WhoWin(Player player1, Player player2)
{
	if (player1.hp == 0)
	{
		cout << player2.name << "�� �¸��߽��ϴ�." << endl;
		return true;
	}
	else if (player2.hp == 0)
	{
		cout << player1.name << "�� �¸��߽��ϴ�." << endl;
		return true;
	}
	return false;
}
int main()
{
	int arr[20][40] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1},
		{1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1},
		{1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	Player players[2];
	Player player1, player2;
	players[0] = player1;
	players[1] = player2;
	for (int i = 0; i < 2; i++)
	{
		players[i].init("player" + to_string(i+1));
	}

	while (true)
	{
		/*
		1. �÷��̾� ���
		2. ȭ�鿡 ü�� ����
		3. ȭ�� ���
		4. ���� �Ǵ�
		5. ��� ��, ȭ�� �ʱ�ȭ
		6. ���ڰ� ���ö����� �ݺ�
		*/
		Fight(players);
		UpdateHp(arr, players);
		PrintArr(arr);
		if (WhoWin(players[0], players[1])) break;
		Sleep(500);
		system("cls");
	}
}