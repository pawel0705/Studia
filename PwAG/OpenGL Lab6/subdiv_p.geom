#version 430 core
#extension GL_EXT_gpu_shader4: enable
#extension GL_EXT_geometry_shader4: enable

layout( triangles ) in;

//wyjsciowym prymitywem powinny byc punkty!!!
layout( points, max_vertices=200 ) out; // odkomentowane
//layout(triangle_strip, max_vertices = 6) out; // zakomentowane

uniform float time;
uniform int level;

vec4 CG;

void main() {
	
	float power = time * 10;

	CG = ( gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position ) / 3.; //srodek

	
	//for(int i = 0; i < gl_in.length(); i++) {
	//	gl_Position = gl_in[i].gl_Position;
	//	EmitVertex();
	//}
	//EndPrimitive();

	int i = 0;
	while(i < gl_in.length())
	{
		// pozycje wierzcholkow trojkata
		vec4 position0 = gl_in[i++].gl_Position;
		vec4 position1 = gl_in[i++].gl_Position;
		vec4 position2 = gl_in[i++].gl_Position;

		// wartosc kroku oraz liczba krokow dla s oraz t
		float stepValue = pow(2, -level);
		int stepsCount = int(pow(2, level)) + 1;

		int i=0;
		float s = 0.0;
		for(i = 0; i < stepsCount; ++i, s+= stepValue)
		{
			int j = 0;
			float t = 0.0;
			for(j = 0; j < stepsCount - i; ++j, t += stepValue)
			{
				// parametryzacja trojkata
				vec4 st = position0 + s * (position1 - position0) + t * (position2 - position0);
			
				gl_Position = CG + (st - CG) * time;
				EmitVertex();
			}
		}
	}
	EndPrimitive();
}