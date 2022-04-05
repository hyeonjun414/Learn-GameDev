using System;

namespace LearnCSharp
{
    public class Person
    {
        // 분할 클래스 : partial 지시자를 사용하여 여러 파일에 나누어 작성할 수 있음 -> 자주 쓰지는 않을 듯
        protected string telephone = "12-5555-6666";
        protected string name = "홍길동";

        public virtual void GetInfo()
        {
            Console.WriteLine("Name: {0}", name);
            Console.WriteLine("Tel: {0}", telephone);
        }

    }
    
    class Employee : Person
    {
        public string id = "AVCSKWDKH2519";
        public override void GetInfo()
        {
            base.GetInfo();
            Console.WriteLine("Employee ID : {0}", id);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Employee e = new Employee();
            e.GetInfo();
        }
    }
}
