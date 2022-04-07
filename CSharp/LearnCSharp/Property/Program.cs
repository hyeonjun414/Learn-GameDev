using System;

namespace Property
{
    public class Player
    {
        int _HP;
        public int HP 
        { 
            get
            {
                return _HP;
            }
            set
            {
                Console.WriteLine("플레이어 체력을 {0}으로 변경", value);
                Console.WriteLine("UI체력도 {0}으로 변경", value);
                _HP = value;
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Player player = new Player();

            player.HP = 0;
            player.HP = 1;
            player.HP = 2;
            player.HP = 3;
        }
    }
}
