// A-2.Template.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

template <typename T>
T sum(T a, T b) { return a + b; }



template <typename T>
class MyVector
{
    T data;
};

class Pointer
{
    int x;
    int y;

public:
    Pointer(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Pointer operator+(Pointer& p)
    {
        return Pointer(x + p.x, y + p.y); 
    }
    Pointer operator+(int pointer)
    {
        return *this;
    }
    void operator+=(Pointer& p)
    {
        this->x += p.x;
        this->y += p.y;
    }
    void ShowPosition()
    {
        cout << "x : " << x << ", y : " << y;
    }
};

int main()
{
    cout << sum(2, 2) << endl;
    cout << sum(3.2f, 1.0f) << endl;
    cout << sum(2.21, 2.92) << endl;

    Pointer object(3, 4);
    Pointer delta(1, 1);

    object = sum(object, delta);

    object += delta;
    object.ShowPosition();
   //MyVector<int> iVector;
   //MyVector<float> fVector; 
}
