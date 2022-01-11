#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long solution(int price, int money, int count)
{
    long long sum = 0;
    for (int i = 1; i <= count; i++)
    {
        sum += price * i;
    }
    if (sum > money)
        return sum - money;
    else
        return 0;
}

long long bestsolution(int price, int money, int count)
{
    // 1부터 n까지의 합 : n * n+1 / 2를 활용
    long long answer = (long long)(count * (count + 1) / 2) * price;
    return answer > money ? answer - money : 0;
}
int main()
{
    cout << solution(3, 20, 4) << endl;
    cout << bestsolution(3, 20, 4) << endl;
}