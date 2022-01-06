#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

//대전게임
struct Player
{
	string name; // 플레이어 이름
	int maxhp; // 최대 체력
	int hp; //체력
	int damage; // 공격력
	int isCasting;
	int curAction; // 현재 취하고있는 액션

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
		cout << name << "은 " << damage << "의 피해를 입었습니다. (현재 체력 : " << hp << ")" << endl;
		// 기모으는중 맞았다면 초기화
		if (isCasting = true)
		{
			isCasting = false;
			cout << name << "의 스킬 시전이 중단되었습니다." << endl;
		}
	}
	void Guard()
	{
		cout << name << "은 방어에 성공했습니다. (현재 체력 : " << hp << ")" << endl;
	}

	void RandomAction()
	{
		if (isCasting == 0)
		{
			switch (curAction = rand() % 3)
			{
			case 0: // 공격
				damage = 1;
				
				break;
			case 1: // 방어
				damage = 0;
				break;
			case 2: // 스킬
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
				cout << "□";
				break;
			case 1 :
				cout << "■";
				break;
			}
		}
		cout << endl;
	}
}

void Fight(Player *players)
{
	// 행동 선택
	for (int i = 0; i < 2; i++)
	{
		players[i].RandomAction();
		switch (players[i].curAction)
		{
		case 0: // 공격
			cout << "Player " << i << " : 공격   ";
			break;
		case 1: // 방어
			cout << "Player " << i << " : 방어   ";
			break;
		case 2: // 스킬
			string str = players[i].isCasting ? "시전중" : "사용";
			cout << "Player " << i << " : 스킬 (스킬 카운트 : " << str << ")   ";
			break;
		}
	}
	cout << endl;

	if (players[0].curAction == 0) // 1p가 공격일때
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : 공격
			players[0].Hit(players[1].damage);
			players[1].Hit(players[0].damage);
			break;
		case 1: // 2p : 방어
			players[1].Guard();
			break;
		case 2: // 2p : 스킬
			if (players[1].isCasting) // 2p
			{
				players[0].Hit(players[1].damage);
			}
			else
				players[1].Hit(players[0].damage);
		}
	}
	else if (players[0].curAction == 1) // 1p가 방어일때
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : 공격
			players[0].Guard();
			break;
		case 1: // 2p : 방어
			break;
		case 2: // 2p : 스킬
			if (players[1].isCasting) // 2p
			{
				players[0].Guard();
			}
		}
	}
	else // 1p가 스킬일때
	{
		if (players[0].isCasting) // 1p
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : 공격
				players[1].Hit(players[0].damage);
				break;
			case 1: // 2p : 방어
				players[1].Guard();
				break;
			case 2: // 2p : 스킬
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
			case 0: // 2p : 공격
				players[0].Hit(players[1].damage);
				break;
			case 1: // 2p : 방어
				break;
			case 2: // 2p : 스킬
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