using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace WindowsApplication1
{
    // G��wna klasa siatki nawigacyjenj
    class cNavMesh
    {
        // Mapa wysokosci
        protected cHeightMap m_heightMap;

        // Lista tr�jk�t�w
        List<cTriangle> m_TriangleList;
        // Zaznaczony tr�jk�t
        protected cTriangle m_selectedTriangle;

        // �aduje mape wysokosci
        public void LoadHeightMap(Stream s, String fileName)
        {
            m_heightMap = new cHeightMap();
            m_heightMap.LoadHeightMap(s, fileName);
        }

        public cHeightMap HeightMap
        {
            get
            {
                return m_heightMap;
            }
        }


        // Tworzy podana liczbe tr�jk�t�w z mapy wysokosci terenu
        public void BuildTriangles(int count)
        {
            m_TriangleList = new List<cTriangle>();

            //-----------------------------------------------------------------------
            // 2. KOD STUDENTA
            //-----------------------------------------------------------------------
            // Utworzy� pocz�tkow� siatke nawigacyjn� zgodnie z instrukcj�


            //-----------------------------------------------------------------------

            var halfTrianglesAmountInRow = (int)Math.Sqrt(count * 0.5f);
            var x = this.HeightMap.TerrainEdgeSize / halfTrianglesAmountInRow;
            var y = -0.5f * this.m_heightMap.TerrainEdgeSize;

            for (int i = 0; i < halfTrianglesAmountInRow; i++)
            {
                for (int j = 0; j < halfTrianglesAmountInRow; j++)
                {
                    var triangleTmp = new cTriangle();

                    var v0 = new cVector3(y + (x * j), y + (x * i), this.HeightMap.GetTerrainHeight(y + (x * j), y + (x * i)));
                    var v1 = new cVector3(y + (x * (j + 1)), y + (x * (i + 1)), this.HeightMap.GetTerrainHeight(y + (x * (j + 1)), y + (x * (i + 1))));
                    var v2 = new cVector3(y + (x * j), y + (x * (i + 1)), this.HeightMap.GetTerrainHeight(y + (x * j), y + (x * (i + 1))));

                    triangleTmp.SetVertex(v0, v1, v2);

                    this.m_TriangleList.Add(triangleTmp);

                    var triangleTmp2 = new cTriangle();

                    var v02 = new cVector3(y + (x * j), y + (x * i), this.m_heightMap.GetTerrainHeight(y + (x * j), y + (x * i)));
                    var v12 = new cVector3(y + (x * (j + 1)), y + (x * i), this.m_heightMap.GetTerrainHeight(y + (x * (j + 1)), y + (x * i)));
                    var v22 = new cVector3(y + (x * (j + 1)), y + (x * (i + 1)), this.m_heightMap.GetTerrainHeight(y + (x * (j + 1)), y + (x * (i + 1))));

                    triangleTmp2.SetVertex(v02, v12, v22);

                    this.m_TriangleList.Add(triangleTmp2);
                }
            }
        }

        // Usuwa tr�j�kty kt�re maj� za du�e nachylenie,
        // maxGradient: maxymalne nachylenie powierzchni w radianach po kt�rym mo�na si� porusza�
        public int DropTriangleBySlopeGradient(float maxGradient)
        {
            //-----------------------------------------------------------------------
            // 4. KOD STUDENTA
            //-----------------------------------------------------------------------
            // Usun�� z listy aktulanych element�w siatki, obszary o zbyt du�ym nachyleniu
            // Zwr�ci� liczb� usunietych element�w
            // HINT 1: wykorzysta� iloczyn skalarny
            // HINT 2: pamieta� o aktualizacji s�siedztwa

            var degree = Math.Cos(maxGradient);

            var baseVector = new cVector3(0f, 0f, 1f);

            var trianglesList = new List<cTriangle>();

            for (int i = 0; i < this.m_TriangleList.Count; i++)
            {
                var dotProduct = this.m_TriangleList[i].GetNormal().Dot(baseVector);

                if (dotProduct >= degree)
                {
                    trianglesList.Add(this.m_TriangleList[i]);
                }
                else
                {
                    for (int neighbourNr = 0; neighbourNr < 3; neighbourNr++)
                    {
                        if (this.m_TriangleList[i].GetNeighbour(neighbourNr) != null)
                        {
                            this.m_TriangleList[i].GetNeighbour(neighbourNr).RemoveNeighbour(this.m_TriangleList[i]);
                        }

                        this.m_TriangleList[i].SetNeighbour(neighbourNr, null);
                    }
                }
            }

            this.m_TriangleList.Clear();
            this.m_TriangleList.AddRange(trianglesList);

            //-----------------------------------------------------------------------
            return 0;

        }

        // Usuwa obszary do kt�rych nie da si� dotrze� z podanego abszaru pocz�tkowego
        public void DropUnreachableArea()
        {
            cTriangle startArea = m_selectedTriangle;
            if (startArea == null)
                return;

            //-----------------------------------------------------------------------
            // 5. KOD STUDENTA
            //-----------------------------------------------------------------------
            // Z aktualnej listy obszar�w usun�� obszary do kt�rych nie da si� dotrze� z zadanego obszaru
            // HINT 1: Mo�na doda� dodatkowe pole do klasy cTriangle bool m_reachable oraz property
            // HINT 2: Pamieta� o aktulizacji powi�za� s�dztwa obszar�w
            //-----------------------------------------------------------------------
            var reachablesList = new List<cTriangle>();
            reachablesList.Add(startArea);

            startArea.m_reachable = true;

            SearchNeighboursRec(startArea);

            for (int i = this.m_TriangleList.Count - 1; i >= 0; i--)
            {
                if (this.m_TriangleList[i].m_reachable == false)
                {
                    this.m_TriangleList.RemoveAt(i);
                }
            }

            //-----------------------------------------------------------------------
            return;
        }

        private void SearchNeighboursRec(cTriangle triangle)
        {
            for (int i = 0; i < 3; ++i)
            {
                var neighbour = triangle.GetNeighbour(i);

                if (neighbour != null)
                {
                    if (neighbour.m_reachable == false)
                    {
                        neighbour.m_reachable = true;
                        SearchNeighboursRec(neighbour);
                    }
                }
            }
        }

        // Ustawia sasiad�w poszczeg�lnych tr�jk�t�w
        public void SetTriangleNeighbour()
        {
            //-----------------------------------------------------------------------
            // 3. KOD STUDENTA
            // Wyznaczy� obszary s�siednie wszystkich element�w siatki
            // Wykorzysta� algorytm podany w instrukcji
            //-----------------------------------------------------------------------      

            var trianglesAmount = this.m_TriangleList.Count;

            var countInStrip = ((int)Math.Sqrt(trianglesAmount / 2f)) * 2;

            for (int i = 0; i < trianglesAmount; i++)
            {
                if ((i % 2) != 0)
                {
                    this.m_TriangleList[i].SetNeighbour(0, this.m_TriangleList[i - 1]);

                    if ((i % countInStrip) != (countInStrip - 1))
                    {
                        this.m_TriangleList[i].SetNeighbour(2, this.m_TriangleList[i + 1]);
                    }

                    if (i > countInStrip)
                    {
                        this.m_TriangleList[i].SetNeighbour(1, this.m_TriangleList[i - countInStrip - 1]);
                    }
                }
                else
                {
                    if ((i % countInStrip) != 0)
                    {
                        this.m_TriangleList[i].SetNeighbour(0, this.m_TriangleList[i - 1]);
                    }

                    if (i < (this.m_TriangleList.Count - countInStrip))
                    {
                        this.m_TriangleList[i].SetNeighbour(2, this.m_TriangleList[i + countInStrip + 1]);
                    }

                    this.m_TriangleList[i].SetNeighbour(1, this.m_TriangleList[i + 1]);
                }
            }

            //-----------------------------------------------------------------------
            return;
        }
        // Rysuje siatke w podanym obszarze, na danym panelu
        public void PreviewMesh(int DrawAreaWidth, int DrawAreaHeight, Panel p)
        {
            if (m_heightMap != null)
            {
                if (m_TriangleList != null)
                    foreach (cTriangle t in m_TriangleList)
                        t.Draw(DrawAreaWidth, DrawAreaHeight, p, m_heightMap.TerrainEdgeSize);
            }
        }

        // Zaznacza tr�jk�t zawieraj�cy podany punkt
        public int SelectTriangle(int x, int y)
        {
            int index = -1;
            if (m_TriangleList == null)
                return -1;

            cTriangle selected = null;
            if (m_heightMap != null)
            {
                // Przeliczamy wsp�rzedne ekranu na terenu
                float position_x = (float)((x * (1.0f / 512) - 0.5f) * m_heightMap.TerrainEdgeSize);
                float position_y = (float)((y * (1.0f / 512) - 0.5f) * m_heightMap.TerrainEdgeSize);

                // Szukamy tr�jk�ta
                for (int i = 0; i < m_TriangleList.Count; i++)
                    if (m_TriangleList[i].IsPointInTriangle(position_x, position_y))
                    {
                        selected = m_TriangleList[i];
                        index = i;
                        break;
                    }
            }
            // Odznaczamy poprzedni obszar
            if (m_selectedTriangle != null)
            {
                m_selectedTriangle.Selected = true;
                m_selectedTriangle.Select(false, -1);
                m_selectedTriangle = null;
            }
            // Zaznaczamy wybrany tr�jk�t
            if (selected != null)
            {
                selected.Selected = true;
                m_selectedTriangle = selected;
                return index;

            }
            else
                /// Nie znaleziono trojk�ta
                return -1;

        }
        // Zaznacza tr�jk�t i jego s�siad�w
        public void SelectTriangleNeighbour(bool Selected)
        {
            if (m_selectedTriangle != null)
            {
                m_selectedTriangle.Selected = false;
                m_selectedTriangle.Select(Selected, 1);
                m_selectedTriangle.Selected = true;
            }

        }

        //-------------------------------------------------------------------------
        // PROPERTISY
        //-------------------------------------------------------------------------
        // Zaznaczony tr�jk�t
        public cTriangle Selected
        {
            get
            {
                return m_selectedTriangle;
            }
        }




    }
}
