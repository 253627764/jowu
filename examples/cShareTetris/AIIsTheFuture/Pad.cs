using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace AIIsTheFuture
{
    class Piece 
    {

        

        private Color m_color;
        private int m_status;

        public Color Color
        {
            get { return m_color; }
            set { m_color = value; }
        }
        public int Status
        {
            get { return m_status; }
            set { m_status = value; }
        }
    }
    partial class Pad
    {
        private int m_lag;
        private int m_AIstep;

        private WayPoint action;//for ai 

        private List<WayPoint> actionList;// for shape ai

        private bool isOver;

        private int m_height;

        public int Height
        {
            get { return m_height; }
            set { m_height = value; }
        }


        public bool IsOver
        {
            get { return isOver; }
            set { isOver = value; }
        }

        private bool isComputer;

        public bool IsComputer
        {
            get { return isComputer; }
            set { isComputer = value; }
        }
        
        private int m_fullLine;

        public int FullLine
        {
            get { return m_fullLine; }
            set { m_fullLine = value; }
        }

        private bool isClearLines;

        public bool IsClearLines
        {
            get { return isClearLines; }
            set { isClearLines = value; }
        }

        private int clearingStep;

        public int ClearingStep
        {
            get { return clearingStep; }
            set { clearingStep = value; }
        }

        private Piece[,] m_pool;

        public Piece[,] Pool
        {
            get { return m_pool; }
            set { m_pool = value; }
        }
        private int m_rows;

        public int Rows
        {
            get { return m_rows; }
            set { m_rows = value; }
        }
        private int m_columns;

        public int Columns
        {
            get { return m_columns; }
            set { m_columns = value; }
        }
        private Block m_currentBlock;

        public Block CurrentBlock
        {
            get { return m_currentBlock; }
            set { m_currentBlock = value; }
        }
        private Block m_nextBlock;

        public Block NextBlock
        {
            get { return m_nextBlock; }
            set { m_nextBlock = value; }
        }

        private Point m_currentPosition;

        public Point CurrentPosition
        {
            get { return m_currentPosition; }
            set { m_currentPosition = value; }
        }

        private List<int> padStatus;

        public List<int> PadStatus
        {
            get { return padStatus; }
            set { padStatus = value; }
        }

        public Pad(int col, int row, bool AI, List<int> destination)
        {
            m_destination = destination;
            padStatus = new List<int>();
            for (int i = 0; i < row; ++i)
            {
                padStatus.Add(0);
            }
            Columns = col;
            Rows = row;
            FullLine = (1 << col) - 1;
            isComputer = AI;
            if (AI)
            {
                loadSimBlocks();
                actionList = new List<WayPoint>();
            }
        }

        private void resetStatus(int formLine, int toLine)
        {
            for (int i = (formLine < 0 ? 0 : formLine); i <= (toLine > Rows - 1 ? Rows - 1 : toLine); i++)
            {
                padStatus[i] = 0;
                for (int j = 0; j < Columns; j++)
                {
                    if (Pool[j, i].Status == 0)
                    {
                        padStatus[i] = padStatus[i] | (1 << (Columns - 1 - j));
                    }
                    if (Pool[j, i].Status == -2)// only for end solid
                    {
                        padStatus[i] = (1 << Columns) - 1; break;
                    }
                }
            }
        }

        enum Action
        {
            Action_left = 1,
            Action_Right,
            Action_Turn,
            Action_Down,
        }
        public double getNum() 
        { 
            Random ro = new Random(GetRandomSeed()); 
            return ro.NextDouble(); 
        }

        public int GetRandomSeed()
        {
            byte[] bytes = new byte[4];
            System.Security.Cryptography.RNGCryptoServiceProvider rng = new System.Security.Cryptography.RNGCryptoServiceProvider();
            rng.GetBytes(bytes); return BitConverter.ToInt32(bytes, 0);
        }

        static int max = 0;
        private static Dictionary<Block.BlockType, int> dictValue =new Dictionary<Block.BlockType,int>();
        public static Dictionary<Block.BlockType, int> DictValue
        {
            get
            {
                return dictValue;
            }
        }

        public static void initRandom()
        {

            foreach (Block.BlockType theType in Block.BlockGroup.Keys)
            {

                if (dictValue.Keys.Count != 7)
                {
                    max += Block.BlockGroup[theType][0].D;
                    dictValue.Add(theType, max);
                }
            }
        }

        private Block getRandBlock()
        {
            Random rdm = new Random();
            int rd = Convert.ToInt32(getNum() * max);
            foreach (Block.BlockType theType in Block.BlockGroup.Keys)
            {
                if (rd <= dictValue[theType])
                {
                    int changedTimes = rdm.Next(Block.BlockGroup[theType][0].ChangeTimes);
                    return Block.BlockGroup[theType][changedTimes];
                }
                continue;
            }
            throw new Exception("fail to generate new block!!");
        }

        public bool isPermitted(Block block, Point position)
        {
            if (position == null || block == null) return false;
            foreach (Point p in block.PointList)
            {
                if ((p.X + position.X) < 0 || (p.X + position.X) >= Columns || (p.Y + position.Y) >= Rows)
                    return false;
                if (Pool[p.X + position.X, p.Y + position.Y].Status != -1)
                    return false;
            }
            return true;
        }

        public bool canMove(Block block, Point position)
        {
            if (null == position || null == block) return false;
            if (isPermitted(block, position))
            {
                return true;
            }
            return false;
        }

        public void addBlockToPad(Block block, Point pos)
        {
            if (block == null || pos == null)
                return;
            try
            {
                foreach (Point p in block.PointList)
                {
                    Pool[pos.X + p.X, pos.Y + p.Y].Status = 0;
                    Pool[pos.X + p.X, pos.Y + p.Y].Color = block.Color;
                }
            }
            catch
            {
                throw new Exception("add to pad failed!");
            }
            resetStatus(pos.Y, pos.Y + 3);
        }

        private void moveOneLine(int FromLine, int ToLine)
        {
            for (int i = 0; i < Columns; i++)
            {
                Pool[i, ToLine].Status = Pool[i, FromLine].Status;
                Pool[i, ToLine].Color = Pool[i, FromLine].Color;
            }
            resetStatus(0, Rows);
        }

        private void moveAllLine(int FromLine, int ToLine, int MoveLine)
        {
            if (FromLine < 0 || FromLine > Rows - 1 || ToLine < 0 || ToLine > Rows - 1 || (FromLine + MoveLine) < 0 || (FromLine + MoveLine) > Rows - 1 || (ToLine + MoveLine) < 0 || (ToLine + MoveLine) > Rows - 1)
                return;
            for (int i = FromLine; i <= ToLine; i++)
            {
                moveOneLine(i, i + MoveLine);
            }
        }

        void test()
        {
            int x =binarysearch(41212);
            int xx = binarysearch(9);
            List<int> cap = new List<int>();
            cap.Add(2047);
            cap.Add(2047);
            cap.Add(1023);
            List<int> cap1 = new List<int>();
                        cap1.Add(0);
                        cap1.Add(0);
                        cap1.Add(1023);

            Point p_end = new Point(0, 2); ;
            loadSimBlocks();
            List<WayPoint> aaa = simList(cap, p_end);
            List<WayPoint> al = new List<WayPoint>();
            //simShape(cap, al);
            //simClear(cap,  al);
            //setDropOrder(lst[0], cap1);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="step"> clear effect flag</param>
        /// <param name="low"> the lowest height of current game pool</param>
        private void killLines(int step, int low)
        {
            List<int> findLines = new List<int>();
            findLines.Clear();
            for (int i = 0; i <= low; i++)
            {
                if (padStatus[i] == FullLine)
                {
                    findLines.Add(i);
                }
            }
            if (findLines.Count > 0)
            {
                clearingStep = step;
                for (int i = 0; i < findLines.Count; i++)
                {
                    for (int j = 0; j < Columns; j++)
                    {
                        Pool[j, findLines[i]].Status = 1;
                        Pool[j, findLines[i]].Color= Color.Black;
                    }
                }
            }
        }

        private void eliminateLines(int low)
        {
            int DropLine = 0;
            if (clearingStep == 5)
            {
                for (int i = m_rows - 1 - low; i >= 0; i--)
                {
                    if (Pool[0, i].Status > 0 && Pool[0, i].Status < 5)
                    {
                        DropLine++; continue;
                    }
                    for (int j = 0; j < Columns; j++)
                    {
                        Pool[j, i + DropLine].Status = Pool[j, i].Status;
                        Pool[j, i + DropLine].Color = Pool[j, i].Color;
                    }
                }
                for (int i = 0; i < DropLine; i++)
                {
                    for (int j = 0; j < Columns; j++)
                    {
                        Pool[j, i].Status = -1;
                    }
                }

                 resetStatus(0, Rows-low);
                //resetStatus(0, ShapeFlag != 0 ? rowsCount - Height : rowsCount - Height - 1);
                //droppadEndSolid面向了两种情形：成型落、防守落
                //对于成型落-shapeFlag!=0-height++，这里消行要读到它的下一层，采用rowscount-Height+1
                clearingStep = 0;
            }
            else
            {
                clearingStep++;
                for (int i = 0; i < m_rows - low; i++)
                {
                    if (Pool[0, i].Status > 0 && Pool[0, i].Status < 5)
                    {
                        for (int j = 0; j < Columns; j++)
                        {
                            Pool[j, i].Status = clearingStep -1 ;
                        }
                    }
                }
            }
        }

        void eliminatePool()
        {
            if (Pool == null) return;
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    if (Pool[i, j] == null)
                        Pool[i, j] = new Piece();
                    Pool[i, j].Status = -1;
                    Pool[i, j].Color = Color.Black;
                }
            }
        }

        private Block getRandomBlock()
        {
            Random rdm = new Random();
            //静态RandomSet方法不让用这个getNum()方法呢
            int rd = Convert.ToInt32(getNum() * max);
            foreach (Block.BlockType theType in Block.BlockGroup.Keys)
            {
                if (rd <= dictValue[theType])
                {
                    //随机确定转动次数
                    int changedTimes = rdm.Next(Block.BlockGroup[theType][0].MaxChangeTimes);
                    return Block.BlockGroup[theType][changedTimes];
                }
                continue;
            }
            throw new Exception("--");
        }

        public void start()
        {
            isOver = false;
            eliminatePool();
            initRandom();
            m_currentPosition = new Point((int)((Columns - 3) / 2), 0);
            if (Pool == null)
            {
                Pool = new Piece[Columns, Rows];
                for (int i = 0; i < Columns; i++)
                {
                    for (int j = 0; j < Rows; j++)
                    {
                        if (Pool[i, j] == null)
                        {
                            Pool[i, j] = new Piece();
                        }
                        Pool[i, j].Status = -1;
                        Pool[i, j].Color = Color.White;
                    }
                }
            }
            if (!isComputer)
            {   
                CurrentBlock = getRandBlock();
            }
        }
        private void play()
        {
            if (m_lag > 20)
            {
                m_lag = 0;
                if (isPermitted(m_currentBlock, new Point(m_currentPosition.X, m_currentPosition.Y + 1)))
                {
                    ++m_currentPosition.Y;
                }
                else
                {
                    addBlockToPad(m_currentBlock, m_currentPosition);
                    killLines(5, m_rows - 1);
                    m_currentBlock = getRandBlock();
                    m_currentPosition = new Point((int)((Columns - 3) / 2), 0);
                    if (!isPermitted(m_currentBlock, m_currentPosition))
                    {
                        this.isOver = true;
                    }
                }
            }
            else
            {
                ++m_lag;
            }
        }

        

        public void run()
        {
            if (isOver) return;
            if (isComputer)
            {
                //playAI();
                testAI();
            }
            else
            {
                play();
            }
        }





    }
}
