Shader "Custom/HeartZoom"
{
    Properties
    {
        _MainTex("Texture", 2D) = "black" {} // texture on which shader will appear
        CX("Center-X", Float) = 0.5 // coordinate x od canter of heart
        CY("Center-Y", Float) = 0.5 // coordinate y od canter of heart
        R("Radius", Float) = 20 // distance between center of heart to bottom of heart
        W("Width", Float) = 0.05 // width of border line
        A("AspectRatio", Float) = 1 // aspect ratio
        Z("Zoom", Float) = 1 // zoom factor
    }
        SubShader
        {
            Pass
            {
                CGPROGRAM
                #include "UnityCG.cginc"
                // Declarations of shaders and functions which use them
                #pragma vertex vert // Vertex shader
                #pragma fragment frag //Fragment shader

            
                // Declaration of struct containing texture and vertex position
                struct v2f
                {
                    float2 uv : TEXCOORD0;
                    float4 vertex : SV_POSITION;
                };

                /* Implementation of vertex shader
                * It projects vertex position on texture
                */
                
                v2f vert(appdata_full v)
                {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex); // Transforming point from object space to the camera’s clip space
                    o.uv = v.texcoord;
                    return o;
                };


                sampler2D _MainTex; // texture on which shader will appear
                float CX; // coordinate x od canter of heart
                float CY; // coordinate y od canter of heart
                float R; // distance between center of heart to bottom of heart
                float A; // aspect ratio
                float W; // width of border line
                float Z; // zoom factor

                // Implementation of fragment shader
                fixed4 frag(v2f i) : SV_Target
                {
                    fixed4 col = tex2D(_MainTex, float2(i.uv.x, 1 - i.uv.y)); // getting color of texture
                    CX = CX * A;
                    float x = i.uv.x * A;
                    float y = i.uv.y;

                    if (y > CY) {
                        // Code for part of "bottom" of heart (one big half of the circle)
                        /* 
                        * For calculating if point is inside or on border of circle was used circle equation
                        * (x − cx)^2 + (y − cy)^2 = r^2
                        */
                        float Left = (x - CX) * (x - CX) + (y - CY) * (y - CY);
                        float Right = R * R;
                        if (Left >= (1 - W) * Right && Left <= (1 + W) * Right)
                        {
                            // Coloring if point is in border
                            col = fixed4(0.92, 1, 0.71, 1);
                        }
                        else if (Left < Right)
                        {
                            // Zoom in if point is inside of heart
                            float X = (i.uv.x - CX) / Z;
                            float Y = (i.uv.y - CY) / Z;
                            col = tex2D(_MainTex, float2(CX + X, 1 - CY - Y));
                        }
                    }
                    else {
                        //  Code for part of "top" heart (two smaller halfs of the circles)
                        if (x < CX) 
                        {
                            float R2 = R / 2;
                            float CX2 = CX - R2;
                            float Left = (x - CX2) * (x - CX2) + (y - CY) * (y - CY);
                            float Right = R2 * R2;
                            if (Left >= (1 - W) * Right && Left <= (1 + W) * Right)
                            {
                                // Coloring if point is in border
                                col = fixed4(0.92, 1, 0.71, 1);
                            }
                            else if (Left < Right)
                            {
                                // Zoom in if point is inside of heart
                                float X = (i.uv.x - CX) / Z;
                                float Y = (i.uv.y - CY) / Z;
                                col = tex2D(_MainTex, float2(CX + X, 1 - CY - Y));
                            }
                        }
                        else
                        {
                            float R2 = R / 2;
                            float CX2 = CX + R2;
                            float Left = (x - CX2) * (x - CX2) + (y - CY) * (y - CY);
                            float Right = R2 * R2;
                            if (Left >= (1 - W) * Right && Left <= (1 + W) * Right)
                            {
                                // Coloring if point is in border
                                col = fixed4(0.92, 1, 0.71, 1);
                            }
                            else if (Left < Right)
                            {
                                // Zoom in if point is inside of heart
                                float X = (i.uv.x - CX) / Z;
                                float Y = (i.uv.y - CY) / Z;
                                col = tex2D(_MainTex, float2(CX + X, 1 - CY - Y));
                            }
                        }
                    }   
                    // Returning 
                    return col;
                }
                ENDCG
            }
        }
            FallBack "Diffuse"
}
