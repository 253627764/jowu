using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace AIIsTheFuture
{
    class Block
    {
        public enum BlockType
        {
            BlockType_Line = 1,
            BlockType_Square = 2,
            BlockType_Z = 3,
            BlockType_MirroZ = 4,
            BlockType_Hill = 5,
            BlockType_L = 6,
            BlockType_MirrorL = 7,
        }

        private BlockType m_type;

        public BlockType Type
        {
            get { return m_type; }
            set { m_type = value; }
        }
        private Block m_left;

        public Block Left
        {
            get { return m_left; }
            set { m_left = value; }
        }
        private Block m_right;

        public Block Right
        {
            get { return m_right; }
            set { m_right = value; }
        }
        private Color m_color;


        List<int> eachRow = new List<int>();

        public List<int> EachRow
        {
            get { return eachRow; }
            set { eachRow = value; }
        }
        public Color Color
        {
            get { return m_color; }
            set { m_color = value; }
        }
        private List<Point> m_pointList;

        public List<Point> PointList
        {
            get { return m_pointList; }
            set { m_pointList = value; }
        }
        private int m_changeTimes;
        
        public int ChangeTimes
        {
            get { return m_changeTimes; }
            set { m_changeTimes = value; }
        }

        private int m_maxChangeTimes;

        public int MaxChangeTimes
        {
            get { return m_maxChangeTimes; }
            set { m_maxChangeTimes = value; }
        }
        private int m_d;

        public int D
        {
            get { return m_d; }
            set { m_d = value; }
        }

        private string m_name;

        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }

        public override string ToString()
        { 
            return m_name + "转了" + m_changeTimes.ToString() + "次";
        }

        public Block(BlockType type, Color color, List<Point> data , int changeTimes,int maxChangeTimes, int value, string name)
        {
            m_type = type;
            m_color = color;
            m_pointList = data;
            m_changeTimes = changeTimes;
            m_maxChangeTimes = maxChangeTimes;
            m_d = value;
            m_name = name;
            Translate();
        }

        private static Dictionary<BlockType, List<Block> > blockGroup = new Dictionary<BlockType, List<Block> >();
        public static Dictionary<BlockType, List<Block> > BlockGroup
        {
            get
            {
                return blockGroup;
            }
        }

        private static void initializeBlockData(BlockType type, string name, List<Point> points, Color color, int maxChangeTimes, int D, int length)
        {   
            int flag;
            if (length < 3)
            {
                 flag = 1;
            }
            else
            {
                flag = 0;
            }
            List<Block> theSetGourp = new List<Block>();
            List<Point> nowPoint=new List<Point>();

            for (int i = 0; i < maxChangeTimes; i++)
            {
                List<Point> rotatedPoint = new List<Point>(); 
                rotatedPoint.Add(new Point(0, 0));
                rotatedPoint.Add(new Point(0, 0));
                rotatedPoint.Add(new Point(0, 0));
                rotatedPoint.Add(new Point(0, 0));
                if (i == 0)
                {
                    Block currentSet = new Block(type, color, points, i, maxChangeTimes, D, name);
                    theSetGourp.Add(currentSet);
                    for (int m = 0; m < points.Count; m++)
                    {
                        nowPoint.Add(new Point(points[m].X, points[m].Y));
                    }
                }
                else
                {
                    for (int k = 0; k < nowPoint.Count; k++)
                    {
                        rotatedPoint[k].X = nowPoint[k].Y + flag;
                        rotatedPoint[k].Y = length - 1 + flag - nowPoint[k].X;
                    }
                    Block rotateBlock = new Block(type, color, rotatedPoint, i, maxChangeTimes, D, name);
                    theSetGourp.Add(rotateBlock);
                    nowPoint.Clear();
                    for (int m = 0; m < rotatedPoint.Count; m++)
                    {
                        nowPoint.Add(new Point(rotatedPoint[m].X, rotatedPoint[m].Y));
                    }
                }
            }
            for (int i = 0; i < maxChangeTimes; i++)
            {
                theSetGourp[i].Left = theSetGourp[(i + 1) % (maxChangeTimes)];
                theSetGourp[i].Right = theSetGourp[(i +maxChangeTimes-1) % (maxChangeTimes)];
            }
            blockGroup.Add(type,theSetGourp);
        }

        private void Translate()
        {
            eachRow.Clear();
            for (int i = 0; i < 4; i++)
            {
                eachRow.Add(0);
            }
            foreach (Point p in m_pointList)
            {
                try
                {
                    eachRow[p.Y] = eachRow[p.Y] | (1 << (3 - p.X));
                }
                catch
                {
                    continue;
                }
            }
        }

        public static void Intialize()
        {
            if (!blockGroup.ContainsKey(BlockType.BlockType_Line))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(0, 1));
                allPoint.Add(new Point(1, 1));
                allPoint.Add(new Point(2, 1));
                allPoint.Add(new Point(3, 1));
                initializeBlockData(BlockType.BlockType_Line, "Line", allPoint, Color.Red, 2, 100, 4);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_Square))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(1, 0)); //  [][]
                allPoint.Add(new Point(1, 1)); //  [][]
                allPoint.Add(new Point(2, 0)); // 
                allPoint.Add(new Point(2, 1)); //  
                initializeBlockData(BlockType.BlockType_Square, "Square", allPoint, Color.Yellow, 1, 100, 2);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_Z))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(0, 0)); //[][]        []
                allPoint.Add(new Point(1, 0)); //  [][]    [][]
                allPoint.Add(new Point(1, 1)); //          []
                allPoint.Add(new Point(2, 1)); //   
                initializeBlockData(BlockType.BlockType_Z, "Z", allPoint, Color.DodgerBlue, 2, 100, 3);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_MirroZ))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(0, 0)); //[]
                allPoint.Add(new Point(0, 1)); //[][]
                allPoint.Add(new Point(1, 1)); //  [] 
                allPoint.Add(new Point(1, 2)); // 
                initializeBlockData(BlockType.BlockType_MirroZ, "MirroZ", allPoint, Color.LimeGreen, 2, 100, 3);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_Hill))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(0, 1)); //  []
                allPoint.Add(new Point(1, 0)); //[][][]
                allPoint.Add(new Point(1, 1)); //   
                allPoint.Add(new Point(2, 1)); //  
                initializeBlockData(BlockType.BlockType_Hill, "Hill", allPoint, Color.Purple, 4, 100, 3);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_L))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(0, 0)); //[]
                allPoint.Add(new Point(0, 1)); //[]
                allPoint.Add(new Point(0, 2)); //[][]   
                allPoint.Add(new Point(1, 2)); // 
                initializeBlockData(BlockType.BlockType_L, "L", allPoint, Color.GreenYellow, 4, 100, 3);
            }

            if (!blockGroup.ContainsKey(BlockType.BlockType_MirrorL))
            {
                List<Point> allPoint = new List<Point>();
                allPoint.Add(new Point(2, 0)); //    []
                allPoint.Add(new Point(2, 1)); //    []
                allPoint.Add(new Point(2, 2)); //  [][] 
                allPoint.Add(new Point(1, 2)); //  
                initializeBlockData(BlockType.BlockType_MirrorL, "MirroL", allPoint, Color.SkyBlue, 4, 100, 3);
            }
        }
    }
}
