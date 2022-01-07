#include <iostream>
#include <string>

using namespace std;

//C , C++ 

//구조체의 선언과 정의
/*

struct 구조체명
{
   멤버 변수...

};

*/

//사용자 정의 데이터타입
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
        cout << "몬스터 이름 : " << name << endl;
        cout << "몬스터 id : " << id << endl;
        cout << "--------------" << endl << endl;
    }
};

const int MONSTER_COUNT = 5;

#pragma region 외부 함수


void SetMonster(Monster* monster, string name, int id)
{
    monster->name = name;
    monster->id = id;
}
void ShowMonsterInfo(Monster monster)
{
    cout << monster.name << "의 id는 " << monster.id << "입니다" << endl;
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

    monsterA.Set("드래곤", 0);
    monsterB.Set("슬라임", 1);
    monsterC.Set("해골", 2);
    monsterD.Set("해골B", 3);
    monsterE.Set("슬라임B", 4);

    monsters[0] = monsterA;
    monsters[1] = monsterB;
    monsters[2] = monsterC;
    monsters[3] = monsterD;
    monsters[4] = monsterE;


    Monster* findMonster = FindId(monsters, 2);
    findMonster->name += " (찾아낸 몬스터)";

    for (int i = 0; i < MONSTER_COUNT; i++)
    {
        monsters[i].ShowInfo();
    }


    int temp;
    cin >> temp;

}