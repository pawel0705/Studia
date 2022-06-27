using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using I_4_Boids.Math;
using System.Collections;


namespace I_4_Boids
{
    public partial class Form1 : Form
    {
        Flock myFlock = new Flock();
        Bitmap myCanvas = new Bitmap(800, 600, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
        Placement myPlacers = new Placement();
        BoidsFactory myFactory = new BoidsFactory();
        InitialDirection myDirectors = new InitialDirection();


        bool myBlockSelectEvent = true;
        public Bitmap Canvas
        {
            get { return myCanvas; }
        }

        public Form1()
        {
            InitializeComponent();

            foreach (string s in myPlacers)
                myBoidInitPlacement.Items.Add(s);

            foreach (string s in myDirectors)
                myBoidInitVelocity.Items.Add(s);

            foreach (string s in myFactory)
                myBoidType.Items.Add(s);
            myBoidInitPlacement.SelectedIndex = 0;
            myBoidInitVelocity.SelectedIndex = 0;
            myBoidType.SelectedIndex = 0;
            myBlockSelectEvent = false;

            RePlace();

            Graphics g = Graphics.FromImage(myCanvas);
            g.Clear(Color.White);
            g.DrawRectangle(new Pen(Color.Black, 1), 10, 10, myCanvas.Width - 20, myCanvas.Height - 20);
            g.Dispose();

            // TODO: a raczej hint :) Tutaj mo¿na wpisaæ ustawienia z jakimi aplikacja startuje (nie trzeba bêdzie tego
            // za ka¿dym razem klikaæ)
            myBoidsCount.Value = 30;
            myBoidType.SelectedItem = "HawkPigeonFlyBoid";
           myBoidInitPlacement.SelectedItem = "HawkPigeonFly";
        }


        private void RePlace()
        {
            myFlock.Reset(myBoidsCount.Value, CountVelocity(), myCanvas.Width, myCanvas.Height,
              myPlacers.placer((string)myBoidInitPlacement.SelectedItem),
              myFactory.maker((string)myBoidType.SelectedItem),
              myDirectors.maker((string)myBoidInitVelocity.SelectedItem));
        }

        private double myTime = 0;
        public void Update(double delta, double time)
        {

            if (myFlock.Boids != null && !myPaused.Checked)
            {
                myTime += delta;
                foreach (Boids.Boid b in myFlock.Boids)
                {
                    b.Update(delta, myTime);

                    // zawijanie
                    if (b.Position.x < 0 || b.Position.x >= myCanvas.Width)
                        b.Position.x = Math.F.Wrap(b.Position.x, 0, myCanvas.Width - 1);
                    if (b.Position.y < 0 || b.Position.y >= myCanvas.Height)
                        b.Position.y = Math.F.Wrap(b.Position.y, 0, myCanvas.Height - 1);
                }
            }

            myRenderArea.Refresh();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.High;

            Graphics tmp = Graphics.FromImage(myCanvas);
            tmp.Clear(Color.White);
            if (myFlock.Boids != null)
                foreach (Boids.Boid b in myFlock.Boids)
                {
                    b.Selected = false;
                    b.AligmentVector = myViewAllVectorA.Checked;
                    b.SeparationVector = myViewAllVectorS.Checked;
                    b.CohesionVector = myViewAllVectorC.Checked;
                    b.SeparationSphere = myViewAllRadiusS.Checked;
                    b.Sphere = myViewAllVectorR.Checked;
                    b.EnemyVector = myViewAllVectorE.Checked;
                    b.Draw(tmp, myCanvas);
                }

            if (myViewBoidEnable.Checked)
            {
                myCurrentBot.Value = Math.F.Clamp(myCurrentBot.Value, 0, myBoidsCount.Value - 1);
                Boids.Boid curr = myFlock[myCurrentBot.Value];
                curr.Selected = true;
                curr.Draw(tmp, myCanvas);
                myViewBoidColor.Text = myFlock[myCurrentBot.Value].BoidColor.Color.Name;
            }
            tmp.Dispose();

            g.DrawImage(myCanvas, new Rectangle(0, 0, myRenderArea.Width, myRenderArea.Height), new Rectangle(0, 0, myCanvas.Width, myCanvas.Height), GraphicsUnit.Pixel);

            g.Dispose();
        }

        private void OnBotsCnt_Changed(object sender, EventArgs e)
        {
            RePlace();
        }

        private void OnCurrentBot_Changed(object sender, EventArgs e)
        {
            if (myCurrentBot.Value >= myBoidsCount.Value)
                myCurrentBot.Value = 0;
            else if (myCurrentBot.Value < 0)
                myCurrentBot.Value = myBoidsCount.Value - 1;
        }

        private void OnPlacement_Changed(object sender, EventArgs e)
        {
            if (!myBlockSelectEvent)
                RePlace();
        }

        private double CountVelocity()
        {
            return Math.F.Scale(myBotsVelocity.Value, myBotsVelocity.Minimum, myBotsVelocity.Maximum, 0.0, 10.0);
        }

        private void OnBotsVelocity_Changed(object sender, EventArgs e)
        {
            if (myFlock.Boids != null)
                foreach (Boids.Boid b in myFlock.Boids)
                    b.Velocity = CountVelocity();
        }

        private void OnClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                myViewBoidEnable.Checked = false;
                return;
            }

            // Przeliczanie na wspó³rzêdne œwiata
            vec3 pt = new vec3((double)e.X / myRenderArea.Width, (double)e.Y / myRenderArea.Height, 0);

            pt.x *= myCanvas.Width;
            pt.y *= myCanvas.Height;

            // Szukamy boidy
            if (myFlock.Boids == null)
                return;

            for (int i = 0; i < myFlock.Boids.Length; ++i)
                if (myFlock.Boids[i].Intersect(pt))
                {
                    myViewBoidEnable.Checked = true;
                    myCurrentBot.Value = i;
                    return;
                }

        }

        private void myRestart_Click(object sender, EventArgs e)
        {
            RePlace();
        }

    }

    public class Placement : IEnumerable
    {
        //foreach (MethodInfo b in typeof(Placement).GetMethods())
        //  if (b.IsStatic && b.Name.Substring(0,5) == "place")
        //    myBoidInitPlacement.Items.Add(b.Name.Substring(5));
        public Flock.PlaceBoid placer(string v)
        {
            return (Flock.PlaceBoid)Delegate.CreateDelegate(typeof(Flock.PlaceBoid), this, "place" + v);//typeof(Placement).GetMethod("place" + v));
        }

        private void placeCircular(out Boids.Boid boid, int w, int h, int idx, int count, Flock.MakeBoid factory, Flock.MakeBoidDirection dir)
        {
            double radius = 150.0;
            double angle = Math.Consts.TWO_PI / count;
            double current = (double)idx * angle;

            vec3 pos = new vec3(System.Math.Sin(current) * radius + (w >> 1), System.Math.Cos(current) * radius + (h >> 1), 0.0);
            vec3 c = new vec3(w >> 1, h >> 1, 0);
            vec3 pl = pos - c;
            pl.normalize();

            boid = factory(pos, dir(pos, c), pl, null, null);
            boid.BoidColor = Flock.nextFlockPen();
        }

        private void placeInMesh(out Boids.Boid boid, int w, int h, int idx, int count, Flock.MakeBoid factory, Flock.MakeBoidDirection dir)
        {
            double a = 150.0;
            int n = (int)System.Math.Ceiling(System.Math.Sqrt(count));
            double step = a / n;

            vec3 pos = new vec3(((w - a) / 2) + (idx % n) * step, ((h - a) / 2) + (idx / n) * step, 0.0);
            vec3 c = new vec3(w >> 1, h >> 1, 0.0);
            vec3 pl = new vec3(pos);
            pl -= c;
            pl.normalize();

            boid = factory(pos, dir(pos, c), pl, null, null);
            boid.BoidColor = Flock.nextFlockPen();
        }

        private System.Random myRand = new Random(System.Environment.TickCount);
        private void placeRandom(out Boids.Boid boid, int w, int h, int idx, int count, Flock.MakeBoid factory, Flock.MakeBoidDirection dir)
        {
            double a = 150.0;

            vec3 pos = new vec3(2 * a * (myRand.NextDouble() - 0.5), 2 * a * (myRand.NextDouble() - 0.5), 0.0);
            vec3 c = new vec3(w >> 1, h >> 1, 0.0);
            vec3 pl = new vec3(pos);
            pl -= c;
            pl.normalize();

            boid = factory(pos, dir(pos, c), pl, null, null);
            boid.BoidColor = Flock.nextFlockPen();
        }

        // TODO_4_1: Te kolory przydadz¹ siê przy tworzeniu stad w zadaniu 4.
        private readonly Pen FlyFlock = Pens.Black;
        private readonly Pen PigeonFlock = Pens.Green;
        private readonly Pen HawkFlock = Pens.Red;

        private void placeHawkPigeonFly(out Boids.Boid boid, int w, int h, int idx, int count, Flock.MakeBoid factory, Flock.MakeBoidDirection dir)
        {
            double radius = 100.0;
            int group_cnt = (int)System.Math.Ceiling(count / 3.0f);
            int gc_x, gc_y;

            // Obliczanie pozycji œrodków grup
            if (idx < group_cnt)
            {
                gc_y = gc_x = 150;
            }
            else if (idx < 2 * group_cnt)
            {
                gc_x = w - 150;
                gc_y = 150;
            }
            else
            {
                gc_x = w / 2;
                gc_y = h - 150;
            }

            // Rozmieszczenie osobnika w okrêgu w danej grupie.
            double angle = Math.Consts.TWO_PI / group_cnt;
            double current = (double)idx * angle;

            vec3 pos = new vec3(System.Math.Sin(current) * radius + gc_x, System.Math.Cos(current) * radius + gc_y, 0.0);
            vec3 c = new vec3(gc_x, gc_y, 0);
            vec3 pl = pos - c;
            pl.normalize();

            int mygroup = idx / group_cnt;

            // TODO_4_2: Tworzenie osobnika z odpowiednimi ustawieniami (skorzystaæ z fabryki) (1pkt)
            boid = null; //<- oczywiœcie wstawione tylko po to, ¿eby kod siê kompilowa³ po wyciêciu niektórych fragmentów
            switch (mygroup)
            {
                case 0:
                    boid = factory(pos, dir(pos, c), pl, this.PigeonFlock, null);
                    boid.BoidColor = this.FlyFlock;
                    break;
                case 1:
                    boid = factory(pos, dir(pos, c), pl, this.HawkFlock, this.FlyFlock);
                    boid.BoidColor = this.PigeonFlock;

                    break;
                default:
                    boid = factory(pos, dir(pos, c), pl, null, this.PigeonFlock);
                    boid.BoidColor = this.HawkFlock;

                    break;
            }
        }

        #region IEnumerable Members
        public IEnumerator GetEnumerator()
        {
            return new Enumer(this.GetType());
        }


        protected class Enumer : IEnumerator
        {
            private System.Collections.ArrayList myInfo = new ArrayList();
            private IEnumerator myEnum;


            private bool filter(MemberInfo m, object filterCriteria)
            {
                return m.Name.Substring(0, 5) == "place" && m.Name != "placer";
            }

            public Enumer(Type t)
            {
                foreach (MemberInfo i in t.FindMembers(MemberTypes.All, (BindingFlags)0xffffff, filter, null))
                    myInfo.Add(i.Name.Substring(5));

                myEnum = myInfo.GetEnumerator();
            }
            public object Current
            {
                get { return myEnum.Current; }
            }

            public bool MoveNext()
            {
                return myEnum.MoveNext();
            }

            public void Reset()
            {
                myEnum.Reset();
            }

        }
        #endregion
    }

    public class InitialDirection : IEnumerable
    {
        public Flock.MakeBoidDirection maker(string s)
        {
            return (Flock.MakeBoidDirection)Delegate.CreateDelegate(typeof(Flock.MakeBoidDirection), this, "make" + s);//typeof(BoidsFactory).GetMethod("make"+s));
        }

        private Math.vec3 makeOutsideCenter(Math.vec3 pos, Math.vec3 c)
        {
            vec3 res = pos - c;
            res.normalize();
            return res;
        }
        private Math.vec3 makeToCenter(Math.vec3 pos, Math.vec3 c)
        {
            vec3 res = c - pos;
            res.normalize();
            return res;
        }
        private Math.vec3 makeCircle(Math.vec3 pos, Math.vec3 c)
        {
            vec3 res = vec3.cross(pos - c, Math.Consts.VersorZ);
            res.normalize();
            return res;
        }

        #region IEnumerable Members
        public IEnumerator GetEnumerator()
        {
            return new Enumer(this.GetType());
        }


        protected class Enumer : IEnumerator
        {
            private System.Collections.ArrayList myInfo = new ArrayList();
            private IEnumerator myEnum;


            private bool filter(MemberInfo m, object filterCriteria)
            {
                return m.Name.Substring(0, 4) == "make" && m.Name != "maker";
            }

            public Enumer(Type t)
            {
                foreach (MemberInfo i in t.FindMembers(MemberTypes.All, (BindingFlags)0xffffff, filter, null))
                    myInfo.Add(i.Name.Substring(4));

                myEnum = myInfo.GetEnumerator();
            }
            public object Current
            {
                get { return myEnum.Current; }
            }

            public bool MoveNext()
            {
                return myEnum.MoveNext();
            }

            public void Reset()
            {
                myEnum.Reset();
            }

        }
        #endregion
    }

    public class BoidsFactory : IEnumerable
    {
        public Flock.MakeBoid maker(string s)
        {
            return (Flock.MakeBoid)Delegate.CreateDelegate(typeof(Flock.MakeBoid), this, "make" + s);//typeof(BoidsFactory).GetMethod("make"+s));
        }

        private Boids.Boid makeSimpleBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen dummy1, Pen dummy2)
        {
            return new Boids.Boid(pos, dir, pl);
        }
        private Boids.Boid makeManyFlocksBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen dummy1, Pen dummy2)
        {
            return new Boids.FlockBoid(pos, dir, pl);
        }
        private Boids.Boid makeBetterSeparationBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen dummy1, Pen dummy2)
        {
            return new Boids.InverseSepBoid(pos, dir, pl);
        }
        private Boids.Boid makeBetterSeparationAndFlockCenterBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen dummy1, Pen dummy2)
        {
            return new Boids.GlobalCohesion(pos, dir, pl);
        }
        private Boids.Boid makeHawkPigeonFlyBoid(Math.vec3 pos, Math.vec3 dir, Math.vec3 pl, Pen avoid, Pen hunt)
        {
            // Jeœli nie ma czego unikaæ, to jastrz¹b,
            // Jeœli nie ma na co polowaæ, to mucha
            // else go³¹b
            return new Boids.HPFBoid(pos, dir, pl, avoid, hunt);
        }
        #region IEnumerable Members
        public IEnumerator GetEnumerator()
        {
            return new Enumer(this.GetType());
        }


        protected class Enumer : IEnumerator
        {
            private System.Collections.ArrayList myInfo = new ArrayList();
            private IEnumerator myEnum;


            private bool filter(MemberInfo m, object filterCriteria)
            {
                return m.Name.Substring(0, 4) == "make" && m.Name != "maker";
            }

            public Enumer(Type t)
            {
                foreach (MemberInfo i in t.FindMembers(MemberTypes.All, (BindingFlags)0xffffff, filter, null))
                    myInfo.Add(i.Name.Substring(4));

                myEnum = myInfo.GetEnumerator();
            }
            public object Current
            {
                get { return myEnum.Current; }
            }

            public bool MoveNext()
            {
                return myEnum.MoveNext();
            }

            public void Reset()
            {
                myEnum.Reset();
            }

        }
        #endregion
    }
}