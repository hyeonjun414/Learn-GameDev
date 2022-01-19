// forward_list.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <forward_list>

using namespace std;

struct citizen
{
    string name;
    int age;

    void printCitizen()
    {
        cout << name << " " << age << endl;
    }
};

int main()
{
    #pragma region 기본 문법
    // 한쪽방향으로 진행하는 연결리스트
    // 선언 및 생성
    forward_list<int> fwd_list = { 1,2,3 };
    // push_front(value) : 맨 앞에 데이터 추가
    fwd_list.push_front(0);

    auto it = fwd_list.begin(); // 데이터 시작점을 반복자로 받음

    // insert_after(iter, value) : iter 위치 다음에 value를 삽입함.
    fwd_list.insert_after(it, 5); // 맨 처음 데이터 다음 위치에 5를 추가한다.
    fwd_list.insert_after(it, 6); // 다시 맨 처음 데이터 다음 위치에 5를 추가한다.

    fwd_list = { 1,2,3,4,5 };
    
    fwd_list.pop_front(); // pop_front() : 맨 앞에 원소를 삭제한다.
    it = fwd_list.begin();
    fwd_list.erase_after(it); // erase_after() : 맨 앞의 다음 원소를 삭제한다.
    fwd_list.erase_after(it, fwd_list.end()); // 맨 앞 다음 원소 부터 끝까지 삭제한다.
#pragma endregion

    #pragma region remove_if 사용하기
    forward_list<citizen> citizens = {
        {"Kim", 22},
        {"Lee", 25},
        {"Park", 18},
        {"Jin", 16}
    };

    auto citizens_copy = citizens; // deep copy;

    cout << "전체 시민들 :" << endl;
    for (auto c : citizens)
    {
        c.printCitizen();
    }
    cout << endl;

    // [] : 람다식  ([](매개변수){구현부 반환부});
    citizens.remove_if([](citizen& c) {
        return (c.age < 19);
        });

    cout << "투표권이 있는 시민들 :" << endl;
    for (auto c : citizens)
    {
        c.printCitizen();
    }

    citizens_copy.remove_if([](citizen& c) {
        return c.age != 18;
        });
    cout << endl;

    cout << "내년에 투표권이 생기는 시민들 :" << endl;
    for (auto c : citizens_copy)
    {
        c.printCitizen();
    }

    //remove()와 remove_if() 함수는 리스트 전체를 순회하면서 
    //조건에 맞는 원소를 모두 삭제하므로 O(n)의 시간 복잡도를 가진다.




#pragma endregion



    
    
}

