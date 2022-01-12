#include <iostream>
#include <string>
#include <vector>

using namespace std;


//사용자 정의 데이터타입

class Student
{

    string name = "용규";
    int id;
    int hp = 100;
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

    int GetHp()
    {
        return hp;
    }

    void SetHp(int value)
    {
        hp = value;
        cout << "남은 hp : " << hp << endl;
        if (hp <= 0)
            Die();
    }

    void Die()
    {
        cout << name << "은 공부하다 죽음" << endl;
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
        cout << name << "은 공부한다" << endl;
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