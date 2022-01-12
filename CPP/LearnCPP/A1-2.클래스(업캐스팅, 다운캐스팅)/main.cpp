#include <iostream>
#include <string>
#include <vector>

using namespace std;


//사용자 정의 데이터타입

class Person
{
protected:
    string name;
    int id;

public:

    //게터 private의 멤버 변수를 반환함
    string GetName()
    {
        return name;
    }
    //세터 private의 멤버 변수에 값을 세팅함
    void SetName(string value)
    {
        name = value;
    }

    void Die()
    {
        cout << name << "은 죽었다" << endl;
    }
    void Eat()
    {
        cout << name << "은 밥을 먹었다" << endl;
    }

    //가상 함수
    virtual void ShowInfo()
    {
        cout << name << endl;
        cout << id << endl;
    }
};
// 상속 : 부모클래스의 멤버변수와 멤버함수를 가짐 
//class 상속받을 클래스 : public 상속할 클래스
class Student : public Person
{
private:
    int achievement;
    int grade;
public:

    //생성자 : 메모리에 할당될 때 호출 됨
    Student()
    {
        cout << "생성자 호출" << endl;
        name = "";
    }

    //생성자 오버로딩
    Student(string _name)
    {
        cout << "생성자 호출" << endl;
        name = _name;
    }


    void Study()
    {
        cout << name << "은 공부한다" << endl;
    }

    void ShowInfo()
    {
        cout << "-------학생의 정보 출력--------" << endl;
        cout << "이름 : " << name << endl;
        cout << "학번 : " << id << endl;
        cout << "학년 : " << grade << endl;
        cout << "성적 : " << achievement << endl;
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
        cout << name << "은" << responsibleSubject << "를 가르친다" << endl;
    }

    void ShowInfo()
    {
        cout << "-------선생의 정보 출력--------" << endl;
        cout << "이름 : " << name << endl;
        cout << "교번 : " << id << endl;
        cout << "담당과목 : " << responsibleSubject << endl;
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
    studentA.SetName("훈교");
    studentA.Eat();

    Teacher teacherA;
    teacherA.SetName("용규");
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