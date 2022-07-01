// perVertexLightingSimple.vs
//
// Zadania:
// 1. Implementacja uproszczonego o�wietlenia Phonga (per-vertex lighting) uwzgl�dniaj�cego tylko �wiat�o globalne i jedno kierunkowe �r�d�o �wiat�a. 
// Wynikowy kolor wierzcho�ka jest interpolowany w shaderze fragment�w na piksele. Wz�r podany w instrukcji. 
// 2. Implementacja uproszczonego mapowanie normalnych, umo�liwiaj�cego osi�gni�cie efektu fali (rysunek w instrukcji) bez zmiany geometrii.

void main()
{
	// do rozwi�zanie b�d� potrzebne nast�puj�ce zmienne, kt�re nale�y wyznaczy�
	vec3 normal, lightDirection, halfVector;
	vec4 globalAmbient, ambient, diffuse, specular;
	
	//normal = normalize(gl_NormalMatrix * gl_Normal);
	normal = normalize(vec3(sin(gl_Vertex.x * 2), sin(gl_Vertex.y), 0.0));
	
	lightDirection = normalize(gl_LightSource[0].position - gl_Vertex);
	halfVector = gl_LightSource[0].halfVector;

	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

	diffuse = max(dot(normal, lightDirection), 0.0) * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
	specular = pow(max(dot(halfVector, normal), 0.0), gl_FrontMaterial.shininess) * gl_LightSource[0].specular * gl_FrontMaterial.specular;
	
	//wynik
	//gl_FrontColor = vec4(0, 1, 0, 1);
	gl_FrontColor =  globalAmbient + ambient + diffuse + specular;
	
	gl_Position = ftransform();
}
