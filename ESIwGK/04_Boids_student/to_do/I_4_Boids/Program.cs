using System;
using System.Collections.Generic;
using System.Windows.Forms;
using GAILabsClasses;

namespace I_4_Boids {
  static class Program {
    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main() {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);

      Form1 form = new Form1();
      Clock clk = new Clock();
      FPSCounter counter = new FPSCounter();

      form.Show();
      clk.Reset();
      counter.Frequency = clk.Frequency;
      counter.RefreshRate = clk.Frequency / 2;

      double delta, time = 0f;
      long tick;


      while (form.Created) {
        tick = clk.TicksDelta();
        delta = (double)tick / clk.Frequency;
        time += delta;


        form.Update(delta, time);
        Application.DoEvents();

        counter.tick(tick);
        form.Text = counter.ToString();
      }
    }
  }
}