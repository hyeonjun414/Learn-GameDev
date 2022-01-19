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
        cout << name << "장비를 장착함" << endl;
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
        cout << name << "를 사용함" << endl;
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

        cout << "--------인벤토리--------" << endl;
        if (equip != NULL)
            cout << "현재 장비 아이템 : " << equip->name << endl;
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << i << "번째 아이템 : " << inventory[i]->name << endl;
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
            cout << "추가 된 후 처리" << endl;
        }
        else if (hp <= (maxHp / 2))
        {
            cout << "으악 아프다" << endl;
        }


    }


    void Hit(int damage)
    {
        cout << "맞았을 때 처리" << endl;
        SetHp(hp - damage);
    }

    void PoisonEat(int value)
    {
        cout << "독이 든 음식을 먹었을 때 처리" << endl;
        SetHp(hp - value);
    }

    void Die()
    {
        cout << "죽음" << endl;
    }

};

void main()
{
    setlocale(LC_ALL, "");
    Player player;


    player.inventory.push_back(new Equip("반지"));
    player.inventory.push_back(new Potion("힐링포션"));
    player.inventory.push_back(new Potion("힐링포션"));
    player.inventory.push_back(new Potion("힐링포션"));
    player.inventory.push_back(new Potion("힐링포션"));

    player.ShowInventory();

    player.UseInventory(0);
    player.UseInventory(3);

    player.ShowInventory();



    int temp;

    cin >> temp;

}