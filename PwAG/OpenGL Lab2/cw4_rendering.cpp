//Laboratorium 4
//Modelowanie sceny w OpenGL

//Zadania:
// 1) - dodac do sceny blyszczaca czerwona sfere z rozblyskiem
// 2) --> ustawic oswietlenie - dwa zrodla swiatla (0 (kierunkowe): AMBIENT, DIFFUSE, 1 (punktowe): SPECULAR)
// 3) --> ustawic parametry materialu

// 4)  - szescian z nalozona tekstura (na ka¿d¹ scianê)
// 5) --> ustawic uwzglednianie oswietlenia na teksturze 
// 6)  - dodaæ obiekt sfery reprezentujacy punktowe zrodlo swiatla (zrodlo swiatla numer 1)
// 7) - dodaæ sfere z nalozona tekstur¹ 

#include <iostream>
#include <fstream>

#define GLUT_DISABLE_ATEXIT_HACK

#include "GL/glut.h"

using namespace std;


static float zMove = 0.0;
static float xRot = 0.0;
static float yRot = 0.0;
static unsigned int texture[2]; // indeksy tekstur.

// Struktura dla pliku bitmapy.
struct BitMapFile
{
	int sizeX;
	int sizeY;
	unsigned char* data;
};

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile* getBMPData(string filename)
{
	BitMapFile* bmp = new BitMapFile;
	unsigned int size, offset, headerSize;

	// Read input file name.
	ifstream infile(filename.c_str(), ios::binary);

	// Get the starting point of the image data.
	infile.seekg(10);
	infile.read((char*)&offset, 4);

	// Get the header size of the bitmap.
	infile.read((char*)&headerSize, 4);

	// Get width and height values in the bitmap header.
	infile.seekg(18);
	infile.read((char*)&bmp->sizeX, 4);
	infile.read((char*)&bmp->sizeY, 4);

	// Allocate buffer for the image.
	size = bmp->sizeX * bmp->sizeY * 24;
	bmp->data = new unsigned char[size];

	// Read bitmap data.
	infile.seekg(offset);
	infile.read((char*)bmp->data, size);

	// Reverse color from bgr to rgb.
	int temp;
	for (int i = 0; i < size; i += 3)
	{
		temp = bmp->data[i];
		bmp->data[i] = bmp->data[i + 2];
		bmp->data[i + 2] = temp;
	}

	return bmp;
}

// Zaladowanie tekstury.
void loadExternalTextures()
{
	BitMapFile* image[2];

	// Zaladownie tekstu z plikow.
	image[0] = getBMPData("Textures/grass.bmp");
	image[1] = getBMPData("Textures/sky.bmp");

	//tekstura grass 
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//ToDo - ustawienie parametrow tekstury glTexParametri 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);

	//tekstura sky
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	//ToDo - ustawienie parametrow tekstury glTexParametri 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
}

//inicjalizacja
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING); //To trzeba wlaczyc!!!

	//ToDo - ustawienie parametrow oswietlenia dla dwoch zrodel swiatla

	// swiatlo 0 - directional
	GLfloat directional[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, directional);
	GLfloat matDefaultAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, matDefaultAmb);
	GLfloat matDefaultDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, matDefaultDiffuse);
	GLfloat matNoSpec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, matNoSpec);

	float lightPosition0[] = { 10.0f, 15.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	glEnable(GL_LIGHT0); // wlaczenie swiatla 0

	// swiatlo 1 - point
	GLfloat point[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, point);
	GLfloat matPointLightSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, matPointLightSpec);
	
	float lightPos1[] = { -15.0f, -5.0f, -25.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glEnable(GL_LIGHT1); // wlaczenie swiatla 1

	//Tekstury
	glGenTextures(2, texture);

	loadExternalTextures();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

//Rysowanie sceny
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	#pragma region Czerwona sfera

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	//  glColor3f(1.0, 0.0, 0.0);//tylko zeby sie cos pojawilo
	glTranslatef(1.5, 0.0, zMove);

	//ToDo - ustawic parametry materialu dla sfery - czerwona z rozblyskiem
	GLfloat matRedSphereAmbient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRedSphereAmbient);
	GLfloat matRedSphereDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRedSphereDiffuse);
	GLfloat matRedSphereSpecular[] = { 0.65f, 0.65f, 0.65f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, matRedSphereSpecular);
	GLfloat matRedSphereShiness[] = { 16.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, matRedSphereShiness);
	GLfloat matRedSphereEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, matRedSphereEmission);
	glutSolidSphere(1.25, 100, 100);

	#pragma endregion

	#pragma region Sfera - swiatlo punktowe

	//ToDo - dodac sfere reprezentujaca polozenie swiatla punktowego o numerze 1 
	//ToDo - zdefiniowac material dla swiecacej sfery (GL_EMISSION)
	glLoadIdentity();

	GLfloat lightSphereDiffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightSphereSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightSphereEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, lightSphereDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSphereSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, lightSphereEmission);

	glTranslatef(-15.0f, -5.0f, -25.0f);
	glutSolidSphere(0.5f, 100, 100);

	#pragma endregion

	#pragma region Kostka
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glTranslatef(1.5, 0.0, zMove);
	glTranslatef(-2.5, 0.0, 0.0);

	
	glEnable(GL_TEXTURE_2D);
	//ToDo - obsluga tekstury dla szescianu
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	float s = 1.0;
	glBegin(GL_QUADS);
		//Sciana przednia
		glNormal3f(0.0f, 0.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-s, -s, s);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(s, -s, s);
		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(s, s, s);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-s, s, s);

		//Sciana tylna 
		glNormal3f(0.0f, 0.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-s, -s, -s);
		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-s, s, -s);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(s, s, -s);
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(s, -s, -s);

		//Sciana gorna
		glNormal3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-s, s, -s);
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-s, s, s);
		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(s, s, s);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(s, s, -s);

		//Sciana dolna
		glNormal3f(0.0f, -1.0f, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-s, -s, -s);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(s, -s, -s);
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(s, -s, s);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-s, -s, s);

		//Prawa sciana
		glNormal3f(1.0f, 0.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(s, -s, -s);
		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(s, s, -s);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(s, s, s);
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(s, -s, s);

		//Lewa sciana
		glNormal3f(-1.0f, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-s, -s, -s);
		glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-s, -s, s);
		glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-s, s, s);
		glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-s, s, -s);
	glEnd();
	
	#pragma endregion

	#pragma region Sfera - tekstura

	glLoadIdentity();

	glTranslatef(0.0, 0.0, -10.0);

	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);

	glTranslatef(0.5, 2.0, zMove);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glutSolidSphere(1.0, 100, 100);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	#pragma endregion

	//ToDo - dodac sfere z nalozona tekstutra
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}


void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (float)w / (float)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) zMove -= 0.1;
	if (key == GLUT_KEY_DOWN) if (zMove < 3.0) zMove += 0.1;

	if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

	if (xRot > 356.0f) xRot = 0.0f;
	if (xRot < -1.0f) xRot = 355.0f;
	if (yRot > 356.0f) yRot = 0.0f;
	if (yRot < -1.0f) yRot = 355.0f;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL - Laboratorium 4");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	glutSpecialFunc(specialKeyInput);
	glutMainLoop();

	return 0;
}
