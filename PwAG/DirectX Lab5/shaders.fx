struct VSInput
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer cb_scene
{
	matrix viewProjectionMatrix;
};

cbuffer cb_object
{
	matrix worldMatrix;
};

// dodane
cbuffer cb_tesselation
{
	float tesselation;
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
VSOutput VSMain(in VSInput input)
{
	VSOutput output;

	// dodane !
	output.position = float4(input.position, 1.0);
	output.color = input.color;

	// zakomentowane !
	//output.position = float4(input.position, 1.0f);
	//output.position = mul(output.position, worldMatrix);
	//output.position = mul(viewProjectionMatrix, output.position);
	//output.color = input.color;
	
	return output;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

typedef VSOutput HSInput;
typedef VSOutput HSOutput;

struct COutput
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
};

COutput PatchConstantFunction(InputPatch<HSInput, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
	COutput output;

	// zakomentowane !
	/*
	output.edges[0] = 1;
	output.edges[1] = 1;
	output.edges[2] = 1;

	output.inside = 1;
	*/

	// dodane 1 zmiana
	output.edges[0] = tesselation;
	output.edges[1] = tesselation;
	output.edges[2] = tesselation;

	output.inside = tesselation;

	return output;
}

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]
HSOutput HSMain(InputPatch<HSInput, 3> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	HSOutput output;
	output.position = patch[pointId].position;
	output.color = patch[pointId].color;

	return output;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

static const float PI = 3.1415926535897932384626433832795f;

[domain("tri")]
PSInput DSMain(COutput input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<HSOutput, 3> patch)
{
	float3 vertexPosition;
	PSInput output;

	// dodane ! zmiana
	vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;
	vertexPosition.z = 0.2 * cos(vertexPosition.x * PI) * cos(vertexPosition.y * PI);

	output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
	output.position = mul(viewProjectionMatrix, output.position);

	output.color = uvwCoord.x * patch[0].color + uvwCoord.y * patch[1].color + uvwCoord.z * patch[2].color;

	// zakomentowane !
	/*
	vertexPosition = patch[0].position;

	//???

	output.color = patch[0].color;
	*/
	return output;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

float4 PSMain(PSInput input) : SV_TARGET
{
	return input.color;
}
///////////////////////////////////////////////////////////////////////////////////////////////