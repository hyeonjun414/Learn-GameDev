#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma region ���� Ŭ����
class Monster
{
private:
    string name;
    int id;
    int hideValue;

public:
    Monster()
    {
        cout << "������ ȣ��" << endl;
        name = "�⺻�̸�";
        id = 0;
        hideValue = 30;
    }
    // �������� �����ε�
    // this.�� ���� ��ü�� �ּҸ� ����Ų��. �׷��� ->�� �����ϰ� �ȴ�.
    Monster(string name, int id)
    {
        cout << "������ ȣ��" << endl;
        this->name = name;
        this->id = id;
    }
    ~Monster()
    {
        cout << "�Ҹ��� ȣ��" << endl;
    }

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
    int GetHideValue()
    {
        return hideValue;
    }
};

#pragma endregion


void main()
{
    // Ŭ������ ��ü�� ��� ���� ���� Ʋ
    //Monster monsterA;

    vector<Monster*> monsterVec;
    for (int i = 0; i < 5; i++)
        monsterVec.push_back(new Monster("������", i));
    for (int i = 0; i < 5; i++)
        monsterVec[i]->ShowInfo();

    int temp;
    cin >> temp;

}