using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    class Point
    {
        public Point(int _x, int _y) {
            x = _x;
            y = _y;
        }

        public Point(int _x, int _y, int _state)
        {
            x = _x;
            y = _y;
            state = _state;
        }

        private int x;

        public int X
        {
            get { return x; }
            set { x = value; }
        }
        private int y;

        public int Y
        {
            get { return y; }
            set { y = value; }
        }

        private int state;

        public int State
        {
            get { return state; }
            set { state = value; }
        }

        public Point movePosition(Point pos)
        {
            x += pos.X;
            y += pos.Y;
            return new Point(x, y);
        }




    }
}
