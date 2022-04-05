using System;
using System.Collections.Generic;

namespace Interface
{
    interface IDrawable
    {
        public void Draw();
    }

    class Figure : IDrawable
    {
        public virtual void Draw() { }
    }
    class Circle : Figure
    {
        public override void Draw()
        {
            Console.WriteLine("원형. 그려짐");
        }
    }
    class Rectangle : Figure
    {
        public override void Draw()
        {
            Console.WriteLine("사각형. 그려짐");
        }
    }
    class Triangle : Figure
    {
        public override void Draw()
        {
            Console.WriteLine("삼각형. 그려짐");
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            List<Figure> list = new List<Figure>();
            list.Add(new Circle());
            list.Add(new Rectangle());
            list.Add(new Triangle());

            foreach(Figure f in list)
            {
                if(f is IDrawable)
                {
                    IDrawable drawable = f as IDrawable;
                    drawable.Draw();
                }
            }
           
        }
    }
}
