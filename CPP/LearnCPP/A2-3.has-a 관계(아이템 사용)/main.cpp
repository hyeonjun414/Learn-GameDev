#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Equip;
class Item;

class Charactor
{
public:
    int hp = 100;
    int maxHp = 100;
    Equip* equip;
    vector<Item*> inventory;
};

class Item
{
public:
    string name;
    virtual void Use(Charactor* target, int index)
    {

    }
};

class Equip : public Item
{
public:
    Equip()
    {

    }
    Equip(string _name)
    {
        name = _name;
    }
    void Use(Charactor* target, int index)
    {
        cout << name << "��� ������" << endl;
        target->equip = this;
    }
};

class Potion : public Item
{
public:
    Potion()
    {

    }

    Potion(string _name)
    {
        name = _name;
    }
    void Use(Charactor* target, int index)
    {
        cout << name << "�� �����" << endl;
        target->hp += 10;
        target->inventory.erase(target->inventory.begin() + index);
    }
};

class Player : public Charactor
{
public:


    void UseInventory(int index)
    {
        inventory[index]->Use(this, index);
    }

    void ShowInventory()
    {

        cout << "--------�κ��丮--------" << endl;
        if (equip != NULL)
            cout << "���� ��� ������ : " << equip->name << endl;
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << i << "��° ������ : " << inventory[i]->name << endl;
        }
        cout << "-----------------------" << endl;

    }
};


class Monster
{
private:
    string name = "TEST";
    int hp = 100;
    int maxHp = 100;

public:

    int GetHp()
    {
        return hp;
    }
    void SetHp(int value)
    {
        hp = value;

        if (hp <= 0)
        {
            Die();
            cout << "�߰� �� �� ó��" << endl;
        }
        else if (hp <= (maxHp / 2))
        {
            cout << "���� ������" << endl;
        }


    }


    void Hit(int damage)
    {
        cout << "�¾��� �� ó��" << endl;
        SetHp(hp - damage);
    }

    void PoisonEat(int value)
    {
        cout << "���� �� ������ �Ծ��� �� ó��" << endl;
        SetHp(hp - value);
    }

    void Die()
    {
        cout << "����" << endl;
    }

};

void main()
{
    setlocale(LC_ALL, "");
    Player player;


    player.inventory.push_back(new Equip("����"));
    player.inventory.push_back(new Potion("��������"));
    player.inventory.push_back(new Potion("��������"));
    player.inventory.push_back(new Potion("��������"));
    player.inventory.push_back(new Potion("��������"));

    player.ShowInventory();

    player.UseInventory(0);
    player.UseInventory(3);

    player.ShowInventory();



    int temp;

    cin >> temp;

}