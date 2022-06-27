namespace WindowsApplication1
{
    partial class FrmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
          this.stsStrip = new System.Windows.Forms.StatusStrip();
          this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
          this.grpPreview = new System.Windows.Forms.GroupBox();
          this.pnlPreview = new System.Windows.Forms.Panel();
          this.grpHeightMap = new System.Windows.Forms.GroupBox();
          this.grpGetTerrainHeight = new System.Windows.Forms.GroupBox();
          this.lblTerrainHeight = new System.Windows.Forms.Label();
          this.label3 = new System.Windows.Forms.Label();
          this.btnGetTerrainHeight = new System.Windows.Forms.Button();
          this.txtX = new System.Windows.Forms.TextBox();
          this.txtY = new System.Windows.Forms.TextBox();
          this.label2 = new System.Windows.Forms.Label();
          this.label1 = new System.Windows.Forms.Label();
          this.lblMaxHeight = new System.Windows.Forms.Label();
          this.lblMaxHeightLbl = new System.Windows.Forms.Label();
          this.lblMinHeight = new System.Windows.Forms.Label();
          this.lblMinHeightLbl = new System.Windows.Forms.Label();
          this.lblTerrainSize = new System.Windows.Forms.Label();
          this.lblTerrainSizeLbl = new System.Windows.Forms.Label();
          this.lblFileName = new System.Windows.Forms.Label();
          this.lblFileNameLbl = new System.Windows.Forms.Label();
          this.btnPreview = new System.Windows.Forms.Button();
          this.btnLoad = new System.Windows.Forms.Button();
          this.grpNavMesh = new System.Windows.Forms.GroupBox();
          this.groupBox6 = new System.Windows.Forms.GroupBox();
          this.button4 = new System.Windows.Forms.Button();
          this.button2 = new System.Windows.Forms.Button();
          this.groupBox5 = new System.Windows.Forms.GroupBox();
          this.btnCurrentMeshPreview = new System.Windows.Forms.Button();
          this.groupBox4 = new System.Windows.Forms.GroupBox();
          this.lblStartID = new System.Windows.Forms.Label();
          this.lblStartIDLbl = new System.Windows.Forms.Label();
          this.btnDropUnreachableArea = new System.Windows.Forms.Button();
          this.groupBox3 = new System.Windows.Forms.GroupBox();
          this.lblNeighbourCount = new System.Windows.Forms.Label();
          this.label7 = new System.Windows.Forms.Label();
          this.btnMarkSelectedAreaNeighbour = new System.Windows.Forms.Button();
          this.lblSelectedID = new System.Windows.Forms.Label();
          this.label5 = new System.Windows.Forms.Label();
          this.btnSetNeighbour = new System.Windows.Forms.Button();
          this.groupBox2 = new System.Windows.Forms.GroupBox();
          this.trcMaxTerrainSlope = new System.Windows.Forms.TrackBar();
          this.btnDropTriangleBySlope = new System.Windows.Forms.Button();
          this.groupBox1 = new System.Windows.Forms.GroupBox();
          this.trcTriangleCount = new System.Windows.Forms.TrackBar();
          this.btnBuildCommonMesh = new System.Windows.Forms.Button();
          this.ofdLoad = new System.Windows.Forms.OpenFileDialog();
          this.stsStrip.SuspendLayout();
          this.grpPreview.SuspendLayout();
          this.grpHeightMap.SuspendLayout();
          this.grpGetTerrainHeight.SuspendLayout();
          this.grpNavMesh.SuspendLayout();
          this.groupBox6.SuspendLayout();
          this.groupBox5.SuspendLayout();
          this.groupBox4.SuspendLayout();
          this.groupBox3.SuspendLayout();
          this.groupBox2.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.trcMaxTerrainSlope)).BeginInit();
          this.groupBox1.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.trcTriangleCount)).BeginInit();
          this.SuspendLayout();
          // 
          // stsStrip
          // 
          this.stsStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
          this.stsStrip.Location = new System.Drawing.Point(0, 569);
          this.stsStrip.Name = "stsStrip";
          this.stsStrip.Size = new System.Drawing.Size(1083, 22);
          this.stsStrip.TabIndex = 0;
          this.stsStrip.Text = "statusStrip1";
          // 
          // toolStripStatusLabel1
          // 
          this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
          this.toolStripStatusLabel1.Size = new System.Drawing.Size(93, 17);
          this.toolStripStatusLabel1.Text = "Test Application";
          // 
          // grpPreview
          // 
          this.grpPreview.Controls.Add(this.pnlPreview);
          this.grpPreview.Location = new System.Drawing.Point(21, 20);
          this.grpPreview.Name = "grpPreview";
          this.grpPreview.Size = new System.Drawing.Size(531, 542);
          this.grpPreview.TabIndex = 1;
          this.grpPreview.TabStop = false;
          this.grpPreview.Text = "Preview";
          // 
          // pnlPreview
          // 
          this.pnlPreview.BackColor = System.Drawing.Color.White;
          this.pnlPreview.Location = new System.Drawing.Point(9, 18);
          this.pnlPreview.Name = "pnlPreview";
          this.pnlPreview.Size = new System.Drawing.Size(512, 512);
          this.pnlPreview.TabIndex = 0;
          this.pnlPreview.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlPreview_Paint);
          this.pnlPreview.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pnlPreview_MouseClick);
          // 
          // grpHeightMap
          // 
          this.grpHeightMap.Controls.Add(this.grpGetTerrainHeight);
          this.grpHeightMap.Controls.Add(this.lblMaxHeight);
          this.grpHeightMap.Controls.Add(this.lblMaxHeightLbl);
          this.grpHeightMap.Controls.Add(this.lblMinHeight);
          this.grpHeightMap.Controls.Add(this.lblMinHeightLbl);
          this.grpHeightMap.Controls.Add(this.lblTerrainSize);
          this.grpHeightMap.Controls.Add(this.lblTerrainSizeLbl);
          this.grpHeightMap.Controls.Add(this.lblFileName);
          this.grpHeightMap.Controls.Add(this.lblFileNameLbl);
          this.grpHeightMap.Controls.Add(this.btnPreview);
          this.grpHeightMap.Controls.Add(this.btnLoad);
          this.grpHeightMap.Location = new System.Drawing.Point(558, 20);
          this.grpHeightMap.Name = "grpHeightMap";
          this.grpHeightMap.Size = new System.Drawing.Size(256, 218);
          this.grpHeightMap.TabIndex = 2;
          this.grpHeightMap.TabStop = false;
          this.grpHeightMap.Text = "HeightMap";
          // 
          // grpGetTerrainHeight
          // 
          this.grpGetTerrainHeight.Controls.Add(this.lblTerrainHeight);
          this.grpGetTerrainHeight.Controls.Add(this.label3);
          this.grpGetTerrainHeight.Controls.Add(this.btnGetTerrainHeight);
          this.grpGetTerrainHeight.Controls.Add(this.txtX);
          this.grpGetTerrainHeight.Controls.Add(this.txtY);
          this.grpGetTerrainHeight.Controls.Add(this.label2);
          this.grpGetTerrainHeight.Controls.Add(this.label1);
          this.grpGetTerrainHeight.Location = new System.Drawing.Point(10, 142);
          this.grpGetTerrainHeight.Name = "grpGetTerrainHeight";
          this.grpGetTerrainHeight.Size = new System.Drawing.Size(237, 69);
          this.grpGetTerrainHeight.TabIndex = 11;
          this.grpGetTerrainHeight.TabStop = false;
          this.grpGetTerrainHeight.Text = "Get Terrain Height";
          // 
          // lblTerrainHeight
          // 
          this.lblTerrainHeight.AutoSize = true;
          this.lblTerrainHeight.Location = new System.Drawing.Point(173, 44);
          this.lblTerrainHeight.Name = "lblTerrainHeight";
          this.lblTerrainHeight.Size = new System.Drawing.Size(27, 13);
          this.lblTerrainHeight.TabIndex = 13;
          this.lblTerrainHeight.Text = "N/A";
          // 
          // label3
          // 
          this.label3.AutoSize = true;
          this.label3.Location = new System.Drawing.Point(90, 44);
          this.label3.Name = "label3";
          this.label3.Size = new System.Drawing.Size(77, 13);
          this.label3.TabIndex = 12;
          this.label3.Text = "Terrain Height:";
          // 
          // btnGetTerrainHeight
          // 
          this.btnGetTerrainHeight.Location = new System.Drawing.Point(90, 16);
          this.btnGetTerrainHeight.Name = "btnGetTerrainHeight";
          this.btnGetTerrainHeight.Size = new System.Drawing.Size(141, 23);
          this.btnGetTerrainHeight.TabIndex = 11;
          this.btnGetTerrainHeight.Text = "Get";
          this.btnGetTerrainHeight.UseVisualStyleBackColor = true;
          this.btnGetTerrainHeight.Click += new System.EventHandler(this.btnGetTerrainHeight_Click);
          // 
          // txtX
          // 
          this.txtX.Location = new System.Drawing.Point(23, 19);
          this.txtX.Name = "txtX";
          this.txtX.Size = new System.Drawing.Size(42, 20);
          this.txtX.TabIndex = 9;
          // 
          // txtY
          // 
          this.txtY.Location = new System.Drawing.Point(23, 41);
          this.txtY.Name = "txtY";
          this.txtY.Size = new System.Drawing.Size(42, 20);
          this.txtY.TabIndex = 10;
          // 
          // label2
          // 
          this.label2.AutoSize = true;
          this.label2.Location = new System.Drawing.Point(8, 44);
          this.label2.Name = "label2";
          this.label2.Size = new System.Drawing.Size(17, 13);
          this.label2.TabIndex = 7;
          this.label2.Text = "Y:";
          // 
          // label1
          // 
          this.label1.AutoSize = true;
          this.label1.Location = new System.Drawing.Point(8, 22);
          this.label1.Name = "label1";
          this.label1.Size = new System.Drawing.Size(17, 13);
          this.label1.TabIndex = 7;
          this.label1.Text = "X:";
          // 
          // lblMaxHeight
          // 
          this.lblMaxHeight.AutoSize = true;
          this.lblMaxHeight.Location = new System.Drawing.Point(68, 98);
          this.lblMaxHeight.Name = "lblMaxHeight";
          this.lblMaxHeight.Size = new System.Drawing.Size(27, 13);
          this.lblMaxHeight.TabIndex = 8;
          this.lblMaxHeight.Text = "N/A";
          // 
          // lblMaxHeightLbl
          // 
          this.lblMaxHeightLbl.AutoSize = true;
          this.lblMaxHeightLbl.Location = new System.Drawing.Point(7, 98);
          this.lblMaxHeightLbl.Name = "lblMaxHeightLbl";
          this.lblMaxHeightLbl.Size = new System.Drawing.Size(67, 13);
          this.lblMaxHeightLbl.TabIndex = 7;
          this.lblMaxHeightLbl.Text = "Max Height: ";
          // 
          // lblMinHeight
          // 
          this.lblMinHeight.AutoSize = true;
          this.lblMinHeight.Location = new System.Drawing.Point(68, 81);
          this.lblMinHeight.Name = "lblMinHeight";
          this.lblMinHeight.Size = new System.Drawing.Size(27, 13);
          this.lblMinHeight.TabIndex = 6;
          this.lblMinHeight.Text = "N/A";
          // 
          // lblMinHeightLbl
          // 
          this.lblMinHeightLbl.AutoSize = true;
          this.lblMinHeightLbl.Location = new System.Drawing.Point(7, 81);
          this.lblMinHeightLbl.Name = "lblMinHeightLbl";
          this.lblMinHeightLbl.Size = new System.Drawing.Size(64, 13);
          this.lblMinHeightLbl.TabIndex = 5;
          this.lblMinHeightLbl.Text = "Min Height: ";
          // 
          // lblTerrainSize
          // 
          this.lblTerrainSize.AutoSize = true;
          this.lblTerrainSize.Location = new System.Drawing.Point(68, 65);
          this.lblTerrainSize.Name = "lblTerrainSize";
          this.lblTerrainSize.Size = new System.Drawing.Size(27, 13);
          this.lblTerrainSize.TabIndex = 4;
          this.lblTerrainSize.Text = "N/A";
          // 
          // lblTerrainSizeLbl
          // 
          this.lblTerrainSizeLbl.AutoSize = true;
          this.lblTerrainSizeLbl.Location = new System.Drawing.Point(7, 65);
          this.lblTerrainSizeLbl.Name = "lblTerrainSizeLbl";
          this.lblTerrainSizeLbl.Size = new System.Drawing.Size(69, 13);
          this.lblTerrainSizeLbl.TabIndex = 3;
          this.lblTerrainSizeLbl.Text = "Terrain Size: ";
          // 
          // lblFileName
          // 
          this.lblFileName.AutoSize = true;
          this.lblFileName.Location = new System.Drawing.Point(68, 49);
          this.lblFileName.Name = "lblFileName";
          this.lblFileName.Size = new System.Drawing.Size(27, 13);
          this.lblFileName.TabIndex = 2;
          this.lblFileName.Text = "N/A";
          // 
          // lblFileNameLbl
          // 
          this.lblFileNameLbl.AutoSize = true;
          this.lblFileNameLbl.Location = new System.Drawing.Point(7, 49);
          this.lblFileNameLbl.Name = "lblFileNameLbl";
          this.lblFileNameLbl.Size = new System.Drawing.Size(60, 13);
          this.lblFileNameLbl.TabIndex = 1;
          this.lblFileNameLbl.Text = "File Name: ";
          // 
          // btnPreview
          // 
          this.btnPreview.Location = new System.Drawing.Point(6, 114);
          this.btnPreview.Name = "btnPreview";
          this.btnPreview.Size = new System.Drawing.Size(244, 23);
          this.btnPreview.TabIndex = 0;
          this.btnPreview.Text = "Preview";
          this.btnPreview.UseVisualStyleBackColor = true;
          this.btnPreview.Click += new System.EventHandler(this.btnPreview_Click);
          // 
          // btnLoad
          // 
          this.btnLoad.Location = new System.Drawing.Point(6, 19);
          this.btnLoad.Name = "btnLoad";
          this.btnLoad.Size = new System.Drawing.Size(244, 23);
          this.btnLoad.TabIndex = 0;
          this.btnLoad.Text = "Load...";
          this.btnLoad.UseVisualStyleBackColor = true;
          this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
          // 
          // grpNavMesh
          // 
          this.grpNavMesh.Controls.Add(this.groupBox6);
          this.grpNavMesh.Controls.Add(this.groupBox5);
          this.grpNavMesh.Controls.Add(this.groupBox4);
          this.grpNavMesh.Controls.Add(this.groupBox3);
          this.grpNavMesh.Controls.Add(this.groupBox2);
          this.grpNavMesh.Controls.Add(this.groupBox1);
          this.grpNavMesh.Location = new System.Drawing.Point(820, 20);
          this.grpNavMesh.Name = "grpNavMesh";
          this.grpNavMesh.Size = new System.Drawing.Size(256, 542);
          this.grpNavMesh.TabIndex = 3;
          this.grpNavMesh.TabStop = false;
          this.grpNavMesh.Text = "NavMesh";
          // 
          // groupBox6
          // 
          this.groupBox6.Controls.Add(this.button4);
          this.groupBox6.Controls.Add(this.button2);
          this.groupBox6.Enabled = false;
          this.groupBox6.Location = new System.Drawing.Point(10, 379);
          this.groupBox6.Name = "groupBox6";
          this.groupBox6.Size = new System.Drawing.Size(237, 88);
          this.groupBox6.TabIndex = 6;
          this.groupBox6.TabStop = false;
          this.groupBox6.Text = "Step 5";
          // 
          // button4
          // 
          this.button4.Location = new System.Drawing.Point(6, 20);
          this.button4.Name = "button4";
          this.button4.Size = new System.Drawing.Size(225, 25);
          this.button4.TabIndex = 2;
          this.button4.Text = "Make Convex Polygon";
          this.button4.UseVisualStyleBackColor = true;
          // 
          // button2
          // 
          this.button2.Location = new System.Drawing.Point(6, 52);
          this.button2.Name = "button2";
          this.button2.Size = new System.Drawing.Size(225, 25);
          this.button2.TabIndex = 1;
          this.button2.Text = "3 -> 2 Merging";
          this.button2.UseVisualStyleBackColor = true;
          // 
          // groupBox5
          // 
          this.groupBox5.Controls.Add(this.btnCurrentMeshPreview);
          this.groupBox5.Location = new System.Drawing.Point(13, 473);
          this.groupBox5.Name = "groupBox5";
          this.groupBox5.Size = new System.Drawing.Size(237, 57);
          this.groupBox5.TabIndex = 5;
          this.groupBox5.TabStop = false;
          this.groupBox5.Text = "Preview";
          // 
          // btnCurrentMeshPreview
          // 
          this.btnCurrentMeshPreview.Location = new System.Drawing.Point(6, 19);
          this.btnCurrentMeshPreview.Name = "btnCurrentMeshPreview";
          this.btnCurrentMeshPreview.Size = new System.Drawing.Size(225, 25);
          this.btnCurrentMeshPreview.TabIndex = 1;
          this.btnCurrentMeshPreview.Text = "Current Navigation Mesh Preview";
          this.btnCurrentMeshPreview.UseVisualStyleBackColor = true;
          this.btnCurrentMeshPreview.Click += new System.EventHandler(this.btnCurrentMeshPreview_Click);
          // 
          // groupBox4
          // 
          this.groupBox4.Controls.Add(this.lblStartID);
          this.groupBox4.Controls.Add(this.lblStartIDLbl);
          this.groupBox4.Controls.Add(this.btnDropUnreachableArea);
          this.groupBox4.Location = new System.Drawing.Point(10, 302);
          this.groupBox4.Name = "groupBox4";
          this.groupBox4.Size = new System.Drawing.Size(237, 71);
          this.groupBox4.TabIndex = 4;
          this.groupBox4.TabStop = false;
          this.groupBox4.Text = "Step 4";
          // 
          // lblStartID
          // 
          this.lblStartID.AutoSize = true;
          this.lblStartID.Location = new System.Drawing.Point(78, 18);
          this.lblStartID.Name = "lblStartID";
          this.lblStartID.Size = new System.Drawing.Size(27, 13);
          this.lblStartID.TabIndex = 6;
          this.lblStartID.Text = "N/A";
          // 
          // lblStartIDLbl
          // 
          this.lblStartIDLbl.AutoSize = true;
          this.lblStartIDLbl.Location = new System.Drawing.Point(6, 18);
          this.lblStartIDLbl.Name = "lblStartIDLbl";
          this.lblStartIDLbl.Size = new System.Drawing.Size(74, 13);
          this.lblStartIDLbl.TabIndex = 5;
          this.lblStartIDLbl.Text = "Start Area ID: ";
          // 
          // btnDropUnreachableArea
          // 
          this.btnDropUnreachableArea.Location = new System.Drawing.Point(6, 36);
          this.btnDropUnreachableArea.Name = "btnDropUnreachableArea";
          this.btnDropUnreachableArea.Size = new System.Drawing.Size(225, 25);
          this.btnDropUnreachableArea.TabIndex = 1;
          this.btnDropUnreachableArea.Text = "Drop Unreachable Areas";
          this.btnDropUnreachableArea.UseVisualStyleBackColor = true;
          this.btnDropUnreachableArea.Click += new System.EventHandler(this.btnDropUnreachableArea_Click);
          // 
          // groupBox3
          // 
          this.groupBox3.Controls.Add(this.lblNeighbourCount);
          this.groupBox3.Controls.Add(this.label7);
          this.groupBox3.Controls.Add(this.btnMarkSelectedAreaNeighbour);
          this.groupBox3.Controls.Add(this.lblSelectedID);
          this.groupBox3.Controls.Add(this.label5);
          this.groupBox3.Controls.Add(this.btnSetNeighbour);
          this.groupBox3.Location = new System.Drawing.Point(10, 95);
          this.groupBox3.Name = "groupBox3";
          this.groupBox3.Size = new System.Drawing.Size(237, 123);
          this.groupBox3.TabIndex = 3;
          this.groupBox3.TabStop = false;
          this.groupBox3.Text = "Step 2";
          // 
          // lblNeighbourCount
          // 
          this.lblNeighbourCount.AutoSize = true;
          this.lblNeighbourCount.Location = new System.Drawing.Point(97, 71);
          this.lblNeighbourCount.Name = "lblNeighbourCount";
          this.lblNeighbourCount.Size = new System.Drawing.Size(27, 13);
          this.lblNeighbourCount.TabIndex = 7;
          this.lblNeighbourCount.Text = "N/A";
          // 
          // label7
          // 
          this.label7.AutoSize = true;
          this.label7.Location = new System.Drawing.Point(6, 71);
          this.label7.Name = "label7";
          this.label7.Size = new System.Drawing.Size(93, 13);
          this.label7.TabIndex = 6;
          this.label7.Text = "Neighbour Count: ";
          // 
          // btnMarkSelectedAreaNeighbour
          // 
          this.btnMarkSelectedAreaNeighbour.Location = new System.Drawing.Point(6, 90);
          this.btnMarkSelectedAreaNeighbour.Name = "btnMarkSelectedAreaNeighbour";
          this.btnMarkSelectedAreaNeighbour.Size = new System.Drawing.Size(225, 24);
          this.btnMarkSelectedAreaNeighbour.TabIndex = 5;
          this.btnMarkSelectedAreaNeighbour.Text = "Mark Selected Area Neighbours";
          this.btnMarkSelectedAreaNeighbour.UseVisualStyleBackColor = true;
          this.btnMarkSelectedAreaNeighbour.Click += new System.EventHandler(this.btnMarkSelectedAreaNeighbour_Click);
          // 
          // lblSelectedID
          // 
          this.lblSelectedID.AutoSize = true;
          this.lblSelectedID.Location = new System.Drawing.Point(97, 56);
          this.lblSelectedID.Name = "lblSelectedID";
          this.lblSelectedID.Size = new System.Drawing.Size(27, 13);
          this.lblSelectedID.TabIndex = 4;
          this.lblSelectedID.Text = "N/A";
          // 
          // label5
          // 
          this.label5.AutoSize = true;
          this.label5.Location = new System.Drawing.Point(6, 56);
          this.label5.Name = "label5";
          this.label5.Size = new System.Drawing.Size(94, 13);
          this.label5.TabIndex = 3;
          this.label5.Text = "Selected Area ID: ";
          // 
          // btnSetNeighbour
          // 
          this.btnSetNeighbour.Location = new System.Drawing.Point(6, 16);
          this.btnSetNeighbour.Name = "btnSetNeighbour";
          this.btnSetNeighbour.Size = new System.Drawing.Size(225, 24);
          this.btnSetNeighbour.TabIndex = 1;
          this.btnSetNeighbour.Text = "Set Area Neighbours";
          this.btnSetNeighbour.UseVisualStyleBackColor = true;
          this.btnSetNeighbour.Click += new System.EventHandler(this.btnSetNeighbour_Click);
          // 
          // groupBox2
          // 
          this.groupBox2.Controls.Add(this.trcMaxTerrainSlope);
          this.groupBox2.Controls.Add(this.btnDropTriangleBySlope);
          this.groupBox2.Location = new System.Drawing.Point(10, 225);
          this.groupBox2.Name = "groupBox2";
          this.groupBox2.Size = new System.Drawing.Size(237, 71);
          this.groupBox2.TabIndex = 2;
          this.groupBox2.TabStop = false;
          this.groupBox2.Text = "Step 3";
          // 
          // trcMaxTerrainSlope
          // 
          this.trcMaxTerrainSlope.LargeChange = 15;
          this.trcMaxTerrainSlope.Location = new System.Drawing.Point(11, 23);
          this.trcMaxTerrainSlope.Maximum = 45;
          this.trcMaxTerrainSlope.Name = "trcMaxTerrainSlope";
          this.trcMaxTerrainSlope.Size = new System.Drawing.Size(116, 45);
          this.trcMaxTerrainSlope.TabIndex = 2;
          this.trcMaxTerrainSlope.TickFrequency = 3;
          this.trcMaxTerrainSlope.Value = 3;
          // 
          // btnDropTriangleBySlope
          // 
          this.btnDropTriangleBySlope.Location = new System.Drawing.Point(133, 15);
          this.btnDropTriangleBySlope.Name = "btnDropTriangleBySlope";
          this.btnDropTriangleBySlope.Size = new System.Drawing.Size(98, 41);
          this.btnDropTriangleBySlope.TabIndex = 1;
          this.btnDropTriangleBySlope.Text = "Drop Area by Terrain Slope";
          this.btnDropTriangleBySlope.UseVisualStyleBackColor = true;
          this.btnDropTriangleBySlope.Click += new System.EventHandler(this.btnDropTriangleBySlope_Click);
          // 
          // groupBox1
          // 
          this.groupBox1.Controls.Add(this.trcTriangleCount);
          this.groupBox1.Controls.Add(this.btnBuildCommonMesh);
          this.groupBox1.Location = new System.Drawing.Point(10, 19);
          this.groupBox1.Name = "groupBox1";
          this.groupBox1.Size = new System.Drawing.Size(237, 70);
          this.groupBox1.TabIndex = 2;
          this.groupBox1.TabStop = false;
          this.groupBox1.Text = "Step 1";
          // 
          // trcTriangleCount
          // 
          this.trcTriangleCount.LargeChange = 2;
          this.trcTriangleCount.Location = new System.Drawing.Point(11, 23);
          this.trcTriangleCount.Maximum = 7;
          this.trcTriangleCount.Name = "trcTriangleCount";
          this.trcTriangleCount.Size = new System.Drawing.Size(116, 45);
          this.trcTriangleCount.TabIndex = 2;
          this.trcTriangleCount.Value = 3;
          // 
          // btnBuildCommonMesh
          // 
          this.btnBuildCommonMesh.Location = new System.Drawing.Point(133, 15);
          this.btnBuildCommonMesh.Name = "btnBuildCommonMesh";
          this.btnBuildCommonMesh.Size = new System.Drawing.Size(98, 41);
          this.btnBuildCommonMesh.TabIndex = 1;
          this.btnBuildCommonMesh.Text = "Build Common Mesh";
          this.btnBuildCommonMesh.UseVisualStyleBackColor = true;
          this.btnBuildCommonMesh.Click += new System.EventHandler(this.btnBuildCommonMesh_Click);
          // 
          // ofdLoad
          // 
          this.ofdLoad.FileName = "openFileDialog1";
          // 
          // FrmMain
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(1083, 591);
          this.Controls.Add(this.grpNavMesh);
          this.Controls.Add(this.grpHeightMap);
          this.Controls.Add(this.grpPreview);
          this.Controls.Add(this.stsStrip);
          this.Name = "FrmMain";
          this.Text = "NavMesh SIwGK";
          this.Load += new System.EventHandler(this.FrmMain_Load);
          this.stsStrip.ResumeLayout(false);
          this.stsStrip.PerformLayout();
          this.grpPreview.ResumeLayout(false);
          this.grpHeightMap.ResumeLayout(false);
          this.grpHeightMap.PerformLayout();
          this.grpGetTerrainHeight.ResumeLayout(false);
          this.grpGetTerrainHeight.PerformLayout();
          this.grpNavMesh.ResumeLayout(false);
          this.groupBox6.ResumeLayout(false);
          this.groupBox5.ResumeLayout(false);
          this.groupBox4.ResumeLayout(false);
          this.groupBox4.PerformLayout();
          this.groupBox3.ResumeLayout(false);
          this.groupBox3.PerformLayout();
          this.groupBox2.ResumeLayout(false);
          this.groupBox2.PerformLayout();
          ((System.ComponentModel.ISupportInitialize)(this.trcMaxTerrainSlope)).EndInit();
          this.groupBox1.ResumeLayout(false);
          this.groupBox1.PerformLayout();
          ((System.ComponentModel.ISupportInitialize)(this.trcTriangleCount)).EndInit();
          this.ResumeLayout(false);
          this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip stsStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.GroupBox grpPreview;
        private System.Windows.Forms.GroupBox grpHeightMap;
        private System.Windows.Forms.GroupBox grpNavMesh;
      private System.Windows.Forms.Button btnLoad;
      private System.Windows.Forms.OpenFileDialog ofdLoad;
      private System.Windows.Forms.Label lblFileNameLbl;
      private System.Windows.Forms.Label lblFileName;
      private System.Windows.Forms.Label lblTerrainSize;
      private System.Windows.Forms.Label lblTerrainSizeLbl;
      private System.Windows.Forms.Label lblMaxHeight;
      private System.Windows.Forms.Label lblMaxHeightLbl;
      private System.Windows.Forms.Label lblMinHeight;
      private System.Windows.Forms.Label lblMinHeightLbl;
      private System.Windows.Forms.Button btnPreview;
      private System.Windows.Forms.GroupBox grpGetTerrainHeight;
      private System.Windows.Forms.TextBox txtX;
      private System.Windows.Forms.TextBox txtY;
      private System.Windows.Forms.Label label3;
      private System.Windows.Forms.Button btnGetTerrainHeight;
      private System.Windows.Forms.Label label2;
      private System.Windows.Forms.Label label1;
      private System.Windows.Forms.Label lblTerrainHeight;
      private System.Windows.Forms.Panel pnlPreview;
      private System.Windows.Forms.GroupBox groupBox1;
      private System.Windows.Forms.Button btnBuildCommonMesh;
      private System.Windows.Forms.TrackBar trcTriangleCount;
      private System.Windows.Forms.GroupBox groupBox2;
      private System.Windows.Forms.TrackBar trcMaxTerrainSlope;
      private System.Windows.Forms.Button btnDropTriangleBySlope;
      private System.Windows.Forms.GroupBox groupBox3;
      private System.Windows.Forms.Button btnMarkSelectedAreaNeighbour;
      private System.Windows.Forms.Label lblSelectedID;
      private System.Windows.Forms.Label label5;
      private System.Windows.Forms.Button btnSetNeighbour;
      private System.Windows.Forms.GroupBox groupBox4;
      private System.Windows.Forms.Label lblStartID;
      private System.Windows.Forms.Label lblStartIDLbl;
      private System.Windows.Forms.Button btnDropUnreachableArea;
      private System.Windows.Forms.Label lblNeighbourCount;
      private System.Windows.Forms.Label label7;
      private System.Windows.Forms.GroupBox groupBox6;
      private System.Windows.Forms.Button button4;
      private System.Windows.Forms.Button button2;
      private System.Windows.Forms.GroupBox groupBox5;
      private System.Windows.Forms.Button btnCurrentMeshPreview;
    }
}

