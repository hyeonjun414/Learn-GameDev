#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma region 몬스터 클래스
class Monster
{
private:
    string name;
    int id;
    int hideValue;

public:
    Monster()
    {
        cout << "생성자 호출" << endl;
        name = "기본이름";
        id = 0;
        hideValue = 30;
    }
    // 생성자의 오버로딩
    // this.는 현재 객체의 주소를 가리킨다. 그래서 ->로 접근하게 된다.
    Monster(string name, int id)
    {
        cout << "생성자 호출" << endl;
        this->name = name;
        this->id = id;
    }
    ~Monster()
    {
        cout << "소멸자 호출" << endl;
    }

    void Set(string _name, int _id)
    {
        name = _name;
        id = _id;
    }

    void ShowInfo()
    {
        cout << "--------------" << endl;
        cout << "몬스터 이름 : " << name << endl;
        cout << "몬스터 id : " << id << endl;
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
    // 클래스는 객체를 찍어 내기 위한 틀
    //Monster monsterA;

    vector<Monster*> monsterVec;
    for (int i = 0; i < 5; i++)
        monsterVec.push_back(new Monster("슬라임", i));
    for (int i = 0; i < 5; i++)
        monsterVec[i]->ShowInfo();

    int temp;
    cin >> temp;

}