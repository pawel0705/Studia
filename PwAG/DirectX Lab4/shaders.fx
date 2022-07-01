struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VSOutput
{
	float4 clipPos : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;	
	float3 worldPos : TEXCOORD1;
	float3 modelPos : TEXCOORD2;
	float3 colMult : TEXCOORD3;
};

cbuffer cb_scene
{
	matrix viewProjectionMatrix;
};

cbuffer cb_object
{
	matrix worldMatrix;
};

Texture2D ggTex : register(t0);
SamplerState basicSampler : register(s0);
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
VSOutput VSMain(in VSInput input)
{
	VSOutput output;

	output.modelPos = input.position;
	output.worldPos = mul(worldMatrix, float4(output.modelPos.xyz, 1.0)).xyz;
	output.clipPos = mul(viewProjectionMatrix, float4(output.worldPos.xyz, 1.0));
	output.normal = mul(worldMatrix, float4(input.normal.xyz, 0)).xyz;
	output.texCoord = input.texCoord;
	output.colMult = 1.0.xxx;

	return output;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
typedef VSOutput GSInput;
typedef VSOutput GSOutput;
static float scale = 1.025;					//global variable marked static is _not_ visible to the app. (not a const-buffer/uniform var.)

GSOutput extrudeVertex(GSInput v)
{
	GSOutput v1 = v;
		
	v1.modelPos *= scale.xxx;
	v1.worldPos = mul(worldMatrix, float4(v1.modelPos.xyz, 1));
	v1.clipPos = mul(viewProjectionMatrix, float4(v1.worldPos.xyz, 1));	

	return v1;
}

// z 3 na 9 ! zmiana
[maxvertexcount(9)]
void GSMain(triangle GSInput input[3], inout TriangleStream<GSOutput> outputStream)
{
	GSOutput inputCopy[3] = { input[0], input[1], input[2] }; // dodane zmiana

	for (int i = 0; i < 3; i++)
	{
		outputStream.Append(input[i]);
	}
	outputStream.RestartStrip();

	// dodane ! zmiana
	for (int i = 0; i < 3; i++)
	{
		inputCopy[i].colMult = 0.0.xxx;
		outputStream.Append(inputCopy[i]);
		outputStream.Append(extrudeVertex(inputCopy[i]));
	}

	outputStream.RestartStrip();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
typedef GSOutput PSInput;

float4 PSMain(PSInput input) : SV_TARGET
{
	float4 texCol = ggTex.Sample(basicSampler, input.texCoord);

	float3 lightPos = float3(3.f, 5.f, -3.f);
	float3 toLightDir = normalize(lightPos - input.worldPos);
	float3 normal = normalize(input.normal);
	
	float diffuse = saturate(dot(toLightDir, normal));
	float amb = 0.5;

	return float4((diffuse + amb) * texCol.rgb * input.colMult, 1.0);
}
///////////////////////////////////////////////////////////////////////////////////////////////