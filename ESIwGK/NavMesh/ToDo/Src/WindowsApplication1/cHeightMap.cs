using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;


namespace WindowsApplication1
{
    // Klasa mapy wysokoœci, odpowiada za:
    //   wczytanie danych
    //   zwracanie wysokosci terenu w zadanym punkcie - wps swiata
    //   zwracanie wysokosci terenu w zadanym punkcie - wps pliku z mapa wysokosci
    class cHeightMap
    {
        protected
        // Binarne dane mapy wysokosci - 16 bitowe probki danych
        ushort[,] m_rawData;
        // Dana przeliczone
        float[,] m_heightData;

        // Wysokosc bazowa
        float m_baseHeight;
        // Zakres wysokosci
        float m_heightRange;

        // Rozmiar tablicy z danymi - zakladamy ze tablica jest kwadratowa
        protected uint m_rawDataSize;
        // Rozmiar krawedzi terenu
        protected float m_terrainEdgeSize;

        // Nazwa wczytanego pliku terenu
        protected String m_fileName;

        // Minimalna i maksymalna wysokoœæ
        protected float m_minHeight;
        protected float m_maxHeight;



        //-------------------------------------------------------------------------
        // METODY POMOCNICZE
        //-------------------------------------------------------------------------
        // Czyta nag³ówek pliku terenu
        protected bool DoReadFileHeader(BinaryReader br)
        {
            // Poczatek naglowka to para waratosc typu uint (unsigned integer 32 bit)
            // Pierwsza wartosc to ID pliku: oczekujemy wartosci 0xF8E9DACB
            // Druga wartosc to wersja pliku: oczekujemy wartosci 100
            uint fileTypeID = br.ReadUInt32();
            uint fileVersionID = br.ReadUInt32();
            // Jesli nie jest to plik terenu, lub wersja jest nie obsugiwana
            if ((fileTypeID != 0xF8E9DACB) || (fileVersionID != 100))
            {
                return false;
            }
            // Czytam dalsza czêœæ nag³ówa czyli informacje o terenie
            // Rozmiar zbioru danych: para wartoœci uint (druga mo¿na pomin¹æ, ropatrujemy tylko obszary kwadratowe)
            m_rawDataSize = br.ReadUInt32();
            br.BaseStream.Position += 4;
            // Wysokoœæ bazowa: wartoœæ typu float
            m_baseHeight = br.ReadSingle();
            // Zakres wysokosci: wartoœæ typu float
            m_heightRange = br.ReadSingle();
            // Rozmiar terenu: para wartoœci typu float (druga mo¿na pomin¹æ, ropatrujemy tylko obszary kwadratowe)
            m_terrainEdgeSize = br.ReadSingle();
            br.BaseStream.Position += 4;
            // Wszystko mamy, zwracamy true jako potwierdzenie
            return true;

        }
        // Czyta dane terenu
        protected bool DoReadRawData(BinaryReader br)
        {
            // Najpierw tworzymy tablice na dane raw
            m_rawData = new ushort[m_rawDataSize, m_rawDataSize];
            // a takze tablice na dane przeliczone
            m_heightData = new float[m_rawDataSize, m_rawDataSize];


            //-----------------------------------------------------------------------
            // 1. KOD STUDENTA
            //-----------------------------------------------------------------------
            // Wczytaæ i przeliczyæ dane mapy wysokosci
            // Dana zapiasna s¹ w postaci 16 bitowych próbek bez znaku
            // Wyznaczyæ minmaln¹ i maksymaln¹ wysokoœæ
            // HINT 1: wykorzystaæ wzór => wysokosc = (wartosc_raw / 0xFFFF * zakres_wys) + wysokosc_bazowa


            //-----------------------------------------------------------------------
            for (int i = 0; i < m_rawDataSize; i++)
            {
                for (int j = 0; j < m_rawDataSize; j++)
                {
                    this.m_rawData[i, j] = br.ReadUInt16();
                    this.m_heightData[i, j] = (((float)this.m_rawData[i, j] / 0xFFFF) * this.m_heightRange) + this.m_baseHeight;

                    if (this.m_heightData[i, j] > this.m_maxHeight)
                    {
                        this.m_maxHeight = this.m_heightData[i, j];
                    }
                    else if (this.m_heightData[i, j] < this.m_minHeight)
                    {
                        this.m_minHeight = this.m_heightData[i, j];
                    }
                }
            }
            return true;
        }


        //-------------------------------------------------------------------------
        // METODY PUBLICZNE
        //-------------------------------------------------------------------------
        // Konstruktor
        public cHeightMap()
        {
            // Nie ma co robiæ :]
        }
        // Zwraca wysokosc terenu - wsp swiata
        public float GetTerrainHeight(float x, float y)
        {
            // Musimy najpierw wyznaczyæ indeks elementów w tablicy, wybiaramy najbli¿sze, 
            // bez interpolacji, nie ma ona bowiem znaczenia w tym æwiczeniu

            // Zak³adamy ¿e srodek terenu znajduje siê w punkcie 0,0
            // Zatem pierwsze co sprawdzamy czy punkt nie jest z poza zakresu
            x = Math.Max(x, -0.5f * m_terrainEdgeSize);
            x = Math.Min(x, 0.5f * m_terrainEdgeSize);
            y = Math.Max(y, -0.5f * m_terrainEdgeSize);
            y = Math.Min(y, 0.5f * m_terrainEdgeSize);

            // Przesuwamy punkt o po³owe rozmiaru i normalizujemy wzgledem rozmiary
            x = (x + 0.5f * m_terrainEdgeSize) / m_terrainEdgeSize;
            y = (y + 0.5f * m_terrainEdgeSize) / m_terrainEdgeSize;

            int index_x = (int)(x * (m_rawDataSize - 1));
            int index_y = (int)(y * (m_rawDataSize - 1));

            return m_heightData[index_x, index_y];
        }
        // £aduje dane z podanego strumienia
        public bool LoadHeightMap(Stream s, String fileName)
        {
            // Tworzy binaryReader
            BinaryReader br = new BinaryReader(s);

            m_fileName = fileName;
            if (DoReadFileHeader(br))
                return DoReadRawData(br);
            return false;
        }

        // Rysuje podgl¹d mapy
        public void Draw(int DrawAreaWidth, int DrawAreaHeight, Panel p)
        {
            System.Drawing.Graphics previewChart = p.CreateGraphics();

            // Ile razy bedziemy rysowaæ
            int count = DrawAreaWidth;
            // Pocz¹tkowa pzycja próbki
            float x = -0.5f * m_terrainEdgeSize;
            float y = -0.5f * m_terrainEdgeSize;
            // Wartoœæ o jak¹ inkremetujemy pozycje próbki
            float step = m_terrainEdgeSize / count;
            byte[] buffer = new byte[count * count * 3];

            // Wyznaczamy wartoœæ koloru dla wysokosci
            for (int i = 0; i < count; i++)
            {
                // Pocz¹tkowa pzycja próbki: x
                x = -0.5f * m_terrainEdgeSize;
                for (int j = 0; j < count; j++)
                {
                    // Pobiramy wysokosc i normalizujemy w min/max
                    float h = GetTerrainHeight(x, y);
                    h = (h - m_minHeight) / (m_maxHeight - m_minHeight);

                    buffer[i * count * 3 + j * 3 + 0] = (byte)(0 * 255);
                    buffer[i * count * 3 + j * 3 + 1] = (byte)(h * 255);
                    buffer[i * count * 3 + j * 3 + 2] = (byte)(0 * 255);
                    x += step;
                }
                y += step;
            }

            // Zeby nie kombinowac, robimy to klasycznie jak w C++ :]
            unsafe
            {
                // Tworzymy bitmape którê bedziemy wyrysowywaæ
                Bitmap bmp = new Bitmap(DrawAreaWidth, DrawAreaHeight, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
                // Wykonujemy lock na bitmapie i dobieramy sie do pixeli
                BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, count, count), System.Drawing.Imaging.ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
                // Prawie jak c++, mo¿na zrobiæ to lepiej :P
                byte* data = (byte*)(bmpData.Scan0.ToPointer());
                for (int i = 0; i < count * count * 3; i++)
                    data[i] = buffer[i];
                // Konczymy kopiowania danych do bitmapy
                bmp.UnlockBits(bmpData);
                // Na koniec wyrysowujemy 
                previewChart.DrawImageUnscaled(bmp, 0, 0);
            }

        }

        //-------------------------------------------------------------------------
        // PROPERTISY
        //-------------------------------------------------------------------------
        // Minimalna wysokoœæ (ReadOnly)
        public float MinHeight
        {
            get
            {
                return m_minHeight;
            }
        }
        // Maksymalna wysokoœæ (ReadOnly)
        public float MaxHeight
        {
            get
            {
                return m_maxHeight;
            }
        }
        // KrawêdŸ terenu (ReadOnly)
        public float TerrainEdgeSize
        {
            get
            {
                return m_terrainEdgeSize;
            }
        }
        // Nazwa pliku terenu
        public string FileName
        {
            get
            {
                return m_fileName;
            }
        }

    }

}
