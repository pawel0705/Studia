struct VSInput
{
    float3 position : POSITION0;
    float4 color: COLOR;
};

struct VSOutput
{
    float4 clipPos : SV_POSITION;
    float4 clipColor: COLOR;
};

cbuffer VSConstants
{
    float4x4 ViewProjMatrix;
};

cbuffer VSConstants
{
    float4x4 worldMatrix;
};

VSOutput VSMain(in VSInput input)
{
    VSOutput output;

    output.clipPos = mul(mul(worldMatrix, ViewProjMatrix), float4(input.position.xyz, 1.0));
    output.clipColor = input.color;
    return output;
}

typedef VSOutput PSInput;

float4 PSMain(PSInput input) : SV_TARGET //note: no parameters -> we could pass VSOutput but SV_Position is not used so params can be dropped
{
    return input.clipColor;
}