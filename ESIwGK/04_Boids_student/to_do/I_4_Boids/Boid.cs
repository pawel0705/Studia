using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using I_4_Boids.Math;
using System.Collections;

namespace I_4_Boids
{
    namespace Boids
    {
        public class Boid
        {
            /// Pozycja bojdy w przestrzeni
            protected vec3 myPos;
            /// Orientacja bojdy w przestrzeni
            protected vec3 myDir;
            protected vec3 myDirN;
            /// Wektor równoleg³y do p³aszczyzny ruchu bojdy
            protected vec3 myPlane;
            private bool myIsSelected = false;

            public bool Selected
            {
                get { return myIsSelected; }
                set { myIsSelected = value; }
            }


            public bool Intersect(vec3 point)
            {
                vec3[] points = Shape();
                vec3[] N = new vec3[3];

                N[0] = vec3.cross(points[0] - points[1], Consts.VersorZ);
                N[1] = vec3.cross(points[1] - points[2], Consts.VersorZ);
                N[2] = vec3.cross(points[2] - points[0], Consts.VersorZ);

                if (vec3.dot(N[0], points[0] - point) < 0
                  && vec3.dot(N[1], points[1] - point) < 0
                  && vec3.dot(N[2], points[2] - point) < 0)
                    return true;

                return false;
            }


            public Boid(vec3 pos, vec3 dir, vec3 plane)
            {
                myPos = pos;
                myDir = dir;
                myDirN = myDir.normalized();
                myPlane = plane;
            }

            public void FindFlock()
            {
                BoidColor = Flock.nextFlockPen();
                doDetectYourFlock();
            }
            #region Boid's logic
            private double mySeparationDistance = 50;

            public double SeparationDistance
            {
                get { return mySeparationDistance; }
                set { mySeparationDistance = value; }
            }


            protected vec3 myTmpSeparation;
            protected vec3 myTmpAlignment;
            protected vec3 myTmpEnemy;
            protected vec3 myTmpCohesion;
            System.Random myRand = new Random(System.Environment.TickCount);
            private readonly double DeviationAngle = Math.Consts.TWO_PI / 2.0; // 2*alpha odchylenia
            private readonly double MaxVelocityChange = 50.0;

            public Random DirectionDeviator
            {
                set
                {
                    myRand = value;
                }
                get
                {
                    return myRand;
                }
            }

            protected bool myQueryPen = false;

            protected virtual void doAccumulate(ref vec3 f)
            {
                f += myTmpCohesion = doCohesion();
                f += myTmpAlignment = doAlignment();
                f += myTmpSeparation = doSeparation();
                f += doMove();
            }

            protected Boid getNearestBoidInSight()
            {
                double d, dres = Double.MaxValue;
                Boid res = null;

                foreach (Boid b in Flock)
                    if (b as Object != this as Object && (d = vec3.distance(myPos, b.Position)) < Radius)
                        if (d < dres)
                        {
                            res = b;
                            dres = d;
                        }

                return res;
            }

            protected bool myIsInFlock = false;
            protected void doUpdate(double delta, double time)
            {
                vec3 f = new vec3();

                doAccumulate(ref f);
                f *= delta;

                // TODO_1: trzeba coœ zrobiæ z tym wektorem f...  (0.5pkt)
                // Najlepiej w jakiœ sposób powi¹zaæ z pozycj¹ i kierunkiem ;]
                // Podpowiedzi: Przypisanie wartoœci length wektora zmienia jego wielkoœæ nie zmieniaj¹c kierunku (np. f.length=5;)
                //              Funkcja F.Clamp(v,min,max) - zwraca wartoœæ v obciêt¹ do przedzia³u <min,max>
                //              f powinien ograniczyæ siê do MaxVelocityChange, mDir do Velocity

                var newfLength = F.Clamp(f.length, 0.0f, this.MaxVelocityChange);
                f.length = newfLength;
                this.myDir += f;

                var newDirLenght = F.Clamp(this.myDir.length, 0.0f, this.Velocity);
                this.myDir.length = newDirLenght;
                this.myPos += this.myDir;

                doDetectYourFlock();
            }

            protected virtual vec3 doMove()
            {
                vec3 res = new vec3(myDir);

                // 60% szans na brak zaburzenia w kierunku poruszania
                if (myRand.NextDouble() < 0.6)
                    return res;

                double d = (myRand.NextDouble() - 0.5) * DeviationAngle;
                res.rotZ(d);
                return res;
            }


            #region TODO_2: Implementacja regu³ podstawowych (3pkt)
            protected virtual vec3 doCohesion()
            {
                vec3 res = new vec3();

                var boids = this.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {
                    var isMe = ReferenceEquals(this, boid);

                    if (isMe == true)
                    {
                        continue;
                    }

                    if (vec3.distance(boid.myPos, this.myPos) < this.Radius)
                    {
                        res += boid.myPos;
                        i++;
                    }
                }

                if (i > 0)
                {
                    res = ((res / (double)i) - this.myPos) / 5.0f;
                }

                return res;
            }
            protected virtual vec3 doAlignment()
            {
                vec3 result = new vec3();

                var boids = this.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {
                    var isMe = ReferenceEquals(this, boid);

                    if (isMe == true)
                    {
                        continue;
                    }

                    if (vec3.distance(boid.Position, this.myPos) < this.Radius)
                    {
                        result += boid.Direction;
                        i++;
                    }
                }

                if (i > 0)
                {
                    result = result / (double)i;
                }

                return result;
            }
            protected virtual vec3 doSeparation()
            {
                vec3 res = new vec3();

                var boids = this.Flock.Boids;

                foreach (var boid in boids)
                {
                    var isMe = ReferenceEquals(this, boid);

                    if (isMe == true)
                    {
                        continue;
                    }

                    if (vec3.distance(boid.Position, this.myPos) < this.SeparationDistance)
                    {
                        res += this.myPos - boid.Position;
                    }
                }

                return res;
            }
            #endregion


            private double myVelocity;
            public virtual double Velocity
            {
                get { return myVelocity; }
                set { myVelocity = value; }
            }


            private double myRadius = 125;
            public double Radius
            {
                get { return myRadius; }
                set { myRadius = value; }
            }

            private Flock myFlock;
            private bool myIsAlive = true;

            public bool IsAlive
            {
                get
                {
                    return myIsAlive;
                }
            }
            public void Kill()
            {
                myIsAlive = false;
            }

            public Flock Flock
            {
                get { return myFlock; }
                set
                {
                    myFlock = value;
                }
            }
            #endregion

            #region IUpdatable
            public virtual void Update(double delta, double time)
            {
                doUpdate(delta, time);
            }
            #endregion

            #region ITransformable
            public virtual vec3 Position
            {
                get
                {
                    return myPos;
                }
                set
                {
                    myPos = value;
                }
            }

            public virtual vec3 Direction
            {
                get
                {
                    return myDir;
                }
                set
                {
                    myDir = value;
                }
            }
            #endregion

            #region IRenderable
            const int trA = 6;
            const int trH = 18;
            readonly int bbW = System.Math.Max(trA, trH);
            public vec3[] Shape()
            {
                vec3[] res = new vec3[3];
                vec3 h = myDir.normalized();
                vec3 a = vec3.cross(h, Consts.VersorZ);

                h *= trH;
                a *= trA;
                res[0] = myPos - a;
                res[1] = myPos + a;
                res[2] = myPos + h;
                return res;
            }
            public vec3[] BBox()
            {
                vec3 delta = new vec3(bbW, bbW, 0);
                return new vec3[] { myPos - delta, myPos + delta };
            }

            public virtual void Draw(Graphics g, Bitmap b)
            {
                if (IsAlive)
                {
                    //trójk¹t
                    vec3[] points = Shape();
                    DrawLine(g, points[0], points[1], myTriangleColor);
                    DrawLine(g, points[1], points[2], myTriangleColor);
                    DrawLine(g, points[2], points[0], myTriangleColor);
                }
                else
                {
                    // krzy¿yk
                    vec3 offX = new vec3(2, 0, 0);
                    vec3 offY = new vec3(0, 2, 0);
                    DrawLine(g, myPos - offX, myPos + offX, myTriangleColor);
                    DrawLine(g, myPos - offY, myPos + offY, myTriangleColor);
                }


                int x = (int)System.Math.Round(myPos.x);
                int y = (int)System.Math.Round(myPos.y);
                doDrawVectors(g, b, x, y);
            }

            protected virtual void doDrawVectors(Graphics g, Bitmap b, int x, int y)
            {
                if (Selected)
                {
                    DrawVector(g, b, x, y, myTmpSeparation, myDrawVecSeparationColor);
                    DrawVector(g, b, x, y, myTmpCohesion, myDrawVecCohesionColor);
                    DrawVector(g, b, x, y, myTmpAlignment, myDrawVecAlignmentColor);
                    DrawSphere(g, b, x, y, mySeparationDistance, myDrawSeparationZoneColor);
                    DrawVector(g, b, x, y, myTmpEnemy, myDrawVecEnemyColor);
                    DrawSphere(g, b, x, y, myRadius, myDrawRadiusColor);
                    return;
                }

                if (myDrawVecSeparation)
                    DrawVector(g, b, x, y, myTmpSeparation, myDrawVecSeparationColor);
                if (myDrawVecCohesion)
                    DrawVector(g, b, x, y, myTmpCohesion, myDrawVecCohesionColor);
                if (myDrawVecAlignment)
                    DrawVector(g, b, x, y, myTmpAlignment, myDrawVecAlignmentColor);
                if (myDrawSeparationZone)
                    DrawSphere(g, b, x, y, mySeparationDistance, myDrawSeparationZoneColor);
                if (myDrawVecEnemy)
                    DrawVector(g, b, x, y, myTmpEnemy, myDrawVecEnemyColor);
                if (myDrawRadius)
                    DrawSphere(g, b, x, y, myRadius, myDrawRadiusColor);
            }

            protected void DrawLine(Graphics g, vec3 from, vec3 to, Pen p)
            {
                int x = (int)System.Math.Floor(from.x + 0.5);
                int y = (int)System.Math.Floor(from.y + 0.5);
                int xx = (int)System.Math.Floor(to.x + 0.5);
                int yy = (int)System.Math.Floor(to.y + 0.5);

                g.DrawLine(p, x, y, xx, yy);
            }

            protected void DrawSphere(Graphics g, Bitmap b, int x, int y, double r, Pen p)
            {
                int rr = (int)System.Math.Round(r);
                g.DrawEllipse(p, x - rr, y - rr, rr << 1, rr << 1);
            }

            protected void DrawVector(Graphics g, Bitmap b, int x, int y, vec3 v, int length, Pen p)
            {
                v.normalize();
                v *= length;
                int xx = x + (int)v.x;
                int yy = y + (int)v.y;

                g.DrawLine(p, x, y, xx, yy);
            }

            protected void DrawVector(Graphics g, Bitmap b, int x, int y, vec3 v, Pen p)
            {
                if (v == null)
                    return;
                int xx = x + (int)v.x;
                int yy = y + (int)v.y;

                g.DrawLine(p, x, y, xx, yy);
            }

            /// Wektor wynikowy - ró¿owy
            private Pen myDrawSeparationZoneColor = Pens.Black;
            private bool myDrawSeparationZone = true;
            /// Wektor wynikowy - zielony
            private Pen myDrawVecSeparationColor = Pens.Green;
            private bool myDrawVecSeparation = false;
            /// Wektor wynikowy - niebieski
            private Pen myDrawVecAlignmentColor = Pens.Blue;
            private bool myDrawVecAlignment = false;
            /// Wektor wynikowy - czerwony
            private Pen myDrawVecCohesionColor = Pens.Red;
            private bool myDrawVecCohesion = false;

            private Pen myDrawVecEnemyColor = Pens.DarkOrange;
            private bool myDrawVecEnemy = false;

            private bool myDrawRadius = false;
            private Pen myDrawRadiusColor = Pens.Silver;

            private Pen myTriangleColor;

            public Pen BoidColor
            {
                get { return myTriangleColor; }
                set { myTriangleColor = value; }
            }

            public Pen SeparationSphereColor
            {
                get { return myDrawSeparationZoneColor; }
                set { myDrawSeparationZoneColor = value; }
            }

            public Pen SeparationVectorColor
            {
                get { return myDrawVecSeparationColor; }
                set { myDrawVecSeparationColor = value; }
            }

            public Pen AlignmentVectorColor
            {
                get { return myDrawVecAlignmentColor; }
                set { myDrawVecAlignmentColor = value; }
            }
            public Pen EnemyVectorColor
            {
                get { return myDrawVecEnemyColor; }
                set { myDrawVecEnemyColor = value; }
            }

            public Pen CohesionVectorColor
            {
                get { return myDrawVecCohesionColor; }
                set { myDrawVecCohesionColor = value; }
            }

            public Pen DrawRadiusColor
            {
                get { return myDrawRadiusColor; }
                set { myDrawRadiusColor = value; }
            }

            public bool DrawRadius
            {
                get { return myDrawRadius; }
                set { myDrawRadius = value; }
            }

            public bool Sphere
            {
                get { return myDrawRadius; }
                set { myDrawRadius = value; }
            }

            public bool SeparationSphere
            {
                get { return myDrawSeparationZone; }
                set { myDrawSeparationZone = value; }
            }

            public bool SeparationVector
            {
                get { return myDrawVecSeparation; }
                set { myDrawVecSeparation = value; }
            }

            public bool AligmentVector
            {
                get { return myDrawVecAlignment; }
                set { myDrawVecAlignment = value; }
            }
            public bool EnemyVector
            {
                get { return myDrawVecEnemy; }
                set { myDrawVecEnemy = value; }
            }
            public bool CohesionVector
            {
                get { return myDrawVecCohesion; }
                set { myDrawVecCohesion = value; }
            }
            #endregion


            protected virtual void doDetectYourFlock()
            {
                Boid b = getNearestBoidInSight();
                if (b == null || b.BoidColor == null)
                {
                    if (myIsInFlock)
                        BoidColor = Flock.nextFlockPen();

                    myIsInFlock = false;
                }
                else
                {
                    myIsInFlock = true;
                    BoidColor = b.BoidColor;
                }
            }
        }

        public class FlockBoid : Boid
        {
            public FlockBoid(vec3 pos, vec3 dir, vec3 pl)
              : base(pos, dir, pl)
            {
            }

            protected override void doDetectYourFlock()
            {
                // Kolorowanie stad
                Boid b = getNearestBoidInSight();
                if (b == null)
                {
                    // Nie mam kompanów, ale chwilê temu mia³em-> wygeneruj nowy kolor stada
                    if (myIsInFlock)
                        BoidColor = Flock.nextFlockPen();

                    myIsInFlock = false;
                }
                else
                {
                    if (BoidColor == null)
                    {
                        BoidColor = b.BoidColor;
                        myIsInFlock = true;
                    }
                    else
                    {
                        if (!myIsInFlock && b.BoidColor != null)
                        {
                            BoidColor = b.BoidColor;
                            myIsInFlock = true;
                        }
                    }
                }
            }

            protected override void doAccumulate(ref vec3 f)
            {
                base.doAccumulate(ref f);

                f += myTmpEnemy = doAvoidOtherFlocks();
            }

            protected vec3 doAvoidOtherFlocks()
            {
                vec3 res = new vec3();

                // TODO_3_1: Implementacja regu³y wielu stad. Stada identyfikujemy po kolorze. (0.5pkt)

                var boids = base.Flock.Boids;

                foreach (var boid in boids)
                {
                    if (!(ReferenceEquals(boid.BoidColor, base.BoidColor) || (vec3.distance(boid.Position, this.myPos) >= this.Radius)))
                    {
                        res += base.myPos - boid.Position;
                    }
                }

                return res;
            }
        }

        public class InverseSepBoid : Boid
        {
            public InverseSepBoid(vec3 a, vec3 b, vec3 c)
              : base(a, b, c) { }

            protected override vec3 doSeparation()
            {
                vec3 res = new vec3();

                // TODO_3_2: Inna implementacja regu³y separacji. (0.5pkt) Osobniki znajduj¹ce siê blisko oddalaj¹ siê o wiêcej, ni¿ osobniki znajduj¹ce siê daleko

                var boids = base.Flock.Boids;

                foreach (var boid in boids)
                {
                    var isMe = ReferenceEquals(this, boid);

                    if (isMe == true)
                    {
                        continue;
                    }

                    if (vec3.distance(boid.Position, base.myPos) < base.SeparationDistance)
                    {
                        var tmpPos = this.Position - boid.Position;
                        tmpPos.length = base.SeparationDistance - tmpPos.length;
                        res += tmpPos;
                    }
                }

                return res;
            }
        }

        public class GlobalCohesion : InverseSepBoid
        {
            public GlobalCohesion(vec3 a, vec3 b, vec3 c)
              : base(a, b, c) { }

            protected override vec3 doCohesion()
            {
                vec3 pos = new vec3();

                // TODO_3_3: Globalna regu³a spójnoœci (0.5pkt)

                var boids = base.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {
                    pos += boid.Position;

                    i++;
                }

                if (i == 0)
                {
                    return pos;
                }

                pos = ((pos / (double)i) - this.Position) / 5.0;

                return pos;
            }
        }


        public class HPFBoid : Boid
        {
            private Pen myAvoidFlockType;
            private Pen myHuntFlockType;

            private double myLife;
            private double myTimeWithoutFood = 0;

            private static Random Deviation = new Random(System.Environment.TickCount);
            private const double MaxHungerTimeStdDev = 25;
            private readonly double MaximumHungerTime = 50 + 25 * (Deviation.NextDouble() * 2 - 1);

            public override double Velocity
            {
                get
                {
                    return base.Velocity * myLife;
                }
                set
                {
                    if (myHuntFlockType == null)
                        base.Velocity = value * 0.9;
                    else if (myAvoidFlockType == null)
                        base.Velocity = value * 1.1;
                    else
                        base.Velocity = value;
                }
            }

            public HPFBoid(vec3 pos, vec3 dir, vec3 pl, Pen avoid, Pen hunt)
              : base(pos, dir, pl)
            {
                myAvoidFlockType = avoid;
                myHuntFlockType = hunt;
                myLife = 1;
            }

            protected override void doDetectYourFlock()
            {
                // Tak, pusta implementacja, poniewa¿ nie zmieniamy swojego gatunku...
                // Jak ktoœ jest much¹, to nie stanie siê jastrzêbiem.
            }

            public override void Update(double delta, double time)
            {
                if (IsAlive)
                {
                    // TODO_4_3: trochê inny update. Do odkomentowania.

                    myTimeWithoutFood += delta;

                    base.Update(delta, time);

                    if (!DidSurvive())
                        Kill();
                }
            }

            protected override void doAccumulate(ref vec3 f)
            {
                base.doAccumulate(ref f);

                f += myTmpHuntVec = doHunt();
                f += myTmpSurviveVec = doSurvive();
            }

            #region TODO_4_4: Niestety wymagamy innych regu³ ni¿ te podstawowe (1pkt)
            protected override vec3 doSeparation()
            {
                vec3 res = new vec3();

                var boids = base.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {
                    if ((!ReferenceEquals(boid, this) && !ReferenceEquals(boid.BoidColor, this.myHuntFlockType)) && (vec3.distance(boid.Position, this.Position) < base.SeparationDistance))
                    {
                        var tmpPos = this.Position - boid.Position;
                        tmpPos.length = base.SeparationDistance - tmpPos.length;
                        res += tmpPos;
                        i++;
                    }
                }

                if (i == 0)
                {
                    return res;
                }

                res = res / (double)i;

                return res;
            }

            protected override vec3 doCohesion()
            {
                vec3 res = new vec3();

                var boids = base.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {

                    if ((!ReferenceEquals(this, boid) && ReferenceEquals(boid.BoidColor, base.BoidColor)) && (vec3.distance(boid.Position, base.myPos) < base.Radius))
                    {
                        res += boid.Position;
                        i++;
                    }
                }

                if (i > 0)
                {
                    res = ((res / (double)i) - base.myPos) / 5.0;
                }

                return res;
            }
            protected override vec3 doAlignment()
            {
                vec3 result = new vec3();

                var boids = base.Flock.Boids;

                var i = 0;

                foreach (var boid in boids)
                {
                    if ((!ReferenceEquals(boid, this) && ReferenceEquals(boid.BoidColor, base.BoidColor)) && (vec3.distance(boid.Position, base.myPos) < base.Radius))
                    {
                        result += boid.Direction;
                        i++;
                    }
                }

                if (i > 1)
                {
                    result /= (double)i;
                }

                result.length = 5.0;

                return result;
            }
            #endregion

            private vec3 myTmpHuntVec = new vec3();
            private vec3 myTmpSurviveVec = new vec3();

            #region TODO_4_5: Najzabawniejsza czêœæ - regu³y prze¿ycia (2pkt)
            protected virtual vec3 doHunt()
            {
                // najblizej z nas znajdujemy
                vec3 res = new vec3();

                var boids = base.Flock.Boids;

                var minPos = double.MaxValue;

                foreach (var boid in boids)
                {
                    if (ReferenceEquals(boid.BoidColor, this.myHuntFlockType))
                    {
                        var tmpPos = 0.0;
                        var pos = boid.Position - this.Position;
                        tmpPos = pos.length;

                        if (tmpPos < base.Radius && tmpPos < minPos)
                        {
                            res = pos;
                            minPos = tmpPos;
                        }
                    }
                }

                return res;
            }

            protected virtual vec3 doSurvive()
            {
                vec3 res = new vec3();

                var boids = base.Flock.Boids;

                foreach (var boid in boids)
                {
                    if (ReferenceEquals(boid.BoidColor, this.myAvoidFlockType) && (vec3.distance(boid.Position, this.Position) < base.Radius))
                    {
                        res += this.Position - boid.Position;
                    }
                }

                return res;
            }
            #endregion

            protected override void doDrawVectors(Graphics g, Bitmap b, int x, int y)
            {
                base.doDrawVectors(g, b, x, y);
                if (!Selected)
                    return;

                DrawVector(g, b, x, y, myTmpHuntVec, Pens.Pink);
                DrawVector(g, b, x, y, myTmpSurviveVec, Pens.LightGreen);
            }

            private bool CheckShapeIntersect(vec3[] a, vec3[] b)
            {
                if (F.SegmentIntersection(a[0], a[1], b[0], b[1]) != null ||
                  F.SegmentIntersection(a[1], a[2], b[0], b[1]) != null ||
                  F.SegmentIntersection(a[2], a[0], b[0], b[1]) != null ||

                  F.SegmentIntersection(a[0], a[1], b[1], b[2]) != null ||
                  F.SegmentIntersection(a[1], a[2], b[1], b[2]) != null ||
                  F.SegmentIntersection(a[2], a[0], b[1], b[2]) != null ||

                  F.SegmentIntersection(a[0], a[1], b[2], b[0]) != null ||
                  F.SegmentIntersection(a[1], a[2], b[2], b[0]) != null ||
                  F.SegmentIntersection(a[2], a[0], b[2], b[0]) != null)
                    return true;

                return false;
            }

            private bool Rect2dIntersect(vec3[] a1, vec3[] a2)
            {
                const int left = 0;
                const int top = 1;
                const int right = 2;
                const int bottom = 3;
                double[] a = { System.Math.Min(a1[0].x, a1[1].x), System.Math.Min(a1[0].y, a1[1].y), System.Math.Max(a1[0].x, a1[1].x), System.Math.Max(a1[0].y, a1[1].y) };
                double[] b = { System.Math.Min(a2[0].x, a2[1].x), System.Math.Min(a2[0].y, a2[1].y), System.Math.Max(a2[0].x, a2[1].x), System.Math.Max(a2[0].y, a2[1].y) };

                return !(a[right] < b[left] ||
                          a[left] > b[right] ||
                          a[top] > b[bottom] ||
                          a[bottom] < b[top]);
            }

            protected bool DidSurvive()
            {
                vec3[] shape = Shape();
                foreach (Boid boid in Flock)
                {
                    if (boid == this || boid.BoidColor == BoidColor)
                        continue;

                    if (!Rect2dIntersect(boid.BBox(), BBox()))
                        continue;

                    if (boid.BoidColor == myAvoidFlockType)
                    {
                        if (CheckShapeIntersect(boid.Shape(), shape))
                            return false;
                    }
                    else
                    {
                        if (CheckShapeIntersect(boid.Shape(), shape))
                            myTimeWithoutFood = 0;
                    }
                }


                // TODO_4_6: Jeœli jeszcze mnie nie zjedli, to mog³em umrzeæ z g³odu, a s³abszy ruszam siê wolniej... (1pkt)
                // Podpowiedzi: Nale¿y u¿yæ: myLife ; MaximumHungerTime ; myTimeWithoutFood;
                // return ...

                if (this.myTimeWithoutFood < this.MaximumHungerTime)
                {
                    return true;
                }

                this.myLife = 1 - (this.myTimeWithoutFood / this.MaximumHungerTime);

                if (this.myLife <= 0)
                {
                    return false;
                }

                return false;
            }
        }


    }
}
