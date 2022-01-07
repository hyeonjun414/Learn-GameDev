#include <iostream>
#include <string>

using namespace std;

//C , C++ 

//����ü�� ����� ����
/*

struct ����ü��
{
   ��� ����...

};

*/

//����� ���� ������Ÿ��
struct Monster
{
    string name;
    int id;

    void Set(string _name, int _id)
    {
        name = _name;
        id = _id;
    }

    void ShowInfo()
    {
        cout << "--------------" << endl;
        cout << "���� �̸� : " << name << endl;
        cout << "���� id : " << id << endl;
        cout << "--------------" << endl << endl;
    }
};

const int MONSTER_COUNT = 5;

#pragma region �ܺ� �Լ�


void SetMonster(Monster* monster, string name, int id)
{
    monster->name = name;
    monster->id = id;
}
void ShowMonsterInfo(Monster monster)
{
    cout << monster.name << "�� id�� " << monster.id << "�Դϴ�" << endl;
}

Monster* FindId(Monster* monsters, int target_id)
{
    for (int i = 0; i < MONSTER_COUNT; i++)
    {
        if (monsters[i].id == target_id)
            return &monsters[i];
    }
}
#pragma endregion




void main()
{
    Monster monsters[MONSTER_COUNT];
    Monster monsterA;
    Monster monsterB;
    Monster monsterC;
    Monster monsterD;
    Monster monsterE;

    monsterA.Set("�巡��", 0);
    monsterB.Set("������", 1);
    monsterC.Set("�ذ�", 2);
    monsterD.Set("�ذ�B", 3);
    monsterE.Set("������B", 4);

    monsters[0] = monsterA;
    monsters[1] = monsterB;
    monsters[2] = monsterC;
    monsters[3] = monsterD;
    monsters[4] = monsterE;


    Monster* findMonster = FindId(monsters, 2);
    findMonster->name += " (ã�Ƴ� ����)";

    for (int i = 0; i < MONSTER_COUNT; i++)
    {
        monsters[i].ShowInfo();
    }


    int temp;
    cin >> temp;

}