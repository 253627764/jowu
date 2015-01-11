using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    class Player
    {
        Pad m_pad;

        internal Pad Pad
        {
            get { return m_pad; }
            set { m_pad = value; }
        }
        int m_score;

        public int Score
        {
            get { return m_score; }
            set { m_score = value; }
        }
        Destination m_obj;

        public Destination Obj
        {
            get { return m_obj; }
            set { m_obj = value; }
        }
        int speedLevel;

        public int SpeedLevel
        {
            get { return speedLevel; }
            set { speedLevel = value; }
        }
        bool isComputer;

        public bool IsComputer
        {
            get { return isComputer; }
            set { isComputer = value; }
        }

        public bool left()
        {
            return m_pad.moveLeft();
        }
        public bool right()
        {
            return m_pad.moveRight();
        }

        public bool turn(bool isClockWise)
        {
            return m_pad.turn(isClockWise);
        }

        public bool drop()
        {
            return m_pad.drop();
        }
        public bool down()
        {
            return m_pad.down();
        }

        public bool attack(int addLines)
        {
            return false;
        }

        public bool protect(int clearLines)
        {
            return false;
        }

        public void start()
        {
            m_pad.start();
        }

        public void run()
        {
            if (m_pad != null)
            {
                m_pad.run();
            }
        }

        public Player(int row, int col, Destination obj, bool AI, List<int> word)
        {
            m_pad = new Pad(col, row, AI, word);
            m_obj = obj;
            isComputer = AI;
        }
    }

}
