using System;
using System.Collections.Generic;
using System.Text;

namespace I_4_Boids {
  namespace Math {
    public static partial class Consts {
      public static double TWO_PI = 6.283185307179586476925286766559;
      public static double PI = 3.1415926535897932384626433832795;
      public readonly static vec3 Origin = new vec3();
      public readonly static vec3 VersorX = new vec3(1, 0, 0);
      public readonly static vec3 VersorY = new vec3(0, 1, 0);
      public readonly static vec3 VersorZ = new vec3(0, 0, 1);
      public static void Swap<T>(ref T a, ref T b) {
        T t = a;
        a = b;
        b = a;
      }
    }

    public static partial class F {
      public static vec3 SegmentIntersection(vec3 a1, vec3 b1, vec3 a2, vec3 b2) {
        double lambda, mi;
        double div;

        div = (b2.x - a2.x) * (a1.y - b1.y) - (b2.y - a2.y) * (a1.x - b1.x);
        if (div == 0)
          return null;

        lambda = ((a1.x - a2.x) * (a1.y - b1.y) - (a1.y - a2.y) * (a1.x - b1.x)) / div;
        mi = ((b2.x - a2.x) * (a1.y - a2.y) - (b2.y - a2.y) * (a1.x - a2.x))/div;
        if (lambda >= 0 && lambda <= 1 && mi >= 0 && mi <= 1)
          return (b1 - a1) * lambda;
        else
          return null;
      }

      public static double Clamp(double v, double min, double max) {
        return System.Math.Min(System.Math.Max(v, min), max);
      }
      public static int Clamp(int v, int min, int max) {
        return System.Math.Min(System.Math.Max(v, min), max);
      }
      public static float Clamp(float v, float min, float max) {
        return System.Math.Min(System.Math.Max(v, min), max);
      }
      public static decimal Clamp(decimal v, decimal min, decimal max) {
        return System.Math.Min(System.Math.Max(v, min), max);
      }
      public static double Wrap(double v, double min, double max) {
        if (v < min)
          return max + v - min;
        if (v > max)
          return min + v - max;
        return v;
      }
      public static int Wrap(int v, int min, int max) {
        if (v < min)
          return max + v - min;
        if (v > max)
          return min + v - max;
        return v;
      }
      public static float Wrap(float v, float min, float max) {
        if (v < min)
          return max + v - min;
        if (v > max)
          return min + v - max;
        return v;
      }
      public static decimal Wrap(decimal v, decimal min, decimal max) {
        if (v < min)
          return max + v - min;
        if (v > max)
          return min + v - max;
        return v;
      }


      public static double Scale(int p, int pmin, int pmax, double min, double max) {
        return ((double)(p - pmin) * (max - min)) / (double)(pmax - pmin) + min;
      }
    }

    public sealed class vec3 { 
      public static double distance(vec3 L, vec3 R) {
        return (L -= R).length;
      }

      private double[] myPts = new double[3];

      public static vec3 operator -(vec3 k) {
        return new vec3(-k.myPts[0], -k.myPts[1], -k.myPts[2]);
      }
      public static vec3 operator +(vec3 l, vec3 r) {
        return new vec3(l.myPts[0] + r.myPts[0], l.myPts[1] + r.myPts[1], l.myPts[2] + r.myPts[2]);
      }
      public static vec3 operator +(vec3 l, double r) {
        return new vec3(l.myPts[0] + r, l.myPts[1] + r, l.myPts[2] + r);
      }
      public static vec3 operator -(vec3 l, vec3 r) {
        return new vec3(l.myPts[0] - r.myPts[0], l.myPts[1] - r.myPts[1], l.myPts[2] - r.myPts[2]);
      }
      public static vec3 operator -(vec3 l, double r) {
        return new vec3(l.myPts[0] - r, l.myPts[1] - r, l.myPts[2] - r);
      }
      public static vec3 operator *(vec3 l, vec3 r) {
        return new vec3(l.myPts[0] * r.myPts[0], l.myPts[1] * r.myPts[1], l.myPts[2] * r.myPts[2]);
      }
      public static vec3 operator *(vec3 l, double r) {
        return new vec3(l.myPts[0] * r, l.myPts[1] * r, l.myPts[2] * r);
      }
      public static vec3 operator /(vec3 l, vec3 r) {
        return new vec3(l.myPts[0] / r.myPts[0], l.myPts[1] / r.myPts[1], l.myPts[2] / r.myPts[2]);
      }
      public static vec3 operator /(vec3 l, double r) {
        return new vec3(l.myPts[0] / r, l.myPts[1] / r, l.myPts[2] / r);
      }

      public double dot(vec3 l) {
        return vec3.dot(this, l);
      }
      public static double dot(vec3 l, vec3 r) {
        return r.myPts[0] * l.myPts[0] + r.myPts[1] * l.myPts[1] + r.myPts[2] * l.myPts[2]; 
      }
      public static vec3 cross(vec3 l, vec3 r) {
        return new vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
      }
      public double length {
        get {
          return System.Math.Sqrt(System.Math.Pow(myPts[0], 2) + System.Math.Pow(myPts[1], 2) + System.Math.Pow(myPts[2], 2));
        }
        set {
          double d = length;

          if (d > 0) {
            double f = value / length;
            myPts[0] *= f;
            myPts[1] *= f;
            myPts[2] *= f;
          }
        }
      }
      public void normalize() {
        double l = length;

        if (l == 0.0)
          return;

        myPts[0] /= l;
        myPts[1] /= l;
        myPts[2] /= l;
      }

      public void rotX(double angle) {
        rotX(angle, Consts.Origin);
      }
      public void rotY(double angle) {
        rotY(angle, Consts.Origin);
      }
      public void rotZ(double angle) {
        rotZ(angle, Consts.Origin);
      }
      private void add(vec3 p) {
        myPts[0] += p.myPts[0];
        myPts[1] += p.myPts[1];
        myPts[2] += p.myPts[2];
      }
      private void sub(vec3 p) {
        myPts[0] -= p.myPts[0];
        myPts[1] -= p.myPts[1];
        myPts[2] -= p.myPts[2];
      }

      public void rotX(double angle, vec3 pt) {
        double s = System.Math.Sin(angle);
        double c = System.Math.Cos(angle);

        sub(pt);
        myPts[1] = myPts[1] * c + myPts[2] * s;
        myPts[2] = myPts[2] * c - myPts[1] * s;
        add(pt);
      }
      public void rotY(double angle, vec3 pt) {
        double s = System.Math.Sin(angle);
        double c = System.Math.Cos(angle);

        sub(pt);
        myPts[2] = myPts[2] * c + myPts[0] * s;
        myPts[0] = myPts[0] * c - myPts[2] * s;
        add(pt);
      }
      public void rotZ(double angle, vec3 pt) {
        double s = System.Math.Sin(angle);
        double c = System.Math.Cos(angle);

        sub(pt);
        myPts[0] = myPts[0] * c + myPts[1] * s;
        myPts[1] = myPts[1] * c - myPts[0] * s;
        add(pt);
      }

      public vec3 normalized() {
        double l = length;

        if ( l == 0.0 )
          return new vec3(this);

        return new vec3(myPts[0] / l, myPts[1] / l, myPts[2] / l);
      }

      public double x {
        get {
          return myPts[0];
        }
        set {
          myPts[0] = value;
        }
      }
      public double y {
        get {
          return myPts[1];
        }
        set {
          myPts[1] = value;
        }
      }
      public double z {
        get {
          return myPts[2];
        }
        set {
          myPts[2] = value;
        }
      }

      public void swapXY() {
        Consts.Swap(ref myPts[0], ref myPts[1]);
      }
      public void swapXZ() {
        Consts.Swap(ref myPts[0], ref myPts[2]);
      }
      public void swapYZ() {
        Consts.Swap(ref myPts[1], ref myPts[2]);
      }

      public vec3(double a, double b, double c) {
        myPts[0] = a;
        myPts[1] = b;
        myPts[2] = c;
      }

      public vec3(vec3 inp) {
        myPts[0] = inp.myPts[0];
        myPts[1] = inp.myPts[1];
        myPts[2] = inp.myPts[2];
      }

      public vec3() {
      }
    }
  }
}