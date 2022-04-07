using System;
using System.Collections.Generic;

namespace Anonymous_Method
{   
    // 익명 메서드와 람다식
    public class Player
    {
        public event EventHandler<EventArgs> PlayerChanged;
        public event EventHandler<EventArgs> PlayerPaused;
        public event EventHandler<EventArgs> PlayerStopped;

        public void DoEvent()
        {
            PlayerChanged?.Invoke(this, EventArgs.Empty);
            PlayerPaused?.Invoke(this, EventArgs.Empty);   
            PlayerStopped?.Invoke(this, EventArgs.Empty);
        }
    }
    public class Monster
    {
        public void SetPlayer(Player player)
        {
/*            player.PlayerChanged += delegate (Object sender, EventArgs e)
            {
                Console.WriteLine("몬스터가 Change 이벤트 받음");
            };
            player.PlayerPaused += delegate (Object sender, EventArgs e)
            {
                Console.WriteLine("몬스터가 Pause 이벤트 받음");
            };
            player.PlayerStopped += delegate (Object sender, EventArgs e)
            {
                Console.WriteLine("몬스터가 Stop 이벤트 받음");
            }; */
            // 람다식은 (매개변수) => 내용으로 구성된다.
            player.PlayerChanged += (Object sender, EventArgs e) =>
            {
                Console.WriteLine("몬스터가 Change 이벤트 받음");
            };
            player.PlayerPaused += (Object sender, EventArgs e) =>
            {
                Console.WriteLine("몬스터가 Pause 이벤트 받음");
            };
            player.PlayerStopped += (Object sender, EventArgs e) =>
            {
                Console.WriteLine("몬스터가 Stop 이벤트 받음");
            };
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Player player = new Player();
            Monster monster = new Monster();
            monster.SetPlayer(player);
            player.DoEvent();

            // 람다식 활용 예
            List<int> list = new List<int>();
            list.Find((x) => x > 0);
        }
    }
}
