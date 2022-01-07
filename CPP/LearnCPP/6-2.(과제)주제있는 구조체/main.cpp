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
	int skillDamage; // 스킬 데미지
	int isCasting; // 스킬 시전중인지 여부
	int curAction; // 현재 취하고있는 행동

	void init(string _name) // 구조체 초기화 함수
	{
		name = _name;
		maxhp = 15;
		hp = 15;
		damage = 1;
		skillDamage = 3;
		isCasting = false;
		curAction = 0;
	}
	int Attack() // 공격 함수, 공격력을 반환한다.
	{
		cout << name << "은 공격합니다. (현재 체력 : " << hp << ")" << endl;
		return damage;
	}
	void Hit(int _damage) // 히트 함수, _damage 만큼 피해를 입는다.
	{
		hp = hp - _damage < 0 ? 0 : hp - _damage;
		cout << name << "은 " << _damage << "의 피해를 입었습니다. (현재 체력 : " << hp << ")" << endl;
	}
	void Guard() // 방어 함수
	{
		cout << name << "은 방어에 성공했습니다. (현재 체력 : " << hp << ")" << endl;
	}
	void Casting() // 스킬 시전 함수
	{
		cout << name << "은 기를 모으고 있습니다. (현재 체력 : " << hp << ")" << endl;
		isCasting = true;
	}
	int Skill() // 스킬 사용 함수
	{
		cout << name << "은 스킬을 사용합니다. (현재 체력 : " << hp << ")" << endl;
		isCasting = false;
		return skillDamage;
	}

	void RandomAction() // 이번 행동을 선택하는 함수
	{
		// srand로 행동을 선택할때마다 다른 행동을 하도록 만든다.
		Sleep(1);
		srand(GetTickCount());
		curAction = rand() % 3;
	}
};

void NoAction(Player* players) // 두 플레이어가 서로 아무 영향을 주지않을때 사용된다.
{
	cout << "아무일도 없었습니다. 현재 체력 : " << players[0].name + "(" + to_string(players[0].hp) + ")  "
											  << players[1].name + "(" + to_string(players[1].hp) + ")" << endl;
}

// 두 플레이어의 행동에 따라 로직을 실행한다.
void Fight(Player *players)
{
	// 행동 선택
	for (int i = 0; i < 2; i++)
	{
		players[i].RandomAction();
		// 플레이어의 현재 행동을 출력한다.
		switch (players[i].curAction)
		{
		case 0: // 공격
			cout << "Player " << i + 1 << " : 공     격\t\t";
			break;
		case 1: // 방어
			cout << "Player " << i + 1 << " : 방     어\t\t";
			break;
		case 2: // 스킬
			if (players[i].isCasting)
				cout << "Player " << i + 1 << " : 스킬 사용\t\t";
			else
				cout << "Player " << i + 1 << " : 기 모으기\t\t";
			break;
		}
		cout << endl;
	}
	cout << endl;

	// 로직 부분
	if (players[0].curAction == 0) // 1p : 공격
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : 공격
			// 서로 일반 데미지를 입는다.
			players[1].Hit(players[0].Attack());
			players[0].Hit(players[1].Attack());
			break;
		case 1: // 2p : 방어
			// 2p가 방어에 성공한다.
			players[1].Guard();
			break;
		case 2: // 2p : 스킬
			if (players[1].isCasting) // 2p : 스킬 사용
			{
				// 1p는 스킬 데미지,
				// 2p는 일반 데미지를 입는다.
				players[0].Hit(players[1].Skill());
				players[1].Hit(players[0].Attack());
			}
			else // 2p : 스킬 시전
			{
				// 2p가 스킬을 시전하고 일반 데미지를 입는다.
				players[1].Casting();
				players[1].Hit(players[0].Attack());
			}
		}
	}
	else if (players[0].curAction == 1) // 1p : 방어
	{
		switch (players[1].curAction)
		{
		case 0: // 2p : 공격
			// 1p는 방어에 성공한다.
			players[0].Guard();
			break;
		case 1: // 2p : 방어
			// 아무일도 일어나지 않는다.
			NoAction(players);
			break;
		case 2: // 2p : 스킬
			if (players[1].isCasting) // 2p
			{
				// 1p는 스킬 데미지를 입는다.
				players[0].Hit(players[1].Skill());
			}
			else
			{
				// 2p는 스킬 시전을 한다.
				players[1].Casting();
			}
		}
	}
	else // 1p : 스킬
	{
		if (players[0].isCasting) // 1p : 스킬 사용
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : 공격
				// 1p는 일반 데미지를,
				// 2p는 스킬 데미지를 입는다.
				players[1].Hit(players[0].Skill());
				players[0].Hit(players[1].Attack());
				break;
			case 1: // 2p : 방어
				// 2p는 스킬 데미지를 입는다.
				players[1].Hit(players[0].Skill());
				break;
			case 2: // 2p : 스킬
				if (players[1].isCasting) // 2p
				{
					// 서로 스킬 데미지를 입는다.
					players[0].Hit(players[1].Skill());
					players[1].Hit(players[0].Skill());
				}
				else
				{
					// 2p는 스킬 데미지를 입고 스킬을 시전한다.
					players[1].Casting();
					players[1].Hit(players[0].Skill());
				}
			}
		}
		else // 1p : 스킬 시전
		{
			switch (players[1].curAction)
			{
			case 0: // 2p : 공격
				// 1p는 일반 데미지를 입고 스킬을 시전한다.
				players[0].Hit(players[1].Attack());
				players[0].Casting();
				break;
			case 1: // 2p : 방어
				// 1p는 스킬을 시전한다.
				players[0].Casting();
				break;
			case 2: // 2p : 스킬
				if (players[1].isCasting) // 2p
				{
					// 1p는 스킬 데미지를 받고 스킬을 시전한다.
					players[0].Hit(players[1].Skill());
					players[0].Casting();
				}
				else
				{ // 두 플레이어는 스킬을 시전한다.
					players[0].Casting();
					players[1].Casting();
				}
			}
		}
	}
	cout << endl;
	// 두 플레이어의 현재 체력상태를 표기한다.
	for (int i = 0; i < 2; i++)
		cout << "Player " + to_string(i+1) + " 체력 ( " + to_string(players[i].hp) + " / " +
														  to_string(players[i].maxhp) + " )\n";


}
// 화면 출력 함수 ( Call 
void PrintArr(int arr[][40])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				cout << "□";
				break;
			case 1:
				cout << "■";
				break;
			}
		}
		cout << endl;
	}
}
// 화면의 체력을 갱신하는 함수
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

// 어떤 플레이어가 이겼는지 판단하는 함수
bool WhoWin(Player player1, Player player2)
{
	if (player1.hp == 0)
	{
		cout << player2.name << "이 승리했습니다." << endl;
		return true;
	}
	else if (player2.hp == 0)
	{
		cout << player1.name << "이 승리했습니다." << endl;
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
		1. 플레이어 대결
		2. 화면에 체력 갱신
		3. 화면 출력
		4. 승자 판단
		5. 대기 후, 화면 초기화
		6. 승자가 나올때까지 반복
		*/
		Fight(players);
		UpdateHp(arr, players);
		PrintArr(arr);
		if (WhoWin(players[0], players[1])) break;
		Sleep(500);
		system("cls");
	}
}