using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Winda
{
    public partial class Form1 : Form , IAkcje
    {
        RootClass aktualnyStan;
        public Form1()
        {
            InitializeComponent();
            aktualnyStan = new Dol(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //TODO Wywo�anie zdarzenia wci�ni�cie przycisku
            aktualnyStan = aktualnyStan.WcisnieciePrzycisku();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            //TODO Wywo�anie zdarzenia dojechanie do pietra
            aktualnyStan = aktualnyStan.DojechanieDoPietra();
        }
        #region IAkcje Members

        public void DotarcieNaGore()
        {
            label1.Text = "Winda stoi na g�rze";
        }

        public void DotarcieNaDol()
        {
            label1.Text = "Winda stoi na dole";
        }

        public void JazdaNaGore()
        {
            label1.Text = "Winda jedzie na g�r�";
        }

        public void JazdaNaDol()
        {
            label1.Text = "Winda jedzie w d�";
        }

        #endregion


    }
}