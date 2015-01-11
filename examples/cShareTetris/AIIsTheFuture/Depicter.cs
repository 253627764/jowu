using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace AIIsTheFuture
{
    class Depicter
    {
        List<Player> m_players;

        Color m_backColor;
        Color m_finishColor;
        Color m_boderColor;

        int m_pix;

        public void paintPad(PictureBox pb, Graphics g)
        {
            for (int cnt = 0; cnt < m_players.Count; ++cnt)
            {
                if (m_players[cnt].Pad != null)
                {
                    for (int i = 0; i < m_players[cnt].Pad.Rows; i++)
                    {
                        for (int j = 0; j < m_players[cnt].Pad.Columns; j++)
                        {
                            switch (m_players[cnt].Pad.Pool[j, i].Status)
                            {
                                case -3:
                                    {
                                        g.DrawRectangle(new Pen(m_boderColor), new Rectangle(m_pix * j - 1, m_pix * i - 1, m_pix - 2, m_pix - 2));
                                        g.FillRectangle(new SolidBrush(Color.Black), new Rectangle(m_pix * j, m_pix * i, m_pix - 3, m_pix - 3));
                                    }
                                    break;
                                case -2:
                                    {
                                        g.DrawRectangle(new Pen(m_boderColor), new Rectangle(m_pix * j - 1, m_pix * i - 1, m_pix - 2, m_pix - 2));
                                        g.FillRectangle(new SolidBrush(m_finishColor), new Rectangle(m_pix * j, m_pix * i, m_pix - 3, m_pix - 3));
                                    }
                                    break;
                                case -1:
                                    {
                                        g.DrawRectangle(new Pen(m_boderColor), new Rectangle(m_pix * j - 1, m_pix * i - 1, m_pix - 2, m_pix - 2));
                                        g.FillRectangle(new SolidBrush(m_backColor), new Rectangle(m_pix * j, m_pix * i, m_pix - 3, m_pix - 3));
                                    }
                                    break;
                                case 0:
                                    {
                                        g.DrawRectangle(new Pen(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j - 1, m_pix * i - 1, m_pix - 2, m_pix - 2));
                                        g.FillRectangle(new SolidBrush(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j, m_pix * i, m_pix - 3, m_pix - 3));
                                    }
                                    break;
                                case 1:
                                    {
                                        g.FillRectangle(new SolidBrush(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j - 1, m_pix * i - 1, m_pix - 2, Convert.ToInt32(m_pix)));
                                    }
                                    break;
                                case 2:
                                    {
                                        g.FillRectangle(new SolidBrush(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j - 1, m_pix * i + 5, m_pix - 2, Convert.ToInt32(0.7 * m_pix)));
                                    }
                                    break;
                                case 3:
                                    {
                                        g.FillRectangle(new SolidBrush(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j - 1, m_pix * i + 10, m_pix - 2, Convert.ToInt32(0.4 * m_pix)));
                                    }
                                    break;
                                case 4:
                                    {
                                        g.FillRectangle(new SolidBrush(m_players[cnt].Pad.Pool[j, i].Color), new Rectangle(m_pix * j - 1, m_pix * i + 14, m_pix - 2, Convert.ToInt32(0.1 * m_pix)));
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }
                    }
                    if (m_players[cnt].Pad.CurrentBlock != null)
                    {
                        foreach (Point p in m_players[cnt].Pad.CurrentBlock.PointList)
                        {
                            g.FillRectangle(new SolidBrush(m_players[cnt].Pad.CurrentBlock.Color), new Rectangle(m_pix * (p.X + m_players[cnt].Pad.CurrentPosition.X), m_pix * (p.Y + m_players[cnt].Pad.CurrentPosition.Y), m_pix - 3, m_pix - 3));
                        }
                    }
                }
            }
        }

        public void paintBlock(PictureBox pb, Graphics g)
        {
            for (int cnt = 0; cnt < m_players.Count; ++cnt)
            {
                    //dangrous code - - sb rabbit
                foreach (Point p in m_players[cnt].Pad.CurrentBlock.PointList)
                {
                    g.DrawRectangle(new Pen(m_boderColor), new Rectangle(m_pix * p.X - 1, m_pix * p.Y - 1, m_pix - 2, m_pix - 2));
                    g.FillRectangle(new SolidBrush(m_players[cnt].Pad.CurrentBlock.Color), new Rectangle(m_pix * p.X, m_pix * p.Y, m_pix - 3, m_pix - 3));
                }
            }
        }

        public void eraseBlock(PictureBox pb, Graphics g)
        {
            Pen Pout = new Pen(Color.WhiteSmoke);
            g.DrawRectangle(Pout, new Rectangle(0, 0, m_pix * 4, m_pix * 4));
        }

        public void initialize(List<Player> players, Color backColor, Color finishColor, Color boderColor)
        {
            m_pix = 20;
            m_backColor = backColor;
            m_boderColor = boderColor;
            m_finishColor = finishColor;

            m_players = new List<Player>();
            for (int i = 0; i < players.Count; ++i)
            {
                m_players.Add(players[i]);
            }
        }

        private static Depicter gamePainter = new Depicter();
        public static Depicter GamePainter
        {
            get
            {
                return gamePainter;
            }
        }
    }
}
