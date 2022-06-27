using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace menu
{
    public partial class Form1 : Form, IAkcje
    {
        RootClass AktualnyStan;
        public Form1()
        {
            InitializeComponent();
            AktualnyStan = new GlowneMenu(this); 
        }
        // Akcje
        public void WejscieDoGlownegoMenu()
        {
            label1.Text = "Menu";
            button1.Text = "Start";
            button2.Text = "Ustawienia";
            button1.Visible = true;
            button2.Visible = true;

        }
        public void WejscieDoStart()
        {
            label1.Text = "Start!";
            button1.Visible = false;
            button2.Visible = false;

        }
        public void Wyjscie() 
        {
            Close();
        }
        public void WejscieDoOpcje() 
        {
            label1.Text = "Opcje";
            button1.Text = "Standardowe";
            button2.Text = "Zaawansowane";
            button1.Visible = true;
            button2.Visible = true;
        }
        public void WejscieDoZaawansowane() 
        {
            label1.Text = "Zaawansowane";
            button1.Visible = false;
            button2.Visible = false;
        }
        public void WejscieDoStandardowe()
        {
            label1.Text = "Standardowe";
            button1.Visible = false;
            button2.Visible = false;
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //TODO Wywolanie zdarzenia 1
            //np AktualnyStan = AktualnyStan.Zdarzenie1();
            AktualnyStan = AktualnyStan.Zdarzenie1();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //TODO Wywolanie zdarzenia 2
            AktualnyStan = AktualnyStan.Zdarzenie2();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //TODO Wywolanie zdarzenia 3
            AktualnyStan = AktualnyStan.Zdarzenie3();
        }
    }
}