namespace AIIsTheFuture
{
    partial class AIIsTheFuture
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Pb1 = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Pb1)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Pb1
            // 
            this.Pb1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Pb1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Pb1.Location = new System.Drawing.Point(327, 14);
            this.Pb1.Name = "Pb1";
            this.Pb1.Size = new System.Drawing.Size(220, 500);
            this.Pb1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Pb1.TabIndex = 15;
            this.Pb1.TabStop = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(763, 208);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 16;
            this.button1.Text = "start";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(710, 283);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 16;
            this.button2.Text = "button1";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // AIIsTheFuture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(875, 528);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Pb1);
            this.Name = "AIIsTheFuture";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.AIIsTheFuture_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Pb1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.PictureBox Pb1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

