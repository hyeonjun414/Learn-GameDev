#include <iostream>
#include <string>
#include <vector>

using namespace std;


//����� ���� ������Ÿ��

class Person
{
protected:
    string name;
    int id;

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

    void Die()
    {
        cout << name << "�� �׾���" << endl;
    }
    void Eat()
    {
        cout << name << "�� ���� �Ծ���" << endl;
    }

    //���� �Լ�
    virtual void ShowInfo()
    {
        cout << name << endl;
        cout << id << endl;
    }
};
// ��� : �θ�Ŭ������ ��������� ����Լ��� ���� 
//class ��ӹ��� Ŭ���� : public ����� Ŭ����
class Student : public Person
{
private:
    int achievement;
    int grade;
public:

    //������ : �޸𸮿� �Ҵ�� �� ȣ�� ��
    Student()
    {
        cout << "������ ȣ��" << endl;
        name = "";
    }

    //������ �����ε�
    Student(string _name)
    {
        cout << "������ ȣ��" << endl;
        name = _name;
    }


    void Study()
    {
        cout << name << "�� �����Ѵ�" << endl;
    }

    void ShowInfo()
    {
        cout << "-------�л��� ���� ���--------" << endl;
        cout << "�̸� : " << name << endl;
        cout << "�й� : " << id << endl;
        cout << "�г� : " << grade << endl;
        cout << "���� : " << achievement << endl;
        cout << "------------------------------" << endl;
    }
};


class Teacher : public Person
{
private:
    string responsibleSubject;
public:

    void Teach()
    {
        cout << name << "��" << responsibleSubject << "�� ����ģ��" << endl;
    }

    void ShowInfo()
    {
        cout << "-------������ ���� ���--------" << endl;
        cout << "�̸� : " << name << endl;
        cout << "���� : " << id << endl;
        cout << "������ : " << responsibleSubject << endl;
        cout << "------------------------------" << endl;
    }

};

void main()
{

    Teacher teacherA;
    Person* personPtr = &teacherA;

    personPtr->ShowInfo();




    /*
    vector<Person*> people;

    Student studentA;
    studentA.SetName("�Ʊ�");
    studentA.Eat();

    Teacher teacherA;
    teacherA.SetName("���");
    teacherA.Die();

    people.push_back(&studentA);
    people.push_back(&teacherA);

    for (int i = 0; i < people.size(); i++)
    {
       people[i]->ShowInfo();
    }
    */






    int temp;
    cin >> temp;
}