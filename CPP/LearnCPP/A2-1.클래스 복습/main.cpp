#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Ŭ���� ���+
//��ĳ���� �ٿ�ĳ����
//�������̵�
//�����Լ�

class Charactor
{
public:
    string name;
    int hp;
    int att;

    void Hit(int damage)
    {
        cout << name << "��" << damage << "��ŭ �������� �޾Ҵ�" << endl;
        hp -= damage;
        if (hp <= 0)
            Die();
    }
    void Attack(Charactor* target)
    {
        cout << "ĳ���� ����" << endl;
    }
    virtual void Die()
    {
        cout << "ĳ���� ����" << endl;
    }
};

class Monster : public Charactor
{
public:
    string dropItem;

    Monster()
    {
        name = "����";
        hp = 100;
        att = 10;
        dropItem = "��Ӿ�����";
    }

    void Drop()
    {
        cout << dropItem << "�� ��������" << endl;
    }

    void Attack(Charactor* player)
    {
        cout << name << "�� �÷��̾� " << player->name << "�� ����" << endl;
        player->Hit(att);
    }
    void Die()
    {
        //������ ������(::)�� ����ϸ� �θ�Ŭ������ �Լ����� ���� �� �� ����.
        Charactor::Die();
        cout << "���� ����" << endl;
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
        name = "�÷��̾�";
        hp = 100;
        att = 20;
    }

    void Attack(Charactor* monster)
    {
        cout << name << "�� ���� " << monster->name << "�� ����" << endl;
        monster->Hit(att);
    }
    void Die()
    {
        cout << "�÷��̾� ����" << endl;
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