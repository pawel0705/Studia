using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace WindowsApplication1
{
  // Klasa trójk¹ta
  class cTriangle
  {
    // Trojkat przechowuje informacje o swoich wierzcho³kach
    protected cVector3[] m_vertex; 
    // Ma wyznaczony wektor normlany swojej powierzchni
    protected cVector3 m_normal;

    // Przechowuje informacje o tym ktore trojk¹ty s¹ s¹siednie
    // Sasiad 0: przylega do krawedzi o wierzcho³kach 0 i 1
    // Sasiad 1: przylega do krawedzi o wierzcho³kach 1 i 2
    // Sasiad 2: przylega do krawedzi o wierzcho³kach 2 i 0
    protected cTriangle []m_neighbour;
    // Flaga czy zaznaczony
    protected bool m_isSelected;

    public bool m_reachable;

    //-------------------------------------------------------------------------
    // METODY PUBLICZNE
    //-------------------------------------------------------------------------
    // Konstruktor
    public cTriangle()
    {
      m_neighbour = new cTriangle[3];
      m_vertex = new cVector3[3];
      // Domyœlny wektor normalny
      m_normal = new cVector3(0.0f, 0.0f, 1.0f);
    }
    // Ustawia wierzcho³ki trójk¹ta
    public void SetVertex(cVector3 v0, cVector3 v1, cVector3 v2)
    {
      m_vertex[0] = new cVector3(v0);
      m_vertex[1] = new cVector3(v1);
      m_vertex[2] = new cVector3(v2);

      // Maj¹c wierzcho³ki mo¿emy wyznaczyæ krawêdzi i policzyæ normaln¹ powierzchni
      // Normaln¹ liczymy tak aby jej z by³ > 0
      // 0->1
      cVector3 edge0 = new cVector3(v1);
      edge0.Subtract(v0);
      // 1->2
      cVector3 edge1 = new cVector3(v2);
      edge1.Subtract(v1);
      // Mamy krawêdzie mo¿emy wyznczyæ normaln¹ powierzchni
      m_normal.Set(edge0);
      m_normal.Cross(edge1);
      m_normal.Normalize();
      if (m_normal.Z < 0.0f)
      { 
        m_normal.Set(edge1);
        m_normal.Cross(edge0);
        m_normal.Normalize();
      }

    }
    // Ustawia dany trójk¹t jako s¹siedni
    public void SetNeighbour(int neighbourID, cTriangle neighbour)
    {
      m_neighbour[neighbourID] = neighbour;
    }
    // Zwraca podanego s¹siada
    public cTriangle GetNeighbour(int neighbourID)
    {
      return m_neighbour[neighbourID];
    }
    // Zwraca wektor normalny powierzchni trójkata, jest to kopia wektora
    public cVector3 GetNormal()
    {
      return new cVector3(m_normal);
    }
    // Usuwa s¹siad¹, jeœli tak owy by³
    public void RemoveNeighbour(cTriangle neighbour)
    {
      for(int i=0; i<3; i++)
      if (m_neighbour[i] == neighbour)
      {
        m_neighbour[i] = null;
        return;
      }
    }
    // Wyrysowuje trójk¹t
    public void Draw(int DrawAreaWidth, int DrawAreaHeight, Panel p, float TerrainEdge)
    {
      Graphics previewChart = p.CreateGraphics();
      Pen pen;
      if (!m_isSelected)
        pen = new Pen(Color.Red,1);
      else
        pen = new Pen(Color.Blue,2);

      // Intersuje nas tylko x,y
      Point []points = new Point[3];
      for (int i = 0; i < 3; i++)
      {
        points[i] = new Point();
        points[i].X = (int)((m_vertex[i].X + (0.5f * TerrainEdge)) / TerrainEdge * (DrawAreaWidth - 1));
        points[i].Y = (int)((m_vertex[i].Y + (0.5f * TerrainEdge)) / TerrainEdge * (DrawAreaWidth - 1));
      }
      previewChart.DrawPolygon(pen, points);
    }
    // Zaznacza trójkat i ewentulanie jego s¹siedztwo
    // selected - stan flagi zaznaczenia
    // neighbourLevel - ile elementów s¹siednich zaznaczyæ (-1 wszystki, 0 - brak, 1 -> tylko swoich s¹siadów, 2-> swoich i s¹saidów s¹siadów itd)
    public void Select(bool selected, int neighbourLevel)
    {
      if (m_isSelected != selected)
      {
        m_isSelected = selected;
        if (neighbourLevel == -1)
        {
          for (int i = 0; i < 3; i++)
            if (m_neighbour[i] != null)
              m_neighbour[i].Select(selected, neighbourLevel);
        }
        else if (neighbourLevel > 0)
        {
          for (int i = 0; i < 3; i++)
            if (m_neighbour[i] != null)
              m_neighbour[i].Select(selected, neighbourLevel - 1);
        }
      }
    
    }
    // Sprawdza czy punkt zawiera siê w obszarze trójk¹ta
    public bool IsPointInTriangle(float x, float y)
    { 
      // Wyznaczamy wektory od srodka do podanego punktu do wierzcho³ków

      cVector3 point = new cVector3(x,y,0);
      cVector3 t0 = new cVector3(m_vertex[0].X, m_vertex[0].Y, 0);
      cVector3 t1 = new cVector3(m_vertex[1].X, m_vertex[1].Y, 0);
      cVector3 t2 = new cVector3(m_vertex[2].X, m_vertex[2].Y, 0);
      t0.Subtract(point);
      t1.Subtract(point);
      t2.Subtract(point);
      t0.Normalize();
      t1.Normalize();
      t2.Normalize();
      
      // Wyzanczamy k¹ty miêdzy punktem a wierzcho³kami
      float arc = (float)Math.Acos(t0.Dot(t1));
      arc += (float)Math.Acos(t1.Dot(t2));
      arc += (float)Math.Acos(t2.Dot(t0));

      // Jeœli jest 2PI to jest w trójk¹cie
      if ((arc > 2*Math.PI - 0.01) && (arc < 2*Math.PI + 0.01))
        return true;
      return false;
    }
    // Zwraca liczbê s¹siadów
    public int GetNeighbourCount()
    {
      int count = 0;
      for (int i = 0; i < 3; i++)
      {
        if (m_neighbour[i] != null)
          count++;
      }
      return count;
    }
    
    //-------------------------------------------------------------------------
    // PROPERTISY
    //-------------------------------------------------------------------------
    // Flaga zaznaczenia
    public bool Selected
    {
      get
      {
        return m_isSelected;
      }
      set
      {
        m_isSelected = value;
      }
    
    }

    

  }
}
