using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    class Controler
    {
        int playerCount;

        public int PlayerCount
        {
            get { return playerCount; }
            set { playerCount = value; }
        }
        List<Player> players;

        public List<Player> Players
        {
            get { return players; }
            set { players = value; }
        }
        int rows;

        public int Rows
        {
            get { return rows; }
            set { rows = value; }
        }
        int columns;

        public int Columns
        {
            get { return columns; }
            set { columns = value; }
        }
        bool isCoumpuer;

        public bool IsCoumpuer
        {
            get { return isCoumpuer; }
            set { isCoumpuer = value; }
        }

        public void run()
        {
            if (null == players) 
            {
                return;
            }

            for (int i = 0; i < playerCount; i++)
            {
                players[i].run();
            }
        }

        public void start(int row, int col, int playerCount, Destination destination, bool AI, Dictionary<int, List<int>> dict)
        {
            if (null != players)
            {
                players.Clear();
            }

            this.players = new List<Player>();
            this.playerCount = playerCount;
            Block.Intialize();

            for (int i = 0; i < playerCount; i++)
            {
                Player thePlayer = new Player(row, col, destination, AI, dict[i]);
                thePlayer.start();
                players.Add(thePlayer);
            }
        }

        public bool left(int index)
        {
            bool ret = false;
            if (null != players[index])
            {
                ret = players[index].left();
            }
            return ret;
        }

        public bool right(int index)
        {
            bool ret = false;
            if (null != players[index])
            {
                ret = players[index].right();
            }
            return ret;
        }

        public bool turn(int index, bool isClockWise)
        {
            bool ret = false;
            if (null != players[index])
            {
                ret = players[index].turn(isClockWise);
            }
            return ret;
        }

        public bool drop(int index)
        {
            bool ret = false;
            if (null != players[index])
            {
                ret = players[index].drop();
            }
            return ret;
        }

        public bool down(int index)
        {
            bool ret = false;
            if (null != players[index])
            {
                ret = players[index].down();
            }
            return ret;
        }

        public Controler()
        {
            
        }

        private static Controler gameControler = new Controler();
        public static Controler GameControler
        {
            get
            {
                return gameControler;
            }
        }
    }
}
