Texture2D shaderTexture;
SamplerState samplerState;

struct VSInput
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VSOutput
{
	float4 clipPos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

typedef VSOutput PSInput;

cbuffer cb_scene
{
	matrix viewProjectionMatrix;
};

cbuffer cb_object
{
	matrix worldMatrix;
};

VSOutput VSMain(in VSInput input)
{
	VSOutput output;

	float4 worldPos = mul(worldMatrix, float4(input.position.xyz, 1.0));
	output.clipPos = mul(viewProjectionMatrix, worldPos);

	output.texCoord = input.texCoord;

	return output;
}

float4 PSMain(PSInput input) : SV_TARGET						//note: no parameters -> we could pass VSOutput but SV_Position is not used so params can be dropped
{
	return shaderTexture.Sample(samplerState, input.texCoord);;
}
