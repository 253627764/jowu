using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    class Destination
    {
        private int layer;

        public int Layer
        {
            get { return layer; }
            set { layer = value; }
        }
        private List<int> dest;

        public List<int> Dest
        {
            get { return dest; }
            set { dest = value; }
        }

        public Destination(int index, List<int> objective)
        {
            layer = index;
            dest = objective;
        }

    }
}
