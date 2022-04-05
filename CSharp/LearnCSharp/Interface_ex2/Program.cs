using System;
using System.Collections.Generic;

namespace Interface_ex2
{
    public interface IEnterable
    {
        public void Open(Door door);
    }
    public interface IHackable
    {
        public void Hacking(Door door);
    }
    public interface ILookable
    {
        public void Opened(IEnterable person);
        public void Hacked(IEnterable person);
    }
    public class Person : IEnterable
    {
        public virtual void MyName() { }

        public virtual void Open(Door door)
        {
            door.Opened(this);
        }
    }
    public class CEO : Person
    {
        public override void MyName() { Console.Write("사장 : "); }

    }
    public class Employee : Person
    {
        public override void MyName() { Console.Write("노동자 :"); }

    }
    public class Spy : Person, IHackable
    {
        public override void MyName() { Console.Write("스파이 : "); }

        public override void Open(Door door)
        {
            Hacking(door);
        }
        public void Hacking(Door door)
        {
            door.Hacked(this);
        }

    }
    public class Door : ILookable
    {
        public void Opened(IEnterable person)
        {
            if(person is CEO)
            {
                Console.WriteLine("사장이다. 문열어라. -> 문이 열렸다.");
            }
            else
            {
                Console.WriteLine("노동자는 못들어간다. 가라. -> 문은 굳게 닫혀있다.");
            }
        }
        public void Hacked(IEnterable person)
        {
            Console.WriteLine("스파이가 해킹을 시도한다. 즉시 검거 -> 스파이는 잡혀갔다.");
        }

    }
    internal class Program
    {
        public static int n = 0;
        static void Main(string[] args)
        {
            
            Random rand = new Random();
            Door door = new Door();
            List<Person> people = new List<Person>();
            for(int i = 0; i < 10; i++)
            {
                switch(rand.Next(0, 3))
                {
                    case 0: people.Add(new Employee()); break;
                    case 1: people.Add(new CEO()); break;
                    case 2: people.Add(new Spy()); break;
                }
            }
            foreach(Person person in people)
            {
                Console.Write(n++.ToString() + " : ");
                person.MyName();
                Console.WriteLine();
            }
            Console.WriteLine();

            for (int i = 0; i < 10; i++)
            {
                int num = rand.Next(0, 10);
                Console.Write(num.ToString() + " : ");
                people[num].MyName();
                people[num].Open(door);
            }
        }
    }
}
