#include <iostream>
#include <string>
#include <vector>

using namespace std;


//����� ���� ������Ÿ��

class Student
{

    string name = "���";
    int id;
    int hp = 100;
public:

    //���� private�� ��� ������ ��ȯ��
    string GetName()
    {
        return name;
    }
    //���� private�� ��� ������ ���� ������
    void SetName(string value)
    {
        name = value;
    }

    int GetHp()
    {
        return hp;
    }

    void SetHp(int value)
    {
        hp = value;
        cout << "���� hp : " << hp << endl;
        if (hp <= 0)
            Die();
    }

    void Die()
    {
        cout << name << "�� �����ϴ� ����" << endl;
    }

    void Hit(int value)
    {
        SetHp(GetHp() - value);
    }

    void PoisonEat()
    {
        SetHp(GetHp() - 10);
    }

    void Study()
    {
        cout << name << "�� �����Ѵ�" << endl;
    }
};

void main()
{

    Student studentA;

    cout << studentA.GetName() << endl;
    int input;
    while (true)
    {
        cin >> input;
        studentA.Hit(input);
    }

    studentA.Study();









    int temp;
    cin >> temp;
}