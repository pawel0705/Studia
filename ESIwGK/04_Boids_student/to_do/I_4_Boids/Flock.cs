using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Drawing;

namespace I_4_Boids {
  public class Flock: IEnumerable {
    internal static int pen = 0;
    internal static Pen[] pens = {
Pens.Black,
Pens.Blue,
Pens.BlueViolet,
Pens.Brown,
Pens.BurlyWood,
Pens.CadetBlue,
Pens.Chocolate,
Pens.DarkBlue,
Pens.DarkCyan,
Pens.DarkGoldenrod,
Pens.DarkGray,
Pens.DarkGreen,
Pens.DarkKhaki,
Pens.DarkMagenta,
Pens.DarkOliveGreen,
Pens.DarkOrange,
Pens.DarkOrchid,
Pens.DarkRed,
Pens.DarkSalmon,
Pens.DarkSeaGreen,
Pens.DarkSlateBlue,
Pens.DarkSlateGray,
Pens.DarkTurquoise,
Pens.DarkViolet,
Pens.DeepPink,
Pens.DeepSkyBlue,
Pens.DimGray,
Pens.ForestGreen,
Pens.Green,
Pens.GreenYellow,
Pens.HotPink,
Pens.IndianRed,
Pens.Indigo,
Pens.LawnGreen,
Pens.Lime,
Pens.LimeGreen,
Pens.Magenta,
Pens.Maroon,
Pens.MediumAquamarine,
Pens.MediumBlue,
Pens.MediumOrchid,
Pens.MediumPurple,
Pens.MediumSeaGreen,
Pens.MediumSlateBlue,
Pens.MediumSpringGreen,
Pens.MediumTurquoise,
Pens.MediumVioletRed,
Pens.MidnightBlue,
Pens.Navy,
Pens.Orange,
Pens.OrangeRed,
Pens.Orchid,
Pens.Pink,
Pens.Plum,
Pens.Purple,
Pens.Red,
Pens.SandyBrown,
Pens.SeaGreen,
Pens.SkyBlue,
Pens.SlateBlue,
Pens.SlateGray,
Pens.SpringGreen,
Pens.SteelBlue,
Pens.Tan,
Pens.Teal,
Pens.Thistle,
Pens.Tomato,
Pens.Turquoise,
Pens.Violet,
Pens.Yellow,
Pens.YellowGreen
    };


    private class FlockEnumerator : IEnumerator {
      private int myIndex = -1;
      private Flock myFlock;

      public FlockEnumerator(Flock f) {
        myFlock = f;
      }

      public object Current {
        get {
          return myFlock.Boids[myIndex];
        }
      }

      public bool MoveNext() {
        while (++myIndex < myFlock.Boids.Length && !myFlock.Boids[myIndex].IsAlive)
          ; // yeap, empty loop

        return myIndex < myFlock.Boids.Length;
      }

      public void Reset() {
        myIndex = -1;
      }
    }



    public IEnumerator GetEnumerator() {
      return new FlockEnumerator(this);
    }

    public static Pen nextFlockPen() {
      Pen res = pens[pen++];

      if (pen >= pens.Length)
        pen = 0;

      return res;
    }


    private Boids.Boid[] myBoids;

    public Boids.Boid this[ decimal idx ] {
      get {
        return myBoids[(int)idx];
      }
    }
    public Boids.Boid this[int idx] {
      get {
        return myBoids[idx];
      }
    }

    public delegate Math.vec3 MakeBoidDirection(Math.vec3 pos, Math.vec3 c);
    public delegate void PlaceBoid(out Boids.Boid boid, int w, int h, int idx, int count, MakeBoid factory, MakeBoidDirection dir);
    public delegate Boids.Boid MakeBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen avoidFlock, Pen huntFlock);
    
    public void Reset(decimal count, double v, int w, int h, PlaceBoid placer, MakeBoid factory, MakeBoidDirection dir) {
      int cnt = (int)count;
      System.Random r = new Random(System.Environment.TickCount);

      myBoids = new Boids.Boid[cnt];
      for (int i = 0; i < cnt; ++i) {
        placer(out myBoids[i], w, h, i, cnt, factory, dir);

        myBoids[i].Flock = this;
        myBoids[i].Velocity = v;
        myBoids[i].DirectionDeviator = new Random(r.Next());
      }
    }

    public Boids.Boid[] Boids {
      get {
        return myBoids;
      }
    }
  }
}
