#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MONSTER_COUNT = 5;

#pragma region 몬스터 구조체
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
        cout << "몬스터 이름 : " << name << endl;
        cout << "몬스터 id : " << id << endl;
        cout << "--------------" << endl << endl;
    }
};

#pragma endregion

#pragma region 외부 함수


void SetMonster(Monster* monster, string name, int id)
{
    monster->name = name;
    monster->id = id;
}
void ShowMonsterInfo(Monster monster)
{
    cout << monster.name << "의 id는 " << monster.id << "입니다" << endl;
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
    #pragma region 가변배열
    /*
     vector<int> intVec;

    //push_back은 가변배열 맨 뒤에 데이터를 삽입
    intVec.push_back(5);
    intVec.push_back(4);
    intVec.push_back(10);
    intVec.push_back(40);
    PrintVec(intVec);

    // 사용자 정의 데이터 타입도 사용가능
    vector<Monster> monsters;
    Monster monsterA;
    Monster monsterB;
    Monster monsterC;

    monsterA.Set("드래곤", 0);
    monsterB.Set("슬라임", 1);
    monsterC.Set("해골", 2);

    monsters.push_back(monsterA);
    monsters.push_back(monsterB);
    monsters.push_back(monsterC);

    PrintVec_Monster(monsters);
    */
    #pragma endregion

    #pragma region 동적할당
    
    // 동적 할당
    // new 키워드는 동적할당을 하기 위함


    Monster* monsterD = new Monster();
    monsterD->Set("테스트", 10);
    monsterD->ShowInfo();
    
    vector<Monster*> monsters2;
    for (int i = 0; i < 3; i++)
    {
        monsters2.push_back(new Monster());
    }
    monsters2[0]->Set("드래곤", 0);
    monsters2[1]->Set("슬라임", 1);
    monsters2[2]->Set("해골", 2);

    for (int i = 0; i < monsters2.size(); i++)
    {
        monsters2[i]->ShowInfo();
    }

    for (int i = 0; i < monsters2.size(); i++)
    {
        delete monsters2[i];
    }
    
    #pragma endregion
    
    #pragma region Vector 활용
    /*
    // 벡터의 선언
    // vector<데이터타입> 변수명;
    vector<int> numbers;
    for (int i = 0; i < 10; i++)
    {
        // push_back(value) : 맨 뒤에 value를 삽입.
        numbers.push_back(i);
    }
    // 일정 영역을 삭제
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