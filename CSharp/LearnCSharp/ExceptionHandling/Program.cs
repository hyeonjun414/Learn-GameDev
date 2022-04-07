using System;

namespace ExceptionHandling
{
    public class Wave
    {
        int[] data = new int[10];
        // 인스턴스를 인덱스 형태로 사용할 수 있다.
        public int this[int index]
        {
            get
            {
                return data[index];
            }
            set
            {
                data[index] = value;
            }
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Wave wave = null;
                wave.ToString();
                Console.WriteLine("정상 실행");
                // 예외가 발생할 수 있는 상황에 대한 코드
            }
            catch (Exception ex)
            {
                // 예외가 발생했을 때 들어오는 영역
                Console.WriteLine("에러 발생");
            }
            finally
            {
                // 무조건 실행되는 영역
                Console.WriteLine("무조건 실행");
            }
        }
    }
}
