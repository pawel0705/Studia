using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Alarm
{
    public partial class Form1 : Form, IAkcje
    {
        RootClass aktualnyStan;
        public Form1()
        {
            InitializeComponent();
            aktualnyStan = new Off(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Wywo³anie zdarzenia

            aktualnyStan = aktualnyStan.WlaczAlarm();

        }
        private void button2_Click(object sender, EventArgs e)
        {
            //Wywo³anie zdarzenia

            aktualnyStan = aktualnyStan.WylaczAlarm();
        }
        #region IAkcje Members

        public void ZgasLampe()
        {
            label1.Text = "Lampa alarmowa wy³¹czona";

        }
        public void ZapalLampe()
        {
            label1.Text = "Lampa alarmowa w³¹czona";
        }

        #endregion

        private void timer1_Tick(object sender, EventArgs e)
        {
            //Wywo³anie zdarzenia czasowego
            aktualnyStan.Tick();
        }


    }
}