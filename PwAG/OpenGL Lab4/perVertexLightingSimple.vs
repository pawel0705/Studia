// perVertexLightingSimple.vs
//
// Zadania:
// 1. Implementacja uproszczonego oœwietlenia Phonga (per-vertex lighting) uwzglêdniaj¹cego tylko œwiat³o globalne i jedno kierunkowe Ÿród³o œwiat³a. 
// Wynikowy kolor wierzcho³ka jest interpolowany w shaderze fragmentów na piksele. Wzór podany w instrukcji. 
// 2. Implementacja uproszczonego mapowanie normalnych, umo¿liwiaj¹cego osi¹gniêcie efektu fali (rysunek w instrukcji) bez zmiany geometrii.

void main()
{
	// do rozwi¹zanie bêd¹ potrzebne nastêpuj¹ce zmienne, które nale¿y wyznaczyæ
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
