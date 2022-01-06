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
		cout << "----------------- ���� ���� --------------------" << endl;
		cout << name << "�� ü�� : " << hp << endl;
		cout << name << "�� ���ݷ� : " << att << endl;
		cout << name << "�� ���� : " << def << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	}
};



// ����ü
int main()
{
	// ���� ������Ÿ���� ������ �迭
	// ���� �ٸ� ������Ÿ���� ������ ����ü
	// C ���� ���� : ��� ����, ������ �� �Լ� ��� ���� -> Ŭ������ ū ���� ����
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