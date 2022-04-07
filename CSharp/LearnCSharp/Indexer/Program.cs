using System;

namespace Indexer
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
            Wave wave = new Wave();
            int[] intList = new int[5];

            int value = wave[0];
        }
    }
    
}
