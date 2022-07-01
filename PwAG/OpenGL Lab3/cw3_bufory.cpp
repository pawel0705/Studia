//Laboratorium 3
//Ładowanie damych do buforów, wstęp do programowania potoku

//Zadania:
//odczytac model z pliku obj --> funkcja loadOBJ
//wyrederowac
//dodac kolory do wierzchołków (atrybuty wierzcholkow)
//wykorzystac w potoku i wyrenderowac - odczytac atrybut koloru w VS, przekazac do FS

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#define GLUT_DISABLE_ATEXIT_HACK
#include "GL/glut.h"
#include "GL/glext.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "objloader.h"

#define COLORS 3

using namespace std;

static int programHandle; // obiekt programu
static int vertexShaderHandle; // obiekt shadera wierzchołków
static int fragmentShaderHandle; // obiekt shadera fragmentów
static GLint locMVP;                 // macierz przekształcenia

//identyfikatory buforow 
GLuint vbo[2]; //wierzchokow
//dodac bufor kolorow
GLfloat* colorBuffer;

size_t uv_size_t;
size_t v_size_t;
size_t n_size_t;

std::vector<glm::vec2> uvs_vector;
std::vector<glm::vec3> vertices_vector;
std::vector<glm::vec3> normals_vector;

//wskaźniki funkcji
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC	glUseProgram = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLPATCHPARAMETERIPROC glPatchParameteri = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;

// funkcja do odczytu kodu shaderow
char* readShader(char* aShaderFile)
{
	FILE* filePointer = fopen(aShaderFile, "rb");
	char* content = NULL;
	long numVal = 0;

	fseek(filePointer, 0L, SEEK_END);
	numVal = ftell(filePointer);
	fseek(filePointer, 0L, SEEK_SET);
	content = (char*)malloc((numVal + 1) * sizeof(char));
	fread(content, 1, numVal, filePointer);
	content[numVal] = '\0';
	fclose(filePointer);
	return content;
}

// incjalizacja shaderów
void setShaders(char* vertexShaderFile, char* fragmentShaderFile)
{
	GLint status = 0;

	char* vertexShader = readShader(vertexShaderFile);
	char* fragmentShader = readShader(fragmentShaderFile);

	programHandle = glCreateProgram(); // tworzenie obiektu programu
	vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER); // shader wierzchołków
	fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER); // shader fragmentów

	glShaderSource(vertexShaderHandle, 1, (const char**)&vertexShader, NULL); // ustawianie źródła shadera wierzchołków
	glShaderSource(fragmentShaderHandle, 1, (const char**)&fragmentShader, NULL); // ustawianie źródła shadera fragmentów

	// kompilacja shaderów
	glCompileShader(vertexShaderHandle);
	glCompileShader(fragmentShaderHandle);

	/* error check */

	glGetObjectParameterivARB(vertexShaderHandle, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if (!status) {
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glGetInfoLogARB(vertexShaderHandle, maxInfoLogSize, NULL, infoLog);
		std::cout << infoLog;
	}

	glGetObjectParameterivARB(fragmentShaderHandle, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if (!status) {
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glGetInfoLogARB(fragmentShaderHandle, maxInfoLogSize, NULL, infoLog);
		std::cout << infoLog;
	}

	//dodanie shaderów do programu
	glAttachShader(programHandle, vertexShaderHandle);
	glAttachShader(programHandle, fragmentShaderHandle);

	/* link */
	//uruchomienie
	glLinkProgram(programHandle);
	glGetObjectParameterivARB(programHandle, GL_OBJECT_LINK_STATUS_ARB, &status);
	if (!status) {
		const int maxInfoLogSize = 2048;
		GLchar infoLog[maxInfoLogSize];
		glGetInfoLogARB(programHandle, maxInfoLogSize, NULL, infoLog);
		std::cout << infoLog;
	}
	glUseProgram(programHandle); // Installs program into current rendering state.

	//zmienna typu UNIFORM -- macierz przekształcenia
	locMVP = glGetUniformLocation(programHandle, "MVP");
}

//TROJKAT
float points[] = {
   0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};

//można wykorzystac jako bufor kolorow
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};


void prepereBuffors()
{
	bool loaded = loadOBJ("bunny.obj", vertices_vector, uvs_vector, normals_vector); // load bunny.obj

	if (!loaded) {
		cout << "Cannot load obj!" << endl;
		return;
	}

	colorBuffer = new GLfloat[vertices_vector.size() * COLORS];

	v_size_t = vertices_vector.size() * sizeof(glm::vec3);
	uv_size_t = uvs_vector.size() * sizeof(glm::vec2);
	n_size_t = normals_vector.size() * sizeof(glm::vec3);

	int j = 0;
	int i = 0;
	int N = vertices_vector.size() * COLORS;
	int rows = sizeof g_color_buffer_data / sizeof g_color_buffer_data[0];
	int cols = sizeof g_color_buffer_data[0] / sizeof(int);
	int colorArraySize = rows * cols;

	for (;j < N; j++)
	{
		colorBuffer[j] = g_color_buffer_data[i];
		i = j % colorArraySize;
	}

	// utworzenie VBO dla wierzcholkow, normalnych i uv
	glGenBuffers(2, vbo);

	// ustawianie i ładowanie danych do bufora vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, vSize, vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, uv_size_t + v_size_t + n_size_t, 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, v_size_t, vertices_vector.data());

	glBufferSubData(GL_ARRAY_BUFFER, v_size_t, n_size_t, normals_vector.data());

	glBufferSubData(GL_ARRAY_BUFFER, n_size_t + v_size_t, uv_size_t, uvs_vector.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ustawianie i ładowanie danych do bufora colorBuffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, N * sizeof(float), colorBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);


	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 Rt = glm::rotate(glm::mat4(1.0f), glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//macierz przekształcenia
	glm::mat4 mvp = Projection * Tr * Rt;
	glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);

	//ustawnienie atrybutow wierzchołka
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // wierzcholki

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)v_size_t); // normalne

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(n_size_t + v_size_t)); // uv

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glEnableVertexAttribArray(3);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL); // kolory

	glDrawArrays(GL_TRIANGLES, 0, vertices_vector.size());

	// Flush created objects to the screen, i.e., force rendering.
	glutSwapBuffers();
	glutPostRedisplay();

	//!!!!
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 033:
	case 'q':
	case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}

// sprawdzenie i przygotowanie obslugi wybranych rozszerzen
void init()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char* version = (char*)glGetString(GL_VERSION);
	printf("%s", version);
	if ((version[0] < '1') || ((version[0] == '1') && (version[2] < '5')) || (version[1] != '.')) {
		printf("Bledny format wersji OpenGL\n");
		exit(0);
	}
	else {
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)wglGetProcAddress("glPatchParameteri");
		glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
		glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");

		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
		glMapBuffer = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	}
}


// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutCreateWindow("OGL 3");
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
	init();
	prepereBuffors();
	setShaders("vert.vs", "frag.fs");
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutMainLoop();

	// clean
	glDeleteBuffers(2, vbo);

	return 0;
}
