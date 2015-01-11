using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    partial class Pad
    {
        public bool moveLeft()
        {
            if (canMove(CurrentBlock, new Point(CurrentPosition.X - 1, CurrentPosition.Y)))
            {
                --m_currentPosition.X;
                return true;
            }
            return false;
        }

        public bool moveRight()
        {
            if (canMove(CurrentBlock, new Point(CurrentPosition.X + 1, CurrentPosition.Y)))
            {
                ++m_currentPosition.X;
                return true;
            }
            return false;
        }

        public bool turn(bool isClockWise)
        {

            if (canMove(isClockWise? CurrentBlock.Right : CurrentBlock.Left, CurrentPosition))
            {
                CurrentBlock = isClockWise ? CurrentBlock.Right : CurrentBlock.Left;
                return true;
            }
            return false;
        }

        public bool down()
        {
            if (isPermitted(CurrentBlock, new Point(m_currentPosition.X, m_currentPosition.Y + 1)))
            {
                m_currentPosition.Y += 1;
                return true;
            }
            return false;
        }
        
        public bool drop()
        {
            while (down()) ;
            addBlockToPad(CurrentBlock, m_currentPosition);
            return true;
            //CHECK IF CLEAR
        }
    }

}
