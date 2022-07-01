// passThrough.fs

void main()
{
	vec4 color = gl_Color;
	vec3 center = vec3(250.0, 260.0, 0.0);

	float dist = (gl_FragCoord.x - center.x) * (gl_FragCoord.x - center.x) + (gl_FragCoord.y - center.y) * (gl_FragCoord.y - center.y);
	float R_inner_squared = 400.0;
	float R_middle_squared = 2500.0;
	float R_outer_squared = 10000.0;

	if(dist < R_inner_squared)
	{
		discard;
	}
	else if (dist < R_middle_squared)
	{
		color = color * 1.5;
	}
	else if (dist < R_outer_squared)
	{
		color = vec4(1.0, 0.5, 0.2, 1.0);
	}
	gl_FragColor = color;
}
