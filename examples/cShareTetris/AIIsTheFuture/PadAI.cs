using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    partial class Pad
    {
        public class WayPoint
        {
            public WayPoint() { }

            public WayPoint(Block b, Point p)
            {
                aimBlock = b;
                aimPosition = p;
            }

            Block aimBlock;

            internal Block AimBlock
            {
                get { return aimBlock; }
                set { aimBlock = value; }
            }

            Point aimPosition;

            internal Point AimPosition
            {
                get { return aimPosition; }
                set { aimPosition = value; }
            }

            public WayPoint Clone()
            {
                return new WayPoint(this.AimBlock, this.AimPosition);
            }
        }

        void autoPlay()
        {

        }

        int getPoolHeight(List<int> pool)
        {
            int height = 0;
            int hole = 0;
            for (int i = 0; i < m_rows; i++)
            {
                if (pool[i] != 0)
                {
                    height = m_rows - i - 1;
                    break;
                }
            }
            return height;
        }

        private int Sim_HoleCount(List<int> nowSuitation, int low)
        {
            int hole = 0;
            for (int i = low; i >= 0; i--)
            {
                for (int j = 0; j < m_columns; j++)
                {
                    if ((nowSuitation[i] & 1 << (m_columns - j - 1)) != 0) continue;
                    if (((i - 1) > 0) && ((nowSuitation[i - 1] & 1 << (m_columns - j - 1)) != 0))
                    {
                        hole++;
                    }
                }
            }

            return hole;
        }

        private int Sim_Evaluate(List<int> nowSuitation, int low)
        {
            int AIScore = 0;
            if (low >= m_rows) return int.MinValue;

            for (int i = low; i >= m_height; i--)
            {
                for (int j = 0; j < m_columns; j++)
                {
                    if ((nowSuitation[i] & 1 << (m_columns - j - 1)) != 0) continue;
                    if (((nowSuitation[i] & 1 << (j == 0 ? m_columns - 1 : m_columns - j)) != 0) || ((nowSuitation[i] & 1 << (j == m_columns - 1 ? 0 : m_columns - j - 2)) != 0))
                    {
                        AIScore -= 2 * (m_rows - i);;
                    }
                    if (((i - 1) > 0) && ((nowSuitation[i - 1] & 1 << (m_columns - j - 1)) != 0))
                    {
                        AIScore -= 10 * (m_rows - i);

                    }
                }
            }

            return AIScore;
        }

        private bool Sim_PositionIsPermitted(Block block, List<int> nowSuitation, Point aimPosition)
        {
            //采用位运算，速度快
            for (int i = 0; i < 4; i++)
            {
                if (block.EachRow[i] == 0) continue;
                if (aimPosition.Y + i >= nowSuitation.Count) return false;
                switch (m_columns)
                {
                    case 4: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7fff0fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 5: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7ffe0fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 6: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7ffc0fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 7: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7ff80fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 8: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7ff00fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 9: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7fe00fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 10: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7fc00fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 11: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7f800fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 12: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7f000fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 13: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7e000fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 14: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7c000fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    case 15: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x78000fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                    default: if (((nowSuitation[i + aimPosition.Y] << 12 | 0x7fc00fff) & (block.EachRow[i] << (m_columns + 8 - aimPosition.X))) != 0) return false; break;
                }
            }
            return true;
        }

        private int Sim_ClearLines(Block theSet, ref List<int> nowSuitation, Point aimPosition)
        {
            int clearingLines = 0;
            for (int i = aimPosition.Y; i <= m_rows - 1; i++) // row - height -1
            {
                if (nowSuitation[i] == m_fullLine)
                {
                    clearingLines++;
                    nowSuitation.RemoveAt(i);
                    nowSuitation.Insert(0, 0);
                }
                continue;
            }

            return clearingLines;
        }

        private List<int> Sim_AddSetToPad(Block theSet, List<int> nowSuitation, Point aimPosition)
        {
            List<int> tempSuitation = new List<int>();
            tempSuitation.Clear();
            for (int i = 0; i < m_rows; i++)
            {
                tempSuitation.Add(nowSuitation[i]);
            }
            for (int i = 0; i < 4; i++)
            {
                if (i + aimPosition.Y >= m_rows) break;
                tempSuitation[i + aimPosition.Y] = (tempSuitation[i + aimPosition.Y] << 4 | theSet.EachRow[i] << (m_columns - aimPosition.X)) >> 4;
            }
            return tempSuitation;
        }

        private WayPoint FindBestStragedy(List<int> tempSuitation)
        {
            WayPoint ret = null;
            int bestScore = int.MinValue;
           // Block blk = getRandBlock();
            foreach (Block.BlockType type in Block.BlockGroup.Keys)
            {
                Block blk = Block.BlockGroup[type][0];
                for (int rotateTime = 0; rotateTime < blk.MaxChangeTimes; ++rotateTime)
                {
                    blk = blk.Right;
                    for (int i = -1; i < m_columns - 1; i++)
                    {
                        bool lastLineOk = false;
                        for (int j = 0; j < m_rows; j++)
                        {
                            if (Sim_PositionIsPermitted(blk, tempSuitation, new Point(i, j)))//判断下一行是否可以安放
                            {
                                lastLineOk = true;
                                continue;
                            }
                            if (lastLineOk)
                            {
                                int AiScore = 0;
                                List<int> theSuitation = Sim_AddSetToPad(blk, tempSuitation, new Point(i, j - 1));
                                int killLines = Sim_ClearLines(blk, ref theSuitation, new Point(i, j - 1));
                                AiScore = Sim_Evaluate(theSuitation, m_rows - 1);
                                if (killLines > 0 && AiScore > -3)
                                {
                                    return new WayPoint(blk, new Point(i, j - 1));
                                }

                                AiScore += 10 * killLines;
                                if (AiScore > bestScore)
                                {
                                    bestScore = AiScore;
                                    ret = new WayPoint(blk, new Point(i, j - 1));
                                }

                                j = m_rows - 1;
                            }
                            if (j == 0)
                            {
                                break;//下落点位是（1，1）为方块的中心的
                            }
                        }
                    }
                }
            }

            return ret;
        }

        static int lag = 1;

        private void playAI()
        {
            test();
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
                                action = FindBestStragedy(padStatus);
                                m_currentBlock = action.AimBlock;
                                m_currentPosition = new Point((int)((m_columns - 3) / 2), 0);
                                //addBlockToPad(m_currentBlock, m_currentPosition);
                                ++m_AIstep;
                            }
                            break;
                        case 1:
                            {
                                while (this.m_currentPosition.X > action.AimPosition.X)
                                {
                                    moveLeft();
                                }

                                while (m_currentPosition.X < action.AimPosition.X)
                                {
                                    moveRight();
                                }
                                ++m_AIstep;
                            }
                            break;
                        case 2:
                            {
                                if ((m_currentPosition.Y < action.AimPosition.Y))
                                {
                                    drop();
                                    ////while (down())
                                    ////{ }
                                }

                                addBlockToPad(action.AimBlock, action.AimPosition);
                                //Sound.MakeSound(7, true);
                                m_AIstep = 0;
                                killLines(1, m_rows - 1 - m_height);// update clear step
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
