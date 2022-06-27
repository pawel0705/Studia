namespace I_4_Boids {
  partial class Form1 {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent() {
      System.Windows.Forms.SplitContainer splitContainer1;
      System.Windows.Forms.Button myRestart;
      System.Windows.Forms.GroupBox groupBox2;
      System.Windows.Forms.GroupBox groupBox4;
      System.Windows.Forms.GroupBox groupBox3;
      System.Windows.Forms.GroupBox groupBox1;
      System.Windows.Forms.Label label5;
      this.myRenderArea = new ctlRenderArea.RenderArea();
      this.myPaused = new System.Windows.Forms.CheckBox();
      this.label1 = new System.Windows.Forms.Label();
      this.myViewBoidColor = new System.Windows.Forms.Label();
      this.myViewBoidVectorE = new System.Windows.Forms.CheckBox();
      this.myViewBoidEnable = new System.Windows.Forms.CheckBox();
      this.myCurrentBot = new System.Windows.Forms.NumericUpDown();
      this.myViewBoidVectorR = new System.Windows.Forms.CheckBox();
      this.myViewBoidRadiusS = new System.Windows.Forms.CheckBox();
      this.myViewBoidVectorA = new System.Windows.Forms.CheckBox();
      this.myViewBoidVectorC = new System.Windows.Forms.CheckBox();
      this.myViewBoidVectorS = new System.Windows.Forms.CheckBox();
      this.myViewAllVectorR = new System.Windows.Forms.CheckBox();
      this.myViewAllRadiusS = new System.Windows.Forms.CheckBox();
      this.myViewAllVectorE = new System.Windows.Forms.CheckBox();
      this.myViewAllVectorA = new System.Windows.Forms.CheckBox();
      this.myViewAllVectorC = new System.Windows.Forms.CheckBox();
      this.myViewAllVectorS = new System.Windows.Forms.CheckBox();
      this.myBotsVelocity = new System.Windows.Forms.TrackBar();
      this.label6 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.myBoidType = new System.Windows.Forms.ComboBox();
      this.myBoidInitVelocity = new System.Windows.Forms.ComboBox();
      this.myBoidInitPlacement = new System.Windows.Forms.ComboBox();
      this.myBoidsCount = new System.Windows.Forms.NumericUpDown();
      this.label4 = new System.Windows.Forms.Label();
      splitContainer1 = new System.Windows.Forms.SplitContainer();
      myRestart = new System.Windows.Forms.Button();
      groupBox2 = new System.Windows.Forms.GroupBox();
      groupBox4 = new System.Windows.Forms.GroupBox();
      groupBox3 = new System.Windows.Forms.GroupBox();
      groupBox1 = new System.Windows.Forms.GroupBox();
      label5 = new System.Windows.Forms.Label();
      splitContainer1.Panel1.SuspendLayout();
      splitContainer1.Panel2.SuspendLayout();
      splitContainer1.SuspendLayout();
      groupBox2.SuspendLayout();
      groupBox4.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.myCurrentBot)).BeginInit();
      groupBox3.SuspendLayout();
      groupBox1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.myBotsVelocity)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.myBoidsCount)).BeginInit();
      this.SuspendLayout();
      // 
      // splitContainer1
      // 
      splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
      splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
      splitContainer1.IsSplitterFixed = true;
      splitContainer1.Location = new System.Drawing.Point(0, 0);
      splitContainer1.Name = "splitContainer1";
      // 
      // splitContainer1.Panel1
      // 
      splitContainer1.Panel1.Controls.Add(this.myRenderArea);
      // 
      // splitContainer1.Panel2
      // 
      splitContainer1.Panel2.Controls.Add(myRestart);
      splitContainer1.Panel2.Controls.Add(this.myPaused);
      splitContainer1.Panel2.Controls.Add(groupBox2);
      splitContainer1.Panel2.Controls.Add(groupBox1);
      splitContainer1.Panel2.Controls.Add(this.myBoidsCount);
      splitContainer1.Panel2.Controls.Add(this.label4);
      splitContainer1.Size = new System.Drawing.Size(1018, 642);  //ToDo Zmiana rozmiaru obszaru, aby poprawiæ widocznoœæ przycisków: np.: Size(1100,642)
      splitContainer1.SplitterDistance = 770;
      splitContainer1.TabIndex = 0;
      // 
      // myRenderArea
      // 
      this.myRenderArea.Dock = System.Windows.Forms.DockStyle.Fill;
      this.myRenderArea.Location = new System.Drawing.Point(0, 0);
      this.myRenderArea.Name = "myRenderArea";
      this.myRenderArea.Size = new System.Drawing.Size(770, 642);
      this.myRenderArea.TabIndex = 0;
      this.myRenderArea.Text = "renderArea1";
      this.myRenderArea.Paint += new System.Windows.Forms.PaintEventHandler(this.OnPaint);
      this.myRenderArea.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OnClick);
      // 
      // myRestart
      // 
      myRestart.Location = new System.Drawing.Point(2, 492);
      myRestart.Name = "myRestart";
      myRestart.Size = new System.Drawing.Size(75, 23);
      myRestart.TabIndex = 7;
      myRestart.Text = "Restart";
      myRestart.UseVisualStyleBackColor = true;
      myRestart.Click += new System.EventHandler(this.myRestart_Click);
      // 
      // myPaused
      // 
      this.myPaused.Appearance = System.Windows.Forms.Appearance.Button;
      this.myPaused.AutoSize = true;
      this.myPaused.Location = new System.Drawing.Point(83, 492);
      this.myPaused.Name = "myPaused";
      this.myPaused.Size = new System.Drawing.Size(47, 23);
      this.myPaused.TabIndex = 6;
      this.myPaused.Text = "Pause";
      this.myPaused.UseVisualStyleBackColor = true;
      // 
      // groupBox2
      // 
      groupBox2.Controls.Add(groupBox4);
      groupBox2.Controls.Add(groupBox3);
      groupBox2.Location = new System.Drawing.Point(2, 173);
      groupBox2.Name = "groupBox2";
      groupBox2.Size = new System.Drawing.Size(239, 313);
      groupBox2.TabIndex = 5;
      groupBox2.TabStop = false;
      groupBox2.Text = "View";
      // 
      // groupBox4
      // 
      groupBox4.Controls.Add(this.label1);
      groupBox4.Controls.Add(this.myViewBoidColor);
      groupBox4.Controls.Add(this.myViewBoidVectorE);
      groupBox4.Controls.Add(this.myViewBoidEnable);
      groupBox4.Controls.Add(this.myCurrentBot);
      groupBox4.Controls.Add(this.myViewBoidVectorR);
      groupBox4.Controls.Add(this.myViewBoidRadiusS);
      groupBox4.Controls.Add(this.myViewBoidVectorA);
      groupBox4.Controls.Add(this.myViewBoidVectorC);
      groupBox4.Controls.Add(this.myViewBoidVectorS);
      groupBox4.Location = new System.Drawing.Point(6, 159);
      groupBox4.Name = "groupBox4";
      groupBox4.Size = new System.Drawing.Size(227, 148);
      groupBox4.TabIndex = 7;
      groupBox4.TabStop = false;
      groupBox4.Text = "Current";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(119, 109);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(23, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "Bot";
      // 
      // myViewBoidColor
      // 
      this.myViewBoidColor.Location = new System.Drawing.Point(145, 63);
      this.myViewBoidColor.Name = "myViewBoidColor";
      this.myViewBoidColor.Size = new System.Drawing.Size(79, 23);
      this.myViewBoidColor.TabIndex = 4;
      // 
      // myViewBoidVectorE
      // 
      this.myViewBoidVectorE.AutoSize = true;
      this.myViewBoidVectorE.Checked = true;
      this.myViewBoidVectorE.CheckState = System.Windows.Forms.CheckState.Checked;
      this.myViewBoidVectorE.Location = new System.Drawing.Point(6, 105);
      this.myViewBoidVectorE.Name = "myViewBoidVectorE";
      this.myViewBoidVectorE.Size = new System.Drawing.Size(91, 17);
      this.myViewBoidVectorE.TabIndex = 0;
      this.myViewBoidVectorE.Text = "Enemy vector";
      this.myViewBoidVectorE.UseVisualStyleBackColor = true;
      // 
      // myViewBoidEnable
      // 
      this.myViewBoidEnable.AutoSize = true;
      this.myViewBoidEnable.Location = new System.Drawing.Point(59, 16);
      this.myViewBoidEnable.Name = "myViewBoidEnable";
      this.myViewBoidEnable.Size = new System.Drawing.Size(108, 17);
      this.myViewBoidEnable.TabIndex = 3;
      this.myViewBoidEnable.Text = "View current boid";
      this.myViewBoidEnable.UseVisualStyleBackColor = true;
      // 
      // myCurrentBot
      // 
      this.myCurrentBot.Location = new System.Drawing.Point(148, 107);
      this.myCurrentBot.Maximum = new decimal(new int[] {
            50001,
            0,
            0,
            0});
      this.myCurrentBot.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
      this.myCurrentBot.Name = "myCurrentBot";
      this.myCurrentBot.Size = new System.Drawing.Size(68, 20);
      this.myCurrentBot.TabIndex = 2;
      this.myCurrentBot.ValueChanged += new System.EventHandler(this.OnCurrentBot_Changed);
      // 
      // myViewBoidVectorR
      // 
      this.myViewBoidVectorR.AutoSize = true;
      this.myViewBoidVectorR.Checked = true;
      this.myViewBoidVectorR.CheckState = System.Windows.Forms.CheckState.Checked;
      this.myViewBoidVectorR.Location = new System.Drawing.Point(122, 39);
      this.myViewBoidVectorR.Name = "myViewBoidVectorR";
      this.myViewBoidVectorR.Size = new System.Drawing.Size(94, 17);
      this.myViewBoidVectorR.TabIndex = 0;
      this.myViewBoidVectorR.Text = "Sensor sphere";
      this.myViewBoidVectorR.UseVisualStyleBackColor = true;
      // 
      // myViewBoidRadiusS
      // 
      this.myViewBoidRadiusS.AutoSize = true;
      this.myViewBoidRadiusS.Location = new System.Drawing.Point(6, 125);
      this.myViewBoidRadiusS.Name = "myViewBoidRadiusS";
      this.myViewBoidRadiusS.Size = new System.Drawing.Size(120, 17);
      this.myViewBoidRadiusS.TabIndex = 0;
      this.myViewBoidRadiusS.Text = "Separation distance";
      this.myViewBoidRadiusS.UseVisualStyleBackColor = true;
      // 
      // myViewBoidVectorA
      // 
      this.myViewBoidVectorA.AutoSize = true;
      this.myViewBoidVectorA.Checked = true;
      this.myViewBoidVectorA.CheckState = System.Windows.Forms.CheckState.Checked;
      this.myViewBoidVectorA.Location = new System.Drawing.Point(6, 85);
      this.myViewBoidVectorA.Name = "myViewBoidVectorA";
      this.myViewBoidVectorA.Size = new System.Drawing.Size(105, 17);
      this.myViewBoidVectorA.TabIndex = 0;
      this.myViewBoidVectorA.Text = "Alignment vector";
      this.myViewBoidVectorA.UseVisualStyleBackColor = true;
      // 
      // myViewBoidVectorC
      // 
      this.myViewBoidVectorC.AutoSize = true;
      this.myViewBoidVectorC.Checked = true;
      this.myViewBoidVectorC.CheckState = System.Windows.Forms.CheckState.Checked;
      this.myViewBoidVectorC.Location = new System.Drawing.Point(6, 62);
      this.myViewBoidVectorC.Name = "myViewBoidVectorC";
      this.myViewBoidVectorC.Size = new System.Drawing.Size(103, 17);
      this.myViewBoidVectorC.TabIndex = 0;
      this.myViewBoidVectorC.Text = "Cohesion vector";
      this.myViewBoidVectorC.UseVisualStyleBackColor = true;
      // 
      // myViewBoidVectorS
      // 
      this.myViewBoidVectorS.AutoSize = true;
      this.myViewBoidVectorS.Checked = true;
      this.myViewBoidVectorS.CheckState = System.Windows.Forms.CheckState.Checked;
      this.myViewBoidVectorS.Location = new System.Drawing.Point(6, 39);
      this.myViewBoidVectorS.Name = "myViewBoidVectorS";
      this.myViewBoidVectorS.Size = new System.Drawing.Size(110, 17);
      this.myViewBoidVectorS.TabIndex = 0;
      this.myViewBoidVectorS.Text = "Separation vector";
      this.myViewBoidVectorS.UseVisualStyleBackColor = true;
      // 
      // groupBox3
      // 
      groupBox3.Controls.Add(this.myViewAllVectorR);
      groupBox3.Controls.Add(this.myViewAllRadiusS);
      groupBox3.Controls.Add(this.myViewAllVectorE);
      groupBox3.Controls.Add(this.myViewAllVectorA);
      groupBox3.Controls.Add(this.myViewAllVectorC);
      groupBox3.Controls.Add(this.myViewAllVectorS);
      groupBox3.Location = new System.Drawing.Point(6, 19);
      groupBox3.Name = "groupBox3";
      groupBox3.Size = new System.Drawing.Size(227, 134);
      groupBox3.TabIndex = 6;
      groupBox3.TabStop = false;
      groupBox3.Text = "All";
      // 
      // myViewAllVectorR
      // 
      this.myViewAllVectorR.AutoSize = true;
      this.myViewAllVectorR.Location = new System.Drawing.Point(122, 19);
      this.myViewAllVectorR.Name = "myViewAllVectorR";
      this.myViewAllVectorR.Size = new System.Drawing.Size(94, 17);
      this.myViewAllVectorR.TabIndex = 0;
      this.myViewAllVectorR.Text = "Sensor sphere";
      this.myViewAllVectorR.UseVisualStyleBackColor = true;
      // 
      // myViewAllRadiusS
      // 
      this.myViewAllRadiusS.AutoSize = true;
      this.myViewAllRadiusS.Location = new System.Drawing.Point(6, 111);
      this.myViewAllRadiusS.Name = "myViewAllRadiusS";
      this.myViewAllRadiusS.Size = new System.Drawing.Size(120, 17);
      this.myViewAllRadiusS.TabIndex = 0;
      this.myViewAllRadiusS.Text = "Separation distance";
      this.myViewAllRadiusS.UseVisualStyleBackColor = true;
      // 
      // myViewAllVectorE
      // 
      this.myViewAllVectorE.AutoSize = true;
      this.myViewAllVectorE.Location = new System.Drawing.Point(6, 88);
      this.myViewAllVectorE.Name = "myViewAllVectorE";
      this.myViewAllVectorE.Size = new System.Drawing.Size(91, 17);
      this.myViewAllVectorE.TabIndex = 0;
      this.myViewAllVectorE.Text = "Enemy vector";
      this.myViewAllVectorE.UseVisualStyleBackColor = true;
      // 
      // myViewAllVectorA
      // 
      this.myViewAllVectorA.AutoSize = true;
      this.myViewAllVectorA.Location = new System.Drawing.Point(6, 65);
      this.myViewAllVectorA.Name = "myViewAllVectorA";
      this.myViewAllVectorA.Size = new System.Drawing.Size(105, 17);
      this.myViewAllVectorA.TabIndex = 0;
      this.myViewAllVectorA.Text = "Alignment vector";
      this.myViewAllVectorA.UseVisualStyleBackColor = true;
      // 
      // myViewAllVectorC
      // 
      this.myViewAllVectorC.AutoSize = true;
      this.myViewAllVectorC.Location = new System.Drawing.Point(6, 42);
      this.myViewAllVectorC.Name = "myViewAllVectorC";
      this.myViewAllVectorC.Size = new System.Drawing.Size(103, 17);
      this.myViewAllVectorC.TabIndex = 0;
      this.myViewAllVectorC.Text = "Cohesion vector";
      this.myViewAllVectorC.UseVisualStyleBackColor = true;
      // 
      // myViewAllVectorS
      // 
      this.myViewAllVectorS.AutoSize = true;
      this.myViewAllVectorS.Location = new System.Drawing.Point(6, 19);
      this.myViewAllVectorS.Name = "myViewAllVectorS";
      this.myViewAllVectorS.Size = new System.Drawing.Size(110, 17);
      this.myViewAllVectorS.TabIndex = 0;
      this.myViewAllVectorS.Text = "Separation vector";
      this.myViewAllVectorS.UseVisualStyleBackColor = true;
      // 
      // groupBox1
      // 
      groupBox1.Controls.Add(this.myBotsVelocity);
      groupBox1.Controls.Add(this.label6);
      groupBox1.Controls.Add(this.label3);
      groupBox1.Controls.Add(this.label2);
      groupBox1.Controls.Add(this.myBoidType);
      groupBox1.Controls.Add(this.myBoidInitVelocity);
      groupBox1.Controls.Add(label5);
      groupBox1.Controls.Add(this.myBoidInitPlacement);
      groupBox1.Location = new System.Drawing.Point(2, 29);
      groupBox1.Name = "groupBox1";
      groupBox1.Size = new System.Drawing.Size(239, 138);
      groupBox1.TabIndex = 4;
      groupBox1.TabStop = false;
      groupBox1.Text = "Boids initial placement";
      // 
      // myBotsVelocity
      // 
      this.myBotsVelocity.AutoSize = false;
      this.myBotsVelocity.Cursor = System.Windows.Forms.Cursors.SizeWE;
      this.myBotsVelocity.LargeChange = 10;
      this.myBotsVelocity.Location = new System.Drawing.Point(69, 108);
      this.myBotsVelocity.Maximum = 1000;
      this.myBotsVelocity.Name = "myBotsVelocity";
      this.myBotsVelocity.Size = new System.Drawing.Size(164, 24);
      this.myBotsVelocity.TabIndex = 7;
      this.myBotsVelocity.TickFrequency = 5;
      this.myBotsVelocity.TickStyle = System.Windows.Forms.TickStyle.None;
      this.myBotsVelocity.Value = 50;
      this.myBotsVelocity.ValueChanged += new System.EventHandler(this.OnBotsVelocity_Changed);
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(12, 84);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(51, 13);
      this.label6.TabIndex = 2;
      this.label6.Text = "Boid type";
      this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(14, 57);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(49, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Direction";
      this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(6, 30);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(57, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "Placement";
      this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
      // 
      // myBoidType
      // 
      this.myBoidType.FormattingEnabled = true;
      this.myBoidType.Location = new System.Drawing.Point(69, 81);
      this.myBoidType.Name = "myBoidType";
      this.myBoidType.Size = new System.Drawing.Size(164, 21);
      this.myBoidType.TabIndex = 3;
      this.myBoidType.SelectedIndexChanged += new System.EventHandler(this.OnPlacement_Changed);
      // 
      // myBoidInitVelocity
      // 
      this.myBoidInitVelocity.FormattingEnabled = true;
      this.myBoidInitVelocity.Location = new System.Drawing.Point(69, 54);
      this.myBoidInitVelocity.Name = "myBoidInitVelocity";
      this.myBoidInitVelocity.Size = new System.Drawing.Size(164, 21);
      this.myBoidInitVelocity.TabIndex = 3;
      this.myBoidInitVelocity.SelectedIndexChanged += new System.EventHandler(this.OnPlacement_Changed);
      // 
      // label5
      // 
      label5.AutoSize = true;
      label5.Location = new System.Drawing.Point(19, 110);
      label5.Name = "label5";
      label5.Size = new System.Drawing.Size(44, 13);
      label5.TabIndex = 1;
      label5.Text = "Velocity";
      label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
      // 
      // myBoidInitPlacement
      // 
      this.myBoidInitPlacement.FormattingEnabled = true;
      this.myBoidInitPlacement.Location = new System.Drawing.Point(69, 27);
      this.myBoidInitPlacement.Name = "myBoidInitPlacement";
      this.myBoidInitPlacement.Size = new System.Drawing.Size(164, 21);
      this.myBoidInitPlacement.TabIndex = 3;
      this.myBoidInitPlacement.SelectedIndexChanged += new System.EventHandler(this.OnPlacement_Changed);
      // 
      // myBoidsCount
      // 
      this.myBoidsCount.Location = new System.Drawing.Point(79, 3);
      this.myBoidsCount.Maximum = new decimal(new int[] {
            50000,
            0,
            0,
            0});
      this.myBoidsCount.Name = "myBoidsCount";
      this.myBoidsCount.Size = new System.Drawing.Size(121, 20);
      this.myBoidsCount.TabIndex = 0;
      this.myBoidsCount.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
      this.myBoidsCount.ValueChanged += new System.EventHandler(this.OnBotsCnt_Changed);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(45, 5);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(28, 13);
      this.label4.TabIndex = 1;
      this.label4.Text = "Bots";
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1018, 642);
      this.Controls.Add(splitContainer1);
      this.Name = "Form1";
      this.Text = "Form1";
      splitContainer1.Panel1.ResumeLayout(false);
      splitContainer1.Panel2.ResumeLayout(false);
      splitContainer1.Panel2.PerformLayout();
      splitContainer1.ResumeLayout(false);
      groupBox2.ResumeLayout(false);
      groupBox4.ResumeLayout(false);
      groupBox4.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.myCurrentBot)).EndInit();
      groupBox3.ResumeLayout(false);
      groupBox3.PerformLayout();
      groupBox1.ResumeLayout(false);
      groupBox1.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.myBotsVelocity)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.myBoidsCount)).EndInit();
      this.ResumeLayout(false);

    }

    #endregion

    private ctlRenderArea.RenderArea myRenderArea;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.NumericUpDown myBoidsCount;
    private System.Windows.Forms.ComboBox myBoidInitPlacement;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.ComboBox myBoidInitVelocity;
    private System.Windows.Forms.CheckBox myViewAllVectorA;
    private System.Windows.Forms.CheckBox myViewAllVectorC;
    private System.Windows.Forms.CheckBox myViewAllVectorS;
    private System.Windows.Forms.CheckBox myViewBoidVectorR;
    private System.Windows.Forms.CheckBox myViewBoidRadiusS;
    private System.Windows.Forms.CheckBox myViewBoidVectorA;
    private System.Windows.Forms.CheckBox myViewBoidVectorC;
    private System.Windows.Forms.CheckBox myViewBoidVectorS;
    private System.Windows.Forms.CheckBox myViewAllVectorR;
    private System.Windows.Forms.CheckBox myViewAllRadiusS;
    private System.Windows.Forms.NumericUpDown myCurrentBot;
    private System.Windows.Forms.CheckBox myPaused;
    private System.Windows.Forms.CheckBox myViewBoidEnable;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.ComboBox myBoidType;
    private System.Windows.Forms.TrackBar myBotsVelocity;
    private System.Windows.Forms.Label myViewBoidColor;
    private System.Windows.Forms.CheckBox myViewAllVectorE;
    private System.Windows.Forms.CheckBox myViewBoidVectorE;
  }
}

