Shader "Custom/SquareShader"
{
    Properties
    {
        _MainTex("Texture", 2D) = "red" {}
        CX("Center-X", Float) = 0.5
        CY("Center-Y", Float) = 0.5
        R("Radius", Float) = 20
        W("Width", Float) = 0.05
        A("AspectRatio", Float) = 1
    }
        SubShader
        {
            Pass
            {
                CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #include "UnityCG.cginc"

                struct v2f
                {
                    float2 uv : TEXCOORD0;
                    float4 vertex : SV_POSITION;
                };
                v2f vert(appdata_full v)
                {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex);
                    o.uv = v.texcoord;
                    return o;
                };


                sampler2D _MainTex;
                float CX;
                float CY;
                float R;
                float T;
                float A;
                float W;
                fixed4 frag(v2f i) : SV_Target
                {
                    fixed4 col = tex2D(_MainTex, float2(i.uv.x, 1 - i.uv.y));
                    CX = CX * A;
                    float x = i.uv.x * A;
                    float y = i.uv.y;
                    if (((x <= (CX + R + W) && x >= (CX + R)) || (x >= (CX - R - W) && x <= (CX - R))) && (y <= (CY + R + W) && y >= (CY - R - W)) ||
                        ((y <= (CY + R + W) && y >= (CY + R)) || (y <= (CY - R) && y >= (CY - R - W))) && (x <= (CX + R + W) && x >= (CX - R - W)))
                    {
                        col = fixed4(0, 1, 0, 1);
                    }
                    return col;
                }
                ENDCG
            }
        }
            FallBack "Diffuse"
}
