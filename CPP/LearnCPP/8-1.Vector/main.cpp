#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MONSTER_COUNT = 5;

#pragma region ���� ����ü
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

#pragma endregion

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

void PrintVec(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}
void PrintVec_Monster(vector<Monster> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].ShowInfo();
    }
}

#pragma endregion

void main()
{
    #pragma region �����迭
    /*
     vector<int> intVec;

    //push_back�� �����迭 �� �ڿ� �����͸� ����
    intVec.push_back(5);
    intVec.push_back(4);
    intVec.push_back(10);
    intVec.push_back(40);
    PrintVec(intVec);

    // ����� ���� ������ Ÿ�Ե� ��밡��
    vector<Monster> monsters;
    Monster monsterA;
    Monster monsterB;
    Monster monsterC;

    monsterA.Set("�巡��", 0);
    monsterB.Set("������", 1);
    monsterC.Set("�ذ�", 2);

    monsters.push_back(monsterA);
    monsters.push_back(monsterB);
    monsters.push_back(monsterC);

    PrintVec_Monster(monsters);
    */
    #pragma endregion

    #pragma region �����Ҵ�
    
    // ���� �Ҵ�
    // new Ű����� �����Ҵ��� �ϱ� ����


    Monster* monsterD = new Monster();
    monsterD->Set("�׽�Ʈ", 10);
    monsterD->ShowInfo();
    
    vector<Monster*> monsters2;
    for (int i = 0; i < 3; i++)
    {
        monsters2.push_back(new Monster());
    }
    monsters2[0]->Set("�巡��", 0);
    monsters2[1]->Set("������", 1);
    monsters2[2]->Set("�ذ�", 2);

    for (int i = 0; i < monsters2.size(); i++)
    {
        monsters2[i]->ShowInfo();
    }

    for (int i = 0; i < monsters2.size(); i++)
    {
        delete monsters2[i];
    }
    
    #pragma endregion
    
    #pragma region Vector Ȱ��
    /*
    // ������ ����
    // vector<������Ÿ��> ������;
    vector<int> numbers;
    for (int i = 0; i < 10; i++)
    {
        // push_back(value) : �� �ڿ� value�� ����.
        numbers.push_back(i);
    }
    // ���� ������ ����
    PrintVec(numbers);
    numbers.erase(numbers.begin()+1, numbers.begin()+5);
    PrintVec(numbers);
    numbers.erase(numbers.begin());
    PrintVec(numbers);

    cout << numbers.at(4) << endl;
    */
    #pragma endregion

    
    
    int temp;
    cin >> temp;

}