using System;

namespace Delegate
{
    // 델리게이트는 반환형과 매개변수가 같아야한다.
    // 이벤트와 마찬가지로 리스트 형태로 저장해 동시에 호출할 수 있다.
    public class Test
    {
        public delegate void TestDelegate(int a);
        public TestDelegate testDelegate;

        public void TestFunc1(int a)
        {
            Console.WriteLine("Func1 호출됨. 들어온 숫자는 " + a.ToString());
        }
        public void TestFunc2(int a)
        {
            Console.WriteLine("Func2 호출됨. 들어온 숫자에 6을 곱하면 " + (a*6).ToString());
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Test test = new Test();
            test.testDelegate += test.TestFunc1;
            test.testDelegate += test.TestFunc2;
            test.testDelegate += test.TestFunc2;
            test.testDelegate -= test.TestFunc2;

            // 함수포인터에 아무 함수가 배치되어있지않으면 오류가 발생한다.
            // Invoke는 변수를 함수 형태로 사용하여 델리게이트라고 알 수 있도록 한다.
            test.testDelegate?.Invoke(10);

            
        }
    }
}
