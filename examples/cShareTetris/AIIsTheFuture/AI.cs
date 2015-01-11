using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    partial class Pad
    {

        public enum AI_Level
        {
            AI_Level_Normal,
            AI_Level_Clear,
            AI_Level_Shape
        };

        private bool isShaping;

        private List<int> m_destination;

        public List<int> Destination
        {
          get { return m_destination; }
          set { m_destination = value; }
        }

        private static List<WayPoint> ShapeList;
          
        public static void loadSimBlocks()
        {
            ShapeList = new List<WayPoint>();
            if(Block.BlockGroup.Count == 0) return;
          
           // 112
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Square][0], new Point(-1, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_L][0], new Point(0, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirrorL][3], new Point(0, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Z][0], new Point(-1, -1))); 
          
           // 122	  
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Hill][0], new Point(0, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Hill][3], new Point(-1, -2)));	
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Hill][2], new Point(-1, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Hill][1], new Point(-1, -2)));

          //  123
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Line][0], new Point(0, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Z][0], new Point(-1, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_Z][1], new Point(0, -2)));	
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirroZ][1], new Point(0, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirroZ][0], new Point(-1, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_L][0], new Point(-1, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_L][3], new Point(0, -1)));	
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_L][2], new Point(-2, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_L][1], new Point(0, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirrorL][2], new Point(-2, -2)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirrorL][1], new Point(-2, -1)));
                ShapeList.Add(new WayPoint(Block.BlockGroup[Block.BlockType.BlockType_MirrorL][0], new Point(-1, -2))); 
           }

        List<int> simCap(int baseHeight)
        {
            int dest = m_destination[Height];
            List<int> cap = new List<int>() ;
            cap.Add(dest);
            cap.Add(m_fullLine);
            cap.Add(m_fullLine - padStatus[baseHeight]);
            return cap;
        }

        List<WayPoint> simList(List<int> cap, Point p_end)
        {
            Random rd = new Random();
            int size = ShapeList.Count;
            int rdNum = rd.Next(size);

            List<WayPoint> ret = new List<WayPoint>();
	        for(int i = 0;i < size; i++) {
                if (canSeparate(ShapeList[(rdNum + i) % size].AimBlock, ShapeList[(rdNum + i) % size].AimPosition, p_end, cap))
		        {
                    ret.Add(new WayPoint(ShapeList[(rdNum + i) % size].AimBlock, new Point(p_end.X + ShapeList[(rdNum + i) % size].AimPosition.X, p_end.Y + ShapeList[(rdNum + i) % size].AimPosition.Y)));
		        }
	        }

	        return ret;
        }

        int binarysearch(int data)
        {
           int pos=0;
           if ((data & 0xFFFF0000) == 0)
               pos += 16;
           else
               data >>= 16;
          
           if ((data & 0xFF00) == 0)
               pos += 8;
           else
               data >>= 8;
          
           if ((data & 0xF0) == 0)
               pos += 4;
           else
               data >>= 4;

           if ((data & 0xC) == 0)	  
               pos += 2;
           else
               data >>= 2;

           if ((data & 0x2) == 0)	  
               pos += 1;

           return 31 - pos;
        }

        Point startPoint(List<int> cap)
        {
	        if(cap.Count == 2)
	        {
	            if(cap[1] != 0)
		        return new Point(m_columns - 1 - binarysearch(cap[1]), 1);
	        }
	        if(cap.Count == 3)
	        {
		        if(cap[2] != 0)
                    return new Point(m_columns - 1 - binarysearch(cap[2]), 2);
		        else
                    return new Point(m_columns - 1 - binarysearch(cap[1]), 1);
	        }

            return null;
        }

        private void simAdd(WayPoint act,  ref List<int> cap)
        {
           for (int i = 0; i < cap.Count; i++)
           {
               if (i - act.AimPosition.Y < 0 || act.AimBlock.EachRow[i - act.AimPosition.Y] == 0) continue;
               cap[i] = ((cap[i] << 4) | (act.AimBlock.EachRow[i - act.AimPosition.Y] << (m_columns - act.AimPosition.X))) >> 4;
           }
        }
            
        private bool simAddIF(WayPoint act, ref List<int> pool)
        {
            bool ret = false;
            List<int> tmp = copyListData(pool);
            int hole = Sim_HoleCount(tmp, pool.Count - 1); // check it
            simAdd(act, ref pool);
            //CORE
            ret = (hole == Sim_HoleCount(pool, pool.Count - 1));
            //CORE
            if (!ret)
            {
                pool.Clear();
                pool = copyListData(tmp);
            }

            return ret;
        }

        void simRemove(WayPoint act,  List<int> cap)
        {
           for (int i = 0; i < cap.Count; i++)
           {
               if (i - act.AimPosition.Y < 0 || act.AimBlock.EachRow[i - act.AimPosition.Y] == 0) continue;
               cap[i] = ((cap[i] << 4) ^ (act.AimBlock.EachRow[i - act.AimPosition.Y] << (m_columns - act.AimPosition.X))) >> 4;
           }
        }


        bool canSeparate(Block blk, Point p,Point p_end, List<int> cap)
        {
           Point aim = new Point(p_end.X + p.X, p_end.Y + p.Y);// get aim pos for the block
           
           for (int i = 0; i < cap.Count; i++)
           {
               if (i - aim.Y < 0 || blk.EachRow[i - aim.Y] == 0) continue;
               int hash = blk.EachRow[i - aim.Y] << (m_columns - aim.X);
               int hashcmp = hash & (cap[i] << 4);
               if ((hash & (cap[i] << 4)) != hash)
               {
                   return false;
               }
           }
            
           return true;
        }

        public static List<List<WayPoint>> lst = new List<List<WayPoint>>();

        void loadActionList(List<WayPoint> actionList)
        {
            List<WayPoint> al = new List<WayPoint>();
            for (int i = 0; i < actionList.Count; i++)
            {
                al.Add(actionList[i].Clone());
            }
            lst.Add(al);
        }

        bool isRevOver = false;

        void copyDataFromSimulation()
        {
            if (null == lst || lst.Count == 0 || lst[0].Count == 0)
                throw new Exception("error");
            isRevOver = false;
            for (int i = 0; i < lst[0].Count; i++)
            {
                actionList.Add(lst[0][i]);
            }
            lst.Clear();
            dropIndex = 0;
        }

        int dropIndex;

        void simClear(List<int> cap, List<WayPoint> actionList)
        {
            if (isRevOver) return;

            if (cap.Count == 1) {

                int a = 1;
            }
            if (cap[1] == 0 && cap[2] == 0)
            {    //FIND SOLUTION
                loadActionList(actionList);
                isRevOver = true;
                return;
            }

	        Point p = startPoint(cap);
	        List<WayPoint> waylist = simList(cap, p);

	        if(waylist.Count == 0) return;
           
	        for(int i = 0; i< waylist.Count ;i++)
	        {
                List<int> tmp = new List<int>();
                for (int k = 0; k < cap.Count; k++)
                {
                    tmp.Add(cap[k]);
                }
                actionList.Add(waylist[i]);
		        simRemove(waylist[i], cap);
                simClear(cap, actionList);

                cap.Clear();
                for (int k = 0; k < tmp.Count; k++)
                {
                    cap.Add(tmp[k]);
                }
		        actionList.Remove(waylist[i]);
	        }
        }

        void AIOfShape()
        {
            AI_Level level = isAvailable();
            switch (level)
            {
                case AI_Level.AI_Level_Normal:
                    {
                        WayPoint action = FindBestStragedy(padStatus);
                        if (action == null)
                            throw new Exception("error");
                        actionList.Add(action);
                        dropIndex = 0;
                    }
                    break;
                case AI_Level.AI_Level_Clear:
                    {
                        int curHeight = getPoolHeight(padStatus);
                        curHeight = curHeight < m_height ? m_height : curHeight;
                        if (curHeight - m_height < 0 || curHeight - m_height > 2)
                            throw new Exception("error\n");

                        List<int> cap = new List<int>();
                        for (int i = curHeight; i >= m_height; i--)
                        {
                            cap.Add(m_fullLine - padStatus[m_rows - 1 - i]);
                        }

                        if (cap.Count == 1)
                        {
                            cap.Insert(0, FullLine);
                        }

                        cap.Insert(0, m_destination[m_height]);

                        List<WayPoint> simActionList = new List<WayPoint>();
                        simClear(cap, simActionList);
                        if (lst.Count == 0)
                        {
                            WayPoint action = FindBestStragedy(padStatus);
                            if (action == null)
                                throw new Exception("error");
                            actionList.Add(action);
                            dropIndex = 0;
                        }
                        else
                        {
                            setDropOrder(cap);
                        }
                        
                    }
                    break;
                case AI_Level.AI_Level_Shape:
                    {
                        int curHeight = getPoolHeight(padStatus);
                        if (curHeight - m_height > 0)
                            throw new Exception("error\n");
                        List<int> cap = new List<int>();
                        //cap with two fulllines, may be fourlines the better
                        cap.Add(m_fullLine);
                        cap.Add(m_fullLine);
                        cap.Add(m_destination[m_height] - padStatus[m_rows - 1 - m_height]);
                        List<WayPoint> simActionList = new List<WayPoint>();
                        simShape(cap, simActionList);
                        copyDataFromSimulation();
                        isShaping = true;
                    }
                    break;
            }
        }



        AI_Level isAvailable()
        {
            AI_Level ret = AI_Level.AI_Level_Normal;
            int curHeight = getPoolHeight(padStatus);
            if (Sim_HoleCount(padStatus, m_rows - 1) == 0)
            {


                if (curHeight == m_height)
                {
                    if ((padStatus[m_rows - 1 - curHeight] | m_destination[Height]) == m_destination[Height])
                    {
                        ret = AI_Level.AI_Level_Shape;
                    }
                }
                else if (curHeight - m_height <= 1) // 1 or 0
                    ret = AI_Level.AI_Level_Clear;
                else
                    ret = AI_Level.AI_Level_Normal;
            }

            return ret;
        }

        void simShape(List<int> cap, List<WayPoint> actionList)
        {
            if (isRevOver) return;

            if (cap[2] == 0)
            {    //FIND SOLUTION
                loadActionList(actionList);
                isRevOver = true;
                return;
            }

            Point p = startPoint(cap);
            List<WayPoint> waylist = simList(cap, p);

            if (waylist.Count == 0) return;

            for (int i = 0; i < waylist.Count; i++)
            {
                List<int> tmp = new List<int>();
                for (int k = 0; k < cap.Count; k++)
                {
                    tmp.Add(cap[k]);
                }

                actionList.Add(waylist[i]);
                simRemove(waylist[i], cap);
                simShape(cap, actionList);

                cap.Clear();
                for (int k = 0; k < tmp.Count; k++)
                {
                    cap.Add(tmp[k]);
                }

                actionList.Remove(waylist[i]);
            }
        }

        List<int> copyListData(List<int> pool) 
        {
            List<int> ret = new List<int>();
            for (int i = 0; i < pool.Count; ++i)
                ret.Add(pool[i]);
            return ret;
        }

        void setDropOrder( List<int> pool)
        {
            if (null == lst || lst.Count == 0 || lst[0].Count == 0)
                throw new Exception("error");
            isRevOver = false;


            dropIndex = 0;

            actionList.Clear();
            int[] orderList = new int[lst[0].Count];
            int orderNum = 0;
            List<int> tmp = copyListData(pool);

            for (int i = 0; i < lst[0].Count; ++i)
            {
                if (isFoundation(lst[0][i], pool))
                {
                    orderList[i] = ++orderNum; // to do : swap random index
                    simAdd(lst[0][i], ref tmp);
                }
                else
                    orderList[i] = 0;
            }

            while (orderNum != lst[0].Count)
            {
                for (int i = 0; i < lst[0].Count; ++i)
                {
                    if (orderList[i] == 0)
                    {
                        if (simAddIF(lst[0][i], ref tmp))
                            orderList[i] = ++orderNum;
                    }
                }
            }
            int idx = 1;
            for (int i = 0; i < lst[0].Count; i++)
            {
                for (int j = 0; j < lst[0].Count; j++)
                {
                    if (idx == orderList[j])
                    {
                        actionList.Add(lst[0][j]);
                        ++idx;
                        break;
                    }
                }
            }

            lst.Clear();
        }

        /// <summary>
        /// drop with order, check hole when the act is executed.
        /// </summary>
        /// <param name="act"></param>
        /// <param name="pool"></param>
        /// <returns>return true if no holes</returns>
        bool isFoundation(WayPoint act, List<int> pool)
        {
            if (Sim_PositionIsPermitted(act.AimBlock, pool, new Point(act.AimPosition.X, act.AimPosition.Y + 1))) return false;
            return isBlockRotated(act.AimBlock);
        }

        bool isBlockRotated(Block block)
        {
            bool hasFindBaseLine = false;
            int baseLine = -1;
            for (int i = block.EachRow.Count - 1; i > 0 ; i--)
            {
                if (block.EachRow[i] == 0) continue;
                if (!hasFindBaseLine)
                {
                    hasFindBaseLine = true;
                    baseLine = block.EachRow[i];
                }
                else
                {
                    if ((baseLine | block.EachRow[i]) != baseLine)
                        return false;
                }
            }

            return true;
        }

        private void testAI()
        {
            int heightofpad = -1;
            for (int i = 0; i < m_rows; i++)
            {
                if (padStatus[i] != 0)
                {
                    heightofpad = i;
                    break;
                }
            }

            if (heightofpad <= 3 && heightofpad >= 0)
            {
                isOver = true;
                return;
            }

            if (m_lag >= lag)//设置游戏速度
            {
                m_lag = 0;
                if (clearingStep == 0) // 
                {
                    switch (m_AIstep)
                    {
                        case 0:
                            {
                                if (m_height >= m_destination.Count)
                                {
                                    int comeherebaby = 1;
                                }
                                if (null == actionList || 0 == actionList.Count)
                                {
                                    AIOfShape();
                                }
                                                                       // trash code
                                if (null == actionList || dropIndex >= actionList.Count || 0 > dropIndex)
                                    throw new Exception("error");
                                m_currentBlock = actionList[dropIndex].AimBlock;
                                m_currentPosition = new Point((int)((m_columns - 3) / 2), 0);
                                ++m_AIstep;
                            }
                            break;
                        case 1:
                            {
                                while (this.m_currentPosition.X > actionList[dropIndex].AimPosition.X)
                                {
                                    moveLeft();
                                }

                                while (m_currentPosition.X < actionList[dropIndex].AimPosition.X)
                                {
                                    moveRight();
                                }
                                ++m_AIstep;
                            }
                            break;
                        case 2:
                            {
                                //if ((m_currentPosition.Y < m_actionList[dropIndex].AimPosition.Y))
                                //{
                                drop();

                                //}

                                //addBlockToPad(actionList[dropIndex].AimBlock, actionList[dropIndex].AimPosition);
                                //Sound.MakeSound(7, true);
                                m_AIstep = 0;
                                killLines(1, m_rows - 1 - m_height);// update clear step
                                if (dropIndex + 1 < actionList.Count)
                                    ++dropIndex;
                                else
                                {
                                    if (isShaping)
                                    {
                                        for (int i = 0; i < m_columns; i++)
                                        {
                                            if ((padStatus[m_rows - m_height - 1] & 1 << (m_columns - 1 - i)) != 0)
                                            {
                                                Pool[i, m_rows - 1 - m_height].Status = -2;
                                            }
                                            else
                                            {
                                                Pool[i, m_rows - 1 - m_height].Status = -3;
                                            }
                                        }
                                        padStatus[m_rows - m_height - 1] = FullLine;
                                        isShaping = false;
                                        ++m_height;
                                    }
                                    
                                    actionList.Clear();
                                    
                                }
                            }
                            break;
                        default:
                            m_AIstep = 0;
                            break;
                    }
                }
                else //clearingStep <= 5 && clearingStep > 0)
                {
                    eliminateLines(m_height);
                }
            }
            else
            {
                m_lag++;
            }
            //--------------------//
        }
    }
}
