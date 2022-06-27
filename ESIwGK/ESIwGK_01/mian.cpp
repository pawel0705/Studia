/*
	ESIwGK
	Wyszukiwanie Drogi (A*) + Mapa Wp³ywów
*/

#include <iostream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

#include "map.h" 

#define MAPA "map6"			//"map6"
#define WROG "units4"
#define CONF "conf06"


typedef struct{
  int m_width;
  int m_height;
  int m_mouseX;
  int m_mouseY;
  float m_tiltAngle;
  float m_twistAngle;
  float m_distance;
  float m_distance_height;
  float m_distance_width;
  bool m_bLeftMouseButtonDown;
  bool m_bRightMouseButtonDown;
 }viewerParam;



viewerParam vpar;

int width = 0;
int height = 0;
short BitsPerPixel = 0;
Map *map=NULL;
bool findpath = false;







void LoadBitmap(const char* FilePath, std::vector<unsigned char>& Pixels)
{
	std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
	if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");

	hFile.seekg(0, std::ios::end);
	int Length = hFile.tellg();
	hFile.seekg(0, std::ios::beg);
	std::vector<std::uint8_t> FileInfo(Length);
	hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);

	if (FileInfo[0] != 'B' && FileInfo[1] != 'M')
	{
		hFile.close();
		throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
	}

	if (FileInfo[28] != 24 && FileInfo[28] != 32)
	{
		hFile.close();
		throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
	}

	BitsPerPixel = FileInfo[28];
	width = FileInfo[18] + (FileInfo[19] << 8);
	height = FileInfo[22] + (FileInfo[23] << 8);
	std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
	std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
	Pixels.resize(size);

	hFile.seekg(PixelsOffset, std::ios::beg);
	hFile.read(reinterpret_cast<char*>(Pixels.data()), size);
	hFile.close();
}

void test(string strmap, string strunits, string strconfig)
{
	map =new Map(strunits + ".txt", strconfig + ".txt");
	GLuint hmap;
	LoadBitmap((strmap + ".bmp").c_str(), map->Pixels);
	glGenTextures(1, &hmap);
	glBindTexture(GL_TEXTURE_2D, hmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, map->Pixels.data());

	clock_t start = clock();

	map->createIMap();

	string str = map->path();
	cout << endl << "Path: " << str << endl;
	cout << "Path lenght: " << map->pathLenght(str) << endl;
	map->drawPath(str);

	findpath = true;
}


// Drawing (display) routine.
void drawScene(void)
{
	GLuint hmap;
	if (map != NULL)
	{
		glGenTextures(1, &hmap);
		glBindTexture(GL_TEXTURE_2D, hmap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, map->imapPixels.data());
	}
	glEnable (GL_LIGHTING);
 
	glClearColor(1.0f, 1.0f, 1.0f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);	

	glEnable (GL_LIGHT0);

	glEnable (GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0f, (GLdouble)vpar.m_width / (GLdouble)vpar.m_height, 10.0, 1000.0);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-vpar.m_distance_width, -vpar.m_distance_height, -vpar.m_distance);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(0, 150, 0);

	glTexCoord2f(0, 1); glVertex3f(200, 150, 0);

	glTexCoord2f(1, 1); glVertex3f(200, -50, 0); //glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0); glVertex3f(0, -50, 0);
	glEnd();

	if (map != NULL)
	{
		glGenTextures(1, &hmap);
		glBindTexture(GL_TEXTURE_2D, hmap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, map->Pixels.data());
	}
	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLdouble)vpar.m_width / (GLdouble)vpar.m_height, 10.0, 1000.0);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-vpar.m_distance_width, -vpar.m_distance_height, -vpar.m_distance);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-200, 150, 0); //glVertex3f(0, -200, 0);

	glTexCoord2f(0, 1); glVertex3f(0, 150, 0);

	glTexCoord2f(1, 1); glVertex3f(0, -50, 0); //glVertex3f(-200, 0, 0);

	glTexCoord2f(1, 0); glVertex3f(-200, -50, 0);
	glEnd();

   glFlush(); 
  glutSwapBuffers();
}



// Initialization routine.
void setup(void) 
{
	

  vpar.m_width = 800;
  vpar.m_height = 600;
  vpar.m_mouseX = 0;
  vpar.m_mouseY = 0;
  vpar.m_tiltAngle = -70.0f;//-99.0f;
  vpar.m_twistAngle = -45.0f;//236.0f;
  vpar.m_distance = 400.0f;//270.0f;
  vpar.m_distance_width=0.f;
  vpar.m_distance_height=0.f;
  vpar.m_bLeftMouseButtonDown = false;
  vpar.m_bRightMouseButtonDown = false;


}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   // Set viewport size to be entire OpenGL window.
	vpar.m_width = w;
	vpar.m_height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
   // Set matrix mode to projection.
   glMatrixMode(GL_PROJECTION);

   // Clear current projection matrix to identity.
   glLoadIdentity();

   // Specify the orthographic (or perpendicular) projection, 
   // i.e., define the viewing box.
	glOrtho(0, (GLdouble)vpar.m_width, 0, (GLdouble)vpar.m_height, -1.0f, 1.0f);
  //glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0); 

   // Set matrix mode to modelview.
   glMatrixMode(GL_MODELVIEW);

   // Clear current modelview matrix to identity.
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  
}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{

		// update mouse button states
		if(button == GLUT_LEFT_BUTTON)
		{
			vpar.m_bLeftMouseButtonDown = true;
		}

		if(button == GLUT_RIGHT_BUTTON)
		{
			vpar.m_bRightMouseButtonDown = true;
		}

		// update internal mouse position
		vpar.m_mouseX = x;
		vpar.m_mouseY = y;
		
		glutPostRedisplay();
	}
	else if(state == GLUT_UP)
	{
		
		// update mouse button states
			if(button == GLUT_LEFT_BUTTON)
			{
				vpar.m_bLeftMouseButtonDown = false;
			}

			if(button == GLUT_RIGHT_BUTTON)
			{
				vpar.m_bRightMouseButtonDown = false;
			}

			// update internal mouse position
			vpar.m_mouseX = x;
			vpar.m_mouseY = y;
		glutPostRedisplay();
	}

}

/*!
*	\brief Called when mouse was moved
*/
void motionFunc(int x, int y)
{
	y=vpar.m_height -y-1;

	if(vpar.m_bLeftMouseButtonDown)
	{
		// calculate new angles
		vpar.m_twistAngle += (float)(vpar.m_mouseX-x);
		vpar.m_tiltAngle -= (float)(y - vpar.m_mouseY);
	}

	// update distance
	if(vpar.m_bRightMouseButtonDown)
	{
			vpar.m_distance -= (float)(y - vpar.m_mouseY) / 3.0f;
			if(vpar.m_distance < 0.0f) vpar.m_distance = 0.0f;
	
		vpar.m_distance_width-= (float)(x - vpar.m_mouseX) / 3.0f;
   }

	// update internal mouse position
	vpar.m_mouseX = x;
	 vpar.m_mouseY = y;
	glutPostRedisplay();
  
}

void animate(int value) {

	test(MAPA, WROG, CONF);
//	if (!findpath)
//		glutTimerFunc(100, animate, 1);
	glutPostRedisplay();
}


// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  
	srand (time(NULL));

	
   // Initialize GLUT.
   glutInit(&argc, argv);
 
   // Set display mode as single-buffered and RGB color.
  // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

   // inicjalizacja bufora ramki
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   
   // Set OpenGL window size.
   glutInitWindowSize(800, 600);

   // Set position of OpenGL window upper-left corner.
   glutInitWindowPosition(100, 100); 
   
   // Create OpenGL window with title.
   glutCreateWindow("ESIwGK - Wyszukiwanie Drogi(A*) + Mapa Wp³ywów");
   
   // Initialize.
   setup(); 
   
   // Register display routine.
   glutDisplayFunc(drawScene); 
   
   // Register reshape routine.
   glutReshapeFunc(resize);  
   

   // Register the mouse and keyboard callback function. 
   glutMouseFunc(mouseControl); 
   glutMotionFunc(motionFunc);
   glutKeyboardFunc(keyInput);

   glutTimerFunc(5, animate, 1);
   
   // Begin processing.
   glutMainLoop(); 

    return 0;
}

