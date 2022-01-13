#include <iostream>
#include <string>
#include <vector>

using namespace std;

//클래스 상속+
//업캐스팅 다운캐스팅
//오버라이딩
//가상함수

class Charactor
{
public:
    string name;
    int hp;
    int att;

    void Hit(int damage)
    {
        cout << name << "은" << damage << "만큼 데미지를 받았다" << endl;
        hp -= damage;
        if (hp <= 0)
            Die();
    }
    void Attack(Charactor* target)
    {
        cout << "캐릭터 때림" << endl;
    }
    virtual void Die()
    {
        cout << "캐릭터 죽음" << endl;
    }
};

class Monster : public Charactor
{
public:
    string dropItem;

    Monster()
    {
        name = "몬스터";
        hp = 100;
        att = 10;
        dropItem = "드롭아이템";
    }

    void Drop()
    {
        cout << dropItem << "을 떨구었다" << endl;
    }

    void Attack(Charactor* player)
    {
        cout << name << "은 플레이어 " << player->name << "을 공격" << endl;
        player->Hit(att);
    }
    void Die()
    {
        //스코프 연산자(::)를 사용하면 부모클래스의 함수에도 접근 할 수 있음.
        Charactor::Die();
        cout << "몬스터 죽음" << endl;
        Drop();
    }
};

class Player : public Charactor
{
public:
    int level;
    int exp;

    Player()
    {
        name = "플레이어";
        hp = 100;
        att = 20;
    }

    void Attack(Charactor* monster)
    {
        cout << name << "은 몬스터 " << monster->name << "을 공격" << endl;
        monster->Hit(att);
    }
    void Die()
    {
        cout << "플레이어 죽음" << endl;
    }
    void GetthingExp(int value)
    {
        exp += value;
    }
};

void main()
{


    Monster* monsterA = new Monster();
    Player* playerA = new Player();

    int input;
    while (true)
    {
        cin >> input;
        playerA->Attack(monsterA);
        monsterA->Attack(playerA);
    }







    int temp;

    cin >> temp;

}