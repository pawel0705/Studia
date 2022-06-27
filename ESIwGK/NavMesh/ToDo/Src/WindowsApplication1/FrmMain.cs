using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WindowsApplication1
{
  public partial class FrmMain : Form
  {
    //protected 
    private cNavMesh m_navMesh;

    public FrmMain()
    {
      InitializeComponent();
      // Tworzymy g³owna klasa aplikacji
      m_navMesh = new cNavMesh();
    }
    
     

    private void btnLoad_Click(object sender, EventArgs e)
    {
      if (ofdLoad.ShowDialog() == DialogResult.OK)
      { 
        m_navMesh.LoadHeightMap(ofdLoad.OpenFile(), ofdLoad.FileName);
        if (m_navMesh.HeightMap != null)
        {
          if (m_navMesh.HeightMap.FileName.Length > 30)
            lblFileName.Text = m_navMesh.HeightMap.FileName.Substring(m_navMesh.HeightMap.FileName.Length - 30, 30).PadLeft(33, '.');
          else
            lblFileName.Text = m_navMesh.HeightMap.FileName;
          this.Text = "NavMesh SIwGK: "+m_navMesh.HeightMap.FileName;
          lblTerrainSize.Text = m_navMesh.HeightMap.TerrainEdgeSize.ToString() + " x " + m_navMesh.HeightMap.TerrainEdgeSize.ToString();
          lblMaxHeight.Text = m_navMesh.HeightMap.MaxHeight.ToString();
          lblMinHeight.Text = m_navMesh.HeightMap.MinHeight.ToString();
        }

        if (m_navMesh.HeightMap != null)
          m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
      }
    }

    private void btnPreview_Click(object sender, EventArgs e)
    {
      if (m_navMesh.HeightMap != null)
        m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
    }

    private void btnGetTerrainHeight_Click(object sender, EventArgs e)
    {
      if (m_navMesh.HeightMap != null)
      {
        float x = 0;
        float y = 0;
        bool result;
        result = float.TryParse(txtX.Text, out x) && float.TryParse(txtY.Text, out y);
        if (result)
        {
          lblTerrainHeight.Text = m_navMesh.HeightMap.GetTerrainHeight(x, y).ToString();
          stsStrip.Items[0].Text = "Zwrócono wysokoœæ: "+lblTerrainHeight.Text;
        }
        else
          stsStrip.Items[0].Text = "Niepoprawne wspó³rzêdne punktu";
      }
    }

    private void FrmMain_Load(object sender, EventArgs e)
    {

    }

    private void lblPreviewMesh_Click(object sender, EventArgs e)
    {
      m_navMesh.PreviewMesh(512, 512, pnlPreview);
    }

    private void btnBuildCommonMesh_Click(object sender, EventArgs e)
    {
      if (m_navMesh.HeightMap != null)
      {
        int count = (int)(Math.Pow(2.0f,trcTriangleCount.Value));
        m_navMesh.BuildTriangles(count * count * 2);
        m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
        m_navMesh.PreviewMesh(512, 512, pnlPreview);
      }
    }

    private void btnDropTriangleBySlope_Click(object sender, EventArgs e)
    {
      if (m_navMesh.HeightMap != null)
      {
        float maxSlopeGradient = (float)((trcMaxTerrainSlope.Value) * Math.PI / 180.0f);
        int count = (int)(Math.Pow(2.0f, trcTriangleCount.Value));
        m_navMesh.DropTriangleBySlopeGradient(maxSlopeGradient);
        m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
        m_navMesh.PreviewMesh(512, 512, pnlPreview);
      }
    }

    private void pnlPreview_MouseClick(object sender, MouseEventArgs e)
    {
      m_navMesh.SelectTriangleNeighbour(false);
      int id = m_navMesh.SelectTriangle(e.X, e.Y);
      if (id > -1)
      {
        lblSelectedID.Text = id.ToString();
        lblStartID.Text = id.ToString();

        if (m_navMesh.Selected != null)
        {
          lblNeighbourCount.Text = m_navMesh.Selected.GetNeighbourCount().ToString();
        }
      }
    }

    private void btnSetNeighbour_Click(object sender, EventArgs e)
    {
      m_navMesh.SetTriangleNeighbour();
    }

    private void btnMarkSelectedAreaNeighbour_Click(object sender, EventArgs e)
    {
      m_navMesh.SelectTriangleNeighbour(true);
      m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
      m_navMesh.PreviewMesh(512, 512, pnlPreview);
    }

    private void btnDropUnreachableArea_Click(object sender, EventArgs e)
    {
      m_navMesh.DropUnreachableArea();
      
      m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
      m_navMesh.PreviewMesh(512, 512, pnlPreview);
    }

    private void pnlPreview_Paint(object sender, PaintEventArgs e)
    {
      if (m_navMesh.HeightMap != null)
      {
        m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
        m_navMesh.PreviewMesh(512, 512, pnlPreview);
      }
    }

    private void btnCurrentMeshPreview_Click(object sender, EventArgs e)
    {
      if (m_navMesh.HeightMap != null)
      {
        m_navMesh.HeightMap.Draw(512, 512, pnlPreview);
        m_navMesh.PreviewMesh(512, 512, pnlPreview);
      }
    }


  }
}