using System;
using System.Collections.Generic;

namespace Astar
{
    internal class Program
    {
        public const int MAP_SIZE = 7;

        public static int[,] map =
        {
            {1, 0, 1, 1, 1, 1, 1 },
            {1, 0, 1, 0, 1, 0, 1 },
            {1, 1, 1, 0, 1, 0, 1 },
            {1, 1, 0, 1, 1, 0, 1 },
            {1, 1, 1, 1, 1, 0, 0 },
            {1, 1, 0, 1, 1, 1, 1 },
            {1, 1, 1, 1, 1, 0, 1 }
        };


        static void Main(string[] args)
        {
            PathFinder pf = new PathFinder();
            pf.ExcutePathFind(new Point(0, 0), new Point(6, 6), map, MAP_SIZE, PathFinder.MODE.None8);
        }
    }
}
