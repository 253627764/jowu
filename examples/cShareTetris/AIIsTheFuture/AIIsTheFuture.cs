using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
namespace AIIsTheFuture
{
    public partial class AIIsTheFuture : Form
    {
        Controler gameControler;
        Depicter gamePainter;
        
        public AIIsTheFuture()
        {
            InitializeComponent();
            gameControler = Controler.GameControler;
            gamePainter = Depicter.GamePainter;
            this.timer1.Interval = 10;
            this.Pb1.Paint += new PaintEventHandler(paintPb);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (gameControler == null || gameControler.PlayerCount == 0)
            {
                bool fedfdsf = true;
            }
            this.Pb1.Refresh();
            gameControler.run();
        }

        private void paintPb(object sender, PaintEventArgs e)
        {
            if (gameControler.PlayerCount == 0) return;

            gamePainter.paintPad(this.Pb1, e.Graphics);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            start();
        }

        void start()
        {
            gameControler.start(25, 11, 1, null, true, Words.GetWords());
            gamePainter.initialize(gameControler.Players, Color.Black, Color.DarkBlue, Color.Red);
            timer1.Start();
        }

        protected override bool ProcessDialogKey(Keys keyCode)
        {
            if(gameControler == null || gameControler.IsCoumpuer) return true;
            switch(keyCode)
            {
                case Keys.J: gameControler.left(0); break;
                case Keys.L: gameControler.right(0); break;
                case Keys.I: gameControler.turn(0, true); break;
                case Keys.K: gameControler.turn(0, false); break;
                case Keys.M: gameControler.down(0); break;
                case Keys.Space: gameControler.drop(0); break;
            }
            return true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            
        }

        private void AIIsTheFuture_Load(object sender, EventArgs e)
        {
            start();
        }

    }
}
