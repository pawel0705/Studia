Shader "Custom/GS Billboard" 
{
	Properties 
	{
		_MainTex ("Base (RGB)", 2D) = "white" {}
	}

	SubShader 
	{
		Pass
		{
			Tags { "Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent" }
			//TODO: Ustalić typ mieszania kolorów dla cząsteczek
			//Blend One One
			//Blend DstColor One
			Blend SrcAlpha One
			//Blend SrcAlpha OneMinusSrcColor 
			//Blend One OneMinusSrcColor
			
			//BlendOp Add - domyślna - nie trzeba definiować
			//BlendOP Max //wybiera maksymalną wartość bez rozjaśniania
			//BlendOp RevSub //mroczne cząsteczki (pochłaniające światło)
			ColorMask RGB

			Cull Off Lighting Off ZWrite Off
		
			CGPROGRAM
				#pragma target 4.0
				#pragma vertex VS_Main
				#pragma fragment FS_Main
				#pragma geometry GS_Main
				#include "UnityCG.cginc" 

				// **************************************************************
				// Data structures												*
				// **************************************************************
				struct GS_INPUT
				{
					float4	pos		: POSITION;

					float2  tex0	: TEXCOORD0;
					float4 color : COLOR;
					//TODO: można zdefiniować kolejne parametry np
					//float3	normal	: NORMAL;
				};

				struct FS_INPUT
				{
					float4	pos		: POSITION;
					float2  tex0	: TEXCOORD0;
					float4 color : COLOR;
				};


				// **************************************************************
				// Vars															*
				// **************************************************************

				float _Size;
				float4x4 _VP;
				sampler2D _MainTex;
				uniform float4x4  _invView;
				// **************************************************************
				// Shader Programs												*
				// **************************************************************

				// Vertex Shader ------------------------------------------------
				GS_INPUT VS_Main(appdata_full v)
				{
					GS_INPUT output = (GS_INPUT)0;
					//TODO: przekazać parametrty które potrzebujemy ze struktury appdata_full v
					//do GS_INPUT output
					//pozycję wierzchołka zwykle mnożymy pozycję przez macierz MVP, w tym wypadku należy przekształcić
					//współrzędne wierzchołka do współrzędnych widoku kamery ponieważ na takich współrzędnych
					//będziemy operować w geometry shader czyli należy przemnożyć je przez macierz UNITY_MATRIX_MV
					output.pos = mul(UNITY_MATRIX_MV, v.vertex);
					output.normal = v.normal;
					output.tex0 = v.texcoord;
					output.color = v.color;
					return output;
				}



				// Geometry Shader -----------------------------------------------------
				[maxvertexcount(4)]
				void GS_Main(point GS_INPUT p[1], inout TriangleStream<FS_INPUT> triStream)
				{
					//TODO: Należy wyemitować 4 wierzchołki dla danego bilboarda
					//Z jednego wierzchołka opisującego pozycję czasteczki
					//utworzyć 4 wierzchołki opisujące bilboard
					//Jako dane wejściowe posiadamy listę wierzchołków o długości jednego wierzchoła GS_INPUT p[1]
					// do danych wejściowych odwołujemy się jak do tablicy 'p[0]'

					//Każdorazowo dla każdego z czterech wierchołków należy ustalić jego pozycję kolor oraz koordynaty tekstur
					//tworząc obiekt FS_INPUT
					//Po zdefiniowaniu parametrów obiektów struktury FS_INPUT dla wierzchołka należy wywołać metodę triStream.Append(...)
					//Koordynaty tekstur są stałe i dla czterech kolejnych wierzchołków należy je podawać w odpowiedniej kolejnośći
					//np zaczynając od jednego z rogów float2(1.0f, 0.0f) kończąc na float2(0.0f, 1.0f)

					//Aby ustalić wyjściowe pozycje wierzchołka należy zmodyfikować wejściową pozycję wierzchołka o rozmiar cząsteczki
					//np dla rogu o współrzędnych tekstury float2(1.0f, 0.0f) współrzędnie wierzchołka 
					//będą wynosić pIn.pos = p[0].pos+float4(halfS.x,-halfS.y,0.0,0.0);
					//Na koniec współrzędne wierzchołka należy przekształcic z widoku kamery mnożnąc przez miacierz UNITY_MATRIX_P
					
					float2 halfS = p[0].tex0*0.5f;
					FS_INPUT pIn;
					//...
					triStream.Append(pIn);

					//Kolejne wierzchołki
				}



				// Fragment Shader -----------------------------------------------
				float4 FS_Main(FS_INPUT input) : COLOR
				{
					return tex2D(_MainTex, input.tex0)*input.color;
				}

			ENDCG
		}
	} 
}
