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
	int isCasting;
	int curAction; // ���� ���ϰ��ִ� �׼�

	void init(string _name)
	{
		name = _name;
		maxhp = 15;
		hp = 15;
		damage = 1;
		isCasting = false;
		curAction = 0;
	}
	void Hit(int damage)
	{
		hp -= damage;
		cout << name << "�� " << damage << "�� ���ظ� �Ծ����ϴ�. (���� ü�� : " << hp << ")" << endl;
		// ��������� �¾Ҵٸ� �ʱ�ȭ
		if (isCasting = true)
		{
			isCasting = false;
			cout << name << "�� ��ų ������ �ߴܵǾ����ϴ�." << endl;
		}
	}
	void Guard()
	{
		cout << name << "�� �� �����߽��ϴ�. (���� ü�� : " << hp << ")" << endl;
	}

	void RandomAction()
	{
		if (isCasting == 0)
		{
			switch (curAction = rand() % 3)
			{
			case 0: // ����
				damage = 1;
				
				break;
			case 1: // ���
				damage = 0;
				break;
			case 2: // ��ų
				if (isCasting = false)
				{
					isCasting = true;
				}
				else
				{
					damage = 3;
					isCasting = false;
				}
				break;
			}
		}
	}
};
void PrintArr(int arr[][40])
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			switch (arr[i][j])
			{
			case 0 :
				cout << "��";
				break;
			case 1 :
				cout << "��";
				break;
			}
		}
		cout << endl;
	}
}

void Fight(Player *players)
{
	// �ൿ ����
	for (int i = 0; i < 2; i++)
	{
		players[i].RandomAction();
		switch (players[i].curAction)
		{
		case 0: // ����
			cout << "Player " << i << " : ����   ";
			break;
		case 1: // ���
			cout << "Player " << i << " : ���   ";
			break;
		case 2: // ��ų
			string str = players[i].isCasting ? "������" : "���";
			cout << "Player " << i << " : ��ų (��ų ī��Ʈ : " << str << ")   ";
			break;
		}
	}
	cout << endl;

	if (players[0].curAction == 0) // 1p�� �����϶�
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : ����
			players[0].Hit(players[1].damage);
			players[1].Hit(players[0].damage);
			break;
		case 1: // 2p : ���
			players[1].Guard();
			break;
		case 2: // 2p : ��ų
			if (players[1].isCasting) // 2p
			{
				players[0].Hit(players[1].damage);
			}
			else
				players[1].Hit(players[0].damage);
		}
	}
	else if (players[0].curAction == 1) // 1p�� ����϶�
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : ����
			players[0].Guard();
			break;
		case 1: // 2p : ���
			break;
		case 2: // 2p : ��ų
			if (players[1].isCasting) // 2p
			{
				players[0].Guard();
			}
		}
	}
	else // 1p�� ��ų�϶�
	{
		if (players[0].isCasting) // 1p
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : ����
				players[1].Hit(players[0].damage);
				break;
			case 1: // 2p : ���
				players[1].Guard();
				break;
			case 2: // 2p : ��ų
				if (players[1].isCasting) // 2p
				{
				}
				else
					players[1].Hit(players[0].damage);

			}
		}
		else
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : ����
				players[0].Hit(players[1].damage);
				break;
			case 1: // 2p : ���
				break;
			case 2: // 2p : ��ų
				if (players[1].isCasting) // 2p
				{
					players[0].Hit(players[1].damage);

				}
			}
		}
	}
}

void UpdateHp(int (*arr)[40], Player *players)
{
	int displayGap = 3;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players[i].maxhp; j++)
		{
			if (j + 1 < players[i].hp)
			{
				arr[2][j + displayGap] = 1;
				arr[3][j + displayGap] = 1;
			}
			else
			{
				arr[2][j + displayGap] = 0;
				arr[3][j + displayGap] = 0;
			}
		}
		displayGap += 20;
	}
}
int main()
{
	int arr[22][40] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
		players[i].init("player" + to_string(1));
	}

	while (true)
	{
		Fight(players);
		UpdateHp(arr, players);
	//	PrintArr(arr);
		Sleep(3000);
		system("cls");
	}
}