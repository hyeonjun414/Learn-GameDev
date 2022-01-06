#include <iostream>
#include <string>

using namespace std;

struct Monster
{
	string name;
	int hp;
	float att;
	float def;
	Monster()
	{
		name = "";
		hp = 0;
		att = 0;
		def = 0;
	}

	void MonsterSet(string _name,
		int _hp, float _att, float _def)
	{
		name = _name;
		hp = _hp;
		att = _att;
		def = _def;
	}

	void MonsterShowInfo()
	{
		cout << "----------------- 몬스터 정보 --------------------" << endl;
		cout << name << "의 체력 : " << hp << endl;
		cout << name << "의 공격력 : " << att << endl;
		cout << name << "의 방어력 : " << def << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	}
};



// 구조체
int main()
{
	// 같은 데이터타입의 묶음은 배열
	// 서로 다른 데이터타입의 묶음은 구조체
	// C 와의 차이 : 상속 가능, 생성자 및 함수 사용 가능 -> 클래스와 큰 차이 없음
	Monster monsters[3];
	Monster dragon;
	dragon.MonsterSet("dragon", 100, 10, 10);
	Monster slime;
	slime.MonsterSet("slime", 10, 1, 2);
	Monster skeleton;
	skeleton.MonsterSet("skeleton", 20, 3, 5);
	monsters[0] = dragon;
	monsters[1] = slime;
	monsters[2] = skeleton;

	for (int i = 0; i < 3; i++)
	{
		monsters[i].MonsterShowInfo();
	}
}