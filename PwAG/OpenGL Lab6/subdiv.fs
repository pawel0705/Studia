uniform float time;

void main() 
{
	// gl_FragColor =  gl_Color;
	gl_FragColor = vec4((sin(time * 5.0) + 1) * 0.4, (cos(time * 4.0) + 1) * 0.4 , (sin(time * 3.0) + 1) * 0.4, 1.0);
}
