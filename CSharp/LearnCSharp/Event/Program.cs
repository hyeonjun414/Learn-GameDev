using System;

namespace Event
{
    #region 센더 리시버 기본
    public class Sender
    {
        public event EventHandler Event;
        public delegate void StrDelegate(string a);
        public StrDelegate strDelegate;
        public void DoEvent()
        {
            Event?.Invoke(this, EventArgs.Empty);
        }
        public void DoText(string name)
        {
            strDelegate?.Invoke(name);
        }
    }
    public class Receiver
    {
        public void CanWriteLine(object sender, EventArgs e)
        {
            Console.WriteLine("나는 출력할 수 있다.");
        }
        public void StringCount(string str)
        {
            Console.WriteLine("이 문장은 " + str.Length + "글자 이다.");
        }
        public void senderExcute(Sender sender)
        {
            sender.strDelegate.Invoke("나나");
        }
    }
    #endregion

    internal class Program
    {
        static void Main(string[] args)
        {
            Sender sender = new Sender();
            Receiver receiver = new Receiver();

            sender.Event += receiver.CanWriteLine;
            sender.DoEvent();

            sender.strDelegate = receiver.StringCount;

            sender.strDelegate.Invoke("다섯글자임");

            receiver.senderExcute(sender);
        }
    }
}
