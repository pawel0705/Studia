using System;
using System.Collections.Generic;
using System.Text;

namespace WindowsApplication1
{
  // Klasa wektora, zawiera podstawow¹ matematyke
  class cVector3
  {
    // Sk³adowe wektora
    private float m_x;
    private float m_y;
    private float m_z;

    //-------------------------------------------------------------------------
    // METODY PUBLICZNE
    //-------------------------------------------------------------------------
    // Konstruktor
    public cVector3()
    {
      Set(0.0f, 0.0f, 0.0f);
    }
    // Konstruktor
    public cVector3(float x, float y, float z)
    {
      Set(x, y, z);
    }
    // Konstruktor
    public cVector3(cVector3 vec)
    {
      Set(vec);
    }
    // Zwraca d³ugoœæ wektora
    public float Length()
    {
      return (float)Math.Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }
    // Normalizuje wektor, zwraca wektor znormalizowany
    // Ci¹gle ten sam wektor, nie tworzy nowego wektora
    public cVector3 Normalize()
    {
      float d = Length();
      if ( d != 0.000001f )
      {
        m_x /= d;
        m_y /= d;
        m_z /= d;
      }
      return this;
    }
    // Dodaje podany wektor
    // Zwraca ci¹gle ten sam wektor
    public cVector3 Add(cVector3 vec)
    {
      m_x += vec.m_x;
      m_y += vec.m_y;
      m_z += vec.m_z;
      return this;
    }
    // Odejmuje podany wektor
    // Zwraca ci¹gle ten sam wektor
    public cVector3 Subtract(cVector3 vec)
    {
      m_x -= vec.m_x;
      m_y -= vec.m_y;
      m_z -= vec.m_z;
      return this;
    }
    // Skaluje wektor przez podana wartosc
    // Zwraca ci¹gle ten sam wektor
    public cVector3 Scale(float scale)
    {
      m_x *= scale;
      m_y *= scale;
      m_z *= scale;
      return this;
    }
    // Ustawia wektor
    public cVector3 Set(float x, float y, float z)
    {
      m_x = x;
      m_y = y;
      m_z = z;
      return this;
    }
    // Ustawia wektor
    public cVector3 Set(cVector3 vec)
    {
      return Set(vec.m_x, vec.m_y, vec.m_z);

    }
    // Wyznacza iloczyn skalarny z podanym wektorem
    public float Dot(cVector3 vec)
    {
      return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
    }
    // Iloczyn skalarny
    public cVector3 Cross(cVector3 vec)
    {
      cVector3 temp = new cVector3();
      temp.Set( m_y * vec.m_z - m_z * vec.m_y,
                m_z * vec.m_x - m_x * vec.m_z,
                m_x * vec.m_y - m_y * vec.m_x );
      Set(temp);
      return this;
    }

    //-------------------------------------------------------------------------
    // PROPERTISY
    //-------------------------------------------------------------------------
    // Sk³adowa X
    public float X
    {
      get
      {
        return m_x;
      }
      set
      {
        m_x = value;
      }
    }
    // Sk³adowa Y
    public float Y
    {
      get
      {
        return m_y;
      }
      set
      {
        m_y = value;
      }
    }
    // Sk³adowa Z
    public float Z
    {
      get
      {
        return m_z;
      }
      set
      {
        m_z = value;
      }
    }

  }
}
