Shader "Hidden/Shader"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}

	}
		SubShader
	{
		// No culling or depth
		Cull Off ZWrite Off ZTest Always

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag

			#include "UnityCG.cginc"

			struct appdata
			{
				float4 vertex : POSITION;
				float2 uv : TEXCOORD0;
			};

			struct v2f
			{
				float2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
			};

			v2f vert(appdata v)
			{
				v2f o;
				o.vertex = UnityObjectToClipPos(v.vertex);
				o.uv = v.uv;
				return o;
			}

			/*
			zwraca:
			-1 dla a < b
			 0 dla a == b
			 1 dla a > b
			*/
			int compareFloats(float a, float b)
			{
				float result = a - b;
				const float maxDiff = 0.000001;

				//a > b
				if (result > maxDiff)
					return 1;
				//a < b
				if (result < -maxDiff)
					return -1;
				//a == b
				return 0;
			}

			sampler2D _MainTex;

			//pozycja startowa malowania
			uniform float _beginXs[20];
			uniform float _beginYs[20];

			//kolor malowania
			uniform float3 _color;

			//wektor kierunkowy prostej - kierunek malowania
			uniform float _dirXs[20];
			uniform float _dirYs[20];

			//parametry prostej (_a = _dirY/_dirX)
			uniform float _as[20];
			uniform float _bs[20];

			//całościowy, aktualny progess - odległość od rzutowanego punktu do punktu startowego, dla której należy zamalować
			uniform float _progress;

			//seed dla wygenerowania losowej liczby
			uniform int _penNr;

			//typ malowania:
			//	1 - pędzel
			//	2 - sprej
			uniform int _type;
			
			//gęstość spreju
			uniform float _sprayDens;

			fixed4 draw(fixed4 col, float2 pos)
			{
				int i = 0;
				for (i = 0; i <= _penNr; i++) {
					//wyliczanie punktu zrzutowanego na prostą (o wektorze kierunkowym z uniformów)
					float orthA = -1 / _as[i];
					float orthB = pos.y - orthA * pos.x;
					
					float orthX = (orthB - _bs[i]) / (_as[i] - orthA);
					float orthY = _as[i] * orthX + _bs[i];
					
					//pozycja zrzutowanego punktu
					float2 posPrim = float2(orthX, orthY);
					
					//I etap sprawdzania - odległość zrzutowanego punktu od punktu początkowego
					float dist = distance(float2(_beginXs[i], _beginYs[i]), posPrim);
					
					if (_penNr > i || dist < (_progress - _penNr)) 
					{
						if (_type == 1) //pędzel
						{
							//II etap sprawdzania - odległość punktu (o pozycji pos) od prostej (od zrzutowanego punktu)
							float lineWidth = (pos.x * sin(pos.y * 10)) / 20.0 + 0.05;
							if (distance(pos, posPrim) < lineWidth)
							{
								col.rgb = _color;
							}
						}
						else if (_type == 2) //sprej
						{
							if (distance(pos, posPrim) < 0.02)
							{
								float random = frac(sin(dot(pos, float2(12.9898, 78.233))) * 43758.5453123);
								if (random < _sprayDens)
								{
									col.rgb = _color;
								}
							}
						}
					}
				}

			return col;
		}

		fixed4 frag(v2f i) : SV_Target
		{
		   fixed4 col = tex2D(_MainTex, i.uv);
		   float2 pos = i.uv;

		   col = draw(col, pos);

		   return col;
		}

		ENDCG
		}
	}
}
