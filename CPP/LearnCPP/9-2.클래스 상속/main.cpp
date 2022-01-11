#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
protected:
    string name;
    int id;
    

public :
    Person()
    {
        this->name = "기본이름";
        this->id = 0;
    }
    Person(string name, int id)
    {
        this->name = name;
        this->id = id;
    }
    void Die()
    {
        cout << name << " : 죽음" << endl;
    }
    virtual void Action() {}
    virtual void ShowInfo() 
    {
        cout << name << " " << id << " : " << typeid(this).name() << endl;
    };

};


class Student : public Person
{
    int grades;

public :
    Student(string name, int id, int grades) : Person(name, id)
    {
        this->grades = grades;
    }
    void Action()
    {
        cout << name <<": 학생은 공부를 한다." << endl;
    }
    
    void ShowInfo()
    {
        cout << name << " " << id << " " << grades << " : " << typeid(this).name() << endl;
    }
};
class Teacher : public Person
{
    string responsibleSubject;
    
public :
    Teacher(string name,int id, string subject) : Person(name, id)
    {
        this->responsibleSubject = subject;
    }
    void Action()
    {
        cout << name << ": 선생은 가르친다" << endl;
    }
    void ShowInfo()
    {
        cout << name << " " << id << " " << responsibleSubject << " : " << typeid(this).name() << endl;
    }
};

void main()
{
    vector<Person*> vec;
    for (int i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            vec.push_back(new Student("학생", i, 3));
        }
        else
        {
            vec.push_back(new Teacher("교수", i, to_string(i)));
        }

    }

    for (int i = 0; i < 5; i++)
    {
        vec[i]->Action();
        vec[i]->ShowInfo();
    }
    int temp;
    cin >> temp;

}