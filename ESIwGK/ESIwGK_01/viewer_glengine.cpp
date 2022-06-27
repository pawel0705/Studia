/***********************************************************************
*	fACT
*	framework for Animation of virtual Characters in Three dimensions
*	TotalCompilation Library
***********************************************************************/

/*!
*  \file   viewer_glengine.cpp  
*  \brief  Definition of the class CglEngine
*  $Date:  2010/05/25$
*/


//--------------------------------------------------------------------------------------//
//	Includes
//--------------------------------------------------------------------------------------//

#include "viewer_glengine.hpp"

#ifdef _GLLIB_
//#define _JPEGLIB_

#include "obj3D.hpp"
#include "subobj3d.hpp"

#include "modelScene.hpp"

#include "GL\freeglut.h"
#include "tga.h"	


#ifdef _JPEGLIB_
#include <jpeglib.h>

#ifdef _DEBUG
#pragma comment (lib, "jpg_d.lib")
#else
#pragma comment (lib, "jpg.lib")
#endif

#endif

const int font=(int)GLUT_BITMAP_8_BY_13;
const int bitmapHeight=13;

//--------------------------------------------------------------------------------------//
//	Statics
//--------------------------------------------------------------------------------------//

//viewerParam CglEngine::vpar;
bool CglEngine::distance_height=false;


CglEngine::CglEngine(const char * name): 
CViewer(name)
{
	distance_height=false;
}

/*! 
*	\brief Initialize OpenGL and call main GL loop
*/
void CglEngine::main()
{
	glEnable(GL_LIGHTING);
	int argc=1;
	char *fake_argv[] =
	{
  "program",
   NULL};
 	
	char **argv = new char*[1];
	argv[0]=new char[35];
	strcpy(argv[0],"fACT.exe");

	
	glutInit(&argc, fake_argv);

   // register our own exit callback
  atexit(exitFunc);

 
  // set all GLUT modes
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(vpar.m_width, vpar.m_height);

  glutCreateWindow("fACT Cal3D-Gl Viever");
	

  if(vpar.m_bFullscreen) glutFullScreen();


  glutSetCursor(GLUT_CURSOR_NONE);

  // register all GLUT callback functions
  glutIdleFunc(CglEngine::idleFunc);
  glutMouseFunc(mouseFunc);
  glutMotionFunc(motionFunc);
  glutPassiveMotionFunc(motionFunc);
  glutReshapeFunc(reshapeFunc);
  glutDisplayFunc(displayFunc);
  glutKeyboardFunc(keyboardFunc);
  glutCloseFunc(closeWindowFunc);


  glutMainLoop();
	

  delete [] argv[0];
  delete [] argv;

 }

/*! 
*	\brief Render whole 3D scene 
*/
void CglEngine::displayFunc()
{
	vpar.viewer_run=1;
	//static long display_klatka=-1;
	if (m_frame==NULL) return;

	if(vpar.m_refreash==1)			 // refresh viewer only with new frame 
		if(display_klatka==*m_frame) return; 


	// clear the vertex and face counters
	vpar.m_vertexCount = 0;
	vpar.m_faceCount = 0;

	// clear all the buffers
	glClearColor(0.0f, 0.0f, 0.30f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLdouble)vpar.m_width / (GLdouble)vpar.m_height, vpar.m_scale * 50.0, vpar.m_scale * 1000.0);

	// set the model transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// light attributes
	const GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
	const GLfloat light_diffuse[]  = { 0.52f, 0.5f, 0.5f, 1.0f };
	const GLfloat light_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	// setup the light attributes
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// set the light position
	GLfloat lightPosition[] = { 0.0f, -1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// set camera position
	if(vpar.m_camera==_CAMERA_ACTIVE_EYE)
	{
		std::vector<CObj3D*> & bipedy= modelscene->getVectorObj3D();
		if(bipedy.empty())
			setCameraGlobal();

	}
	else //_CAMERA_GLOBAL
	{
		setCameraGlobal();
	}

	/*! Render characters */
	//renderCharacter();
	/*! Render 3D objects */
	block.lock();
	
	try{
		renderScene();
	}
	catch(...){	}
	
	block.unlock();
	/*! render cursor */
	renderCursor();
	/*! render number of frame */
	renderNrFrame();

	// swap the front- and back-buffer
	glutSwapBuffers();

	/*! Save screen shot if attribute viewer_save is true */
	if(vpar.save && display_klatka!=*m_frame)
		takeScreenShot();

	 display_klatka=*m_frame;
}

/*! 
*	 \brief Set global camera
*/
void CglEngine::setCameraGlobal()
{
	glTranslatef(-vpar.m_distance_width*vpar.m_scale, -vpar.m_distance_height*vpar.m_scale, -vpar.m_distance * vpar.m_scale);
	glRotatef(vpar.m_tiltAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(-(vpar.m_twistAngle-180), 0.0f, 0.0f, 1.0f);
	//glTranslatef(0.0f, 0.0f, 0.0f * vpar.m_scale);
}

/*!
 *  \brief Save OpenGL screen to jpg
 */
void CglEngine::takeScreenShot()
{
#ifdef _JPEGLIB_

	long int i=*m_frame;
	char number[10];
	if(i<10)
		sprintf(number,"000%d.jpg",i);
	else if (i<100)
		sprintf(number,"00%d.jpg",i);
	else if (i<1000)
		sprintf(number,"0%d.jpg",i);
	else
		sprintf(number,"%d.jpg",i);

	 unsigned char *imageData ;
	 
	 imageData = new unsigned char[ vpar.m_width * vpar.m_height * 3 +3] ;
	 
	 glReadPixels( 0, 0, vpar.m_width-1, vpar.m_height-1, GL_RGB, GL_UNSIGNED_BYTE, imageData ) ;
	 
	//  return imageData ;
	struct jpeg_compress_struct cinfo;
	/* This struct represents a JPEG error handler.  It is declared separately
	* because applications often want to supply a specialized error handler
	* (see the second half of this file for an example).  But here we just
	* take the easy way out and use the standard error handler, which will
	* print a message on stderr and call exit() if compression fails.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct jpeg_error_mgr jerr;
	/* More stuff */
	FILE * outfile;		/* target file */
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
	int row_stride;		/* physical row width in image buffer */

	/* Step 1: allocate and initialize JPEG compression object */

	/* We have to set up the error handler first, in case the initialization
	* step fails.  (Unlikely, but it could happen if you are out of memory.)
	* This routine fills in the contents of struct jerr, and returns jerr's
	* address which we place into the link field in cinfo.
	*/
	cinfo.err = jpeg_std_error(&jerr);
	/* Now we can initialize the JPEG compression object. */
	jpeg_create_compress(&cinfo);

	/* Step 2: specify data destination (eg, a file) */
	/* Note: steps 2 and 3 can be done in either order. */

	/* Here we use the library-supplied code to send compressed data to a
	* stdio stream.  You can also write your own code to do something else.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to write binary files.
	*/
	// std::string filename(".jpg");

	if ((outfile = fopen(number, "wb")) == NULL) {
	fprintf(stderr, "can't open %s\n",number);
	//exit(1);
	return;
	}
	jpeg_stdio_dest(&cinfo, outfile);

	/* Step 3: set parameters for compression */

	/* First we supply a description of the input image.
	* Four fields of the cinfo struct must be filled in:
	*/
	cinfo.image_width = vpar.m_width; 	/* image width and height, in pixels */
	cinfo.image_height = vpar.m_height;
	cinfo.input_components = 3;		/* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	/* Now use the library's routine to set default compression parameters.
	* (You must set at least cinfo.in_color_space before calling this,
	* since the defaults depend on the source color space.)
	*/
	jpeg_set_defaults(&cinfo);
	/* Now you can set any non-default parameters you wish to.
	* Here we just illustrate the use of quality (quantization table) scaling:
	*/
	//  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

	/* Step 4: Start compressor */

	/* TRUE ensures that we will write a complete interchange-JPEG file.
	* Pass TRUE unless you are very sure of what you're doing.
	*/
	jpeg_start_compress(&cinfo, TRUE);

	/* Step 5: while (scan lines remain to be written) */
	/*           jpeg_write_scanlines(...); */

	/* Here we use the library's state variable cinfo.next_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	* To keep things simple, we pass one scanline per call; you can pass
	* more if you wish, though.
	*/
	row_stride = vpar.m_width * 3;	/* JSAMPLEs per row in image_buffer */

	//while (cinfo.next_scanline < cinfo.image_height) {
	for(int i=vpar.m_height-1; i>-1; --i)
	{
	/* jpeg_write_scanlines expects an array of pointers to scanlines.
	 * Here the array is only one element long, but you could pass
	 * more than one scanline at a time if that's more convenient.
	 */
	row_pointer[0] = & imageData[i * row_stride];
	(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	//jpeg_write_raw_data(&cinfo,(JSAMPIMAGE)imageData,30);
	/* Step 6: Finish compression */

	jpeg_finish_compress(&cinfo);
	/* After finish_compress, we can close the output file. */
	fclose(outfile);

	/* Step 7: release JPEG compression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_compress(&cinfo);

	delete [] imageData;

#endif
 
}

/*! 
*	\brief Render the 3D object -Texture
*/
void CglEngine::renderObj3D_TEXTURE(CalVector * obb)
{
	glBegin(GL_QUAD_STRIP); 
	 glVertex3f(obb[4].x,obb[4].y,obb[4].z);
	 glVertex3f(obb[0].x,obb[0].y,obb[0].z);
	 
	 glVertex3f(obb[5].x,obb[5].y,obb[5].z);
	 glVertex3f(obb[1].x,obb[1].y,obb[1].z);

	 glVertex3f(obb[7].x,obb[7].y,obb[7].z);
	 glVertex3f(obb[3].x,obb[3].y,obb[3].z);

	 glVertex3f(obb[6].x,obb[6].y,obb[6].z);
	 glVertex3f(obb[2].x,obb[2].y,obb[2].z);

	 glVertex3f(obb[4].x,obb[4].y,obb[4].z);
	 glVertex3f(obb[0].x,obb[0].y,obb[0].z);
	glEnd(); 

	// Gorna sciana
	glBegin(GL_QUAD_STRIP); 
	 glVertex3f(obb[6].x,obb[6].y,obb[6].z);
	 glVertex3f(obb[4].x,obb[4].y,obb[4].z);

	 glVertex3f(obb[7].x,obb[7].y,obb[7].z);
	 glVertex3f(obb[5].x,obb[5].y,obb[5].z);
	glEnd(); 


	// Dolna sciana
	glBegin(GL_QUAD_STRIP); 
	 glVertex3f(obb[2].x,obb[2].y,obb[2].z);
	 glVertex3f(obb[0].x,obb[0].y,obb[0].z);
	 glVertex3f(obb[3].x,obb[3].y,obb[3].z);
	 glVertex3f(obb[1].x,obb[1].y,obb[1].z);
	glEnd();
}


/*! 
*	\brief Render the 3D object -Bounding volumes
*/
void CglEngine::renderObj3D_BV(CalVector * vectorBone)
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(vectorBone[0].x, vectorBone[0].y, vectorBone[0].z);
	glVertex3f(vectorBone[1].x, vectorBone[1].y, vectorBone[1].z);
	glVertex3f(vectorBone[3].x, vectorBone[3].y, vectorBone[3].z);
	glVertex3f(vectorBone[2].x, vectorBone[2].y, vectorBone[2].z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(vectorBone[6].x, vectorBone[6].y, vectorBone[6].z);
	glVertex3f(vectorBone[7].x, vectorBone[7].y, vectorBone[7].z);
	glVertex3f(vectorBone[3].x, vectorBone[3].y, vectorBone[3].z);
	glVertex3f(vectorBone[2].x, vectorBone[2].y, vectorBone[2].z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(vectorBone[5].x, vectorBone[5].y, vectorBone[5].z);
	glVertex3f(vectorBone[7].x, vectorBone[7].y, vectorBone[7].z);
	glVertex3f(vectorBone[6].x, vectorBone[6].y, vectorBone[6].z);
	glVertex3f(vectorBone[4].x, vectorBone[4].y, vectorBone[4].z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(vectorBone[5].x, vectorBone[5].y, vectorBone[5].z);
	glVertex3f(vectorBone[1].x, vectorBone[1].y, vectorBone[1].z);
	glVertex3f(vectorBone[0].x, vectorBone[0].y, vectorBone[0].z);
	glVertex3f(vectorBone[4].x, vectorBone[4].y, vectorBone[4].z);
	glEnd();

}

/*! 
*	\brief Render sphere of an object
*/
void CglEngine::renderSpheres(CObj3D* obj)
{
	CSubObj3D * Iter=NULL;
		
	size_t vectorSubobjSize=obj->getsubobjCount();
	
	for(size_t subId=0;subId<vectorSubobjSize;++subId)
	{
		Iter= obj->getsubobj(subId);

		if(!Iter->isshow()){ continue;}

		obj->calculateBoundingSpheres();
		
		glColor3f (0.0, 0.0, 0.0);

		glPushMatrix ();
		
		glTranslatef (obj->getsphereCentre(NULL).x, obj->getsphereCentre(NULL).y, obj->getsphereCentre(NULL).z);

		glutWireSphere( obj->getsphereRadius(NULL),10,10);

		glPopMatrix ();

	
	}

}


/*! 
*	\brief Render AABB of an object
*/
void CglEngine::renderAABB(CObj3D* obj)
{
	CSubObj3D * Iter=NULL;
		
	
	Iter= obj->getsubobj(0);

	if(!Iter->isshow()){ return;}

		OBB obb;
		maxMiny mm = obj->getMaxMin(NULL);
		OBBCreate(mm,obb);
		
		glLineWidth(1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);

		renderObj3D_BV(obb);
		
	
}

/*! 
*	\brief Render the 3D objects
*/
void CglEngine::renderScene()
{
	if (modelscene==NULL) return;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	modelscene->SetBoundingBoxes(-1);
	modelscene->SetBoundingBoxes(0);

	std::vector<CObj3D*> & scena = modelscene->getVectorObj3D();

	//std::vector<CObj3D*>::iterator Iterobj;

	for(int i=0;i <scena.size();++i)
	{
		if(scena[i]==NULL) continue;
		if(! scena[i]->isshow()) continue;
		
		
		if(vpar.face == SHOW_TEXTURE || vpar.face== SHOW_MESH)
		{
			scena[i]->setTexture();
			fACTRenderer *pRenderer = scena[i]->getRenderer();
			if(pRenderer!=NULL)
			{
				if(pRenderer->beginRendering())
				{
					if(vpar.face==SHOW_TEXTURE)
						renderCharacterTexture(pRenderer);
					else
						renderCharacterMesh(pRenderer);
				}

				if(vpar.viewer_render & ADDRENDER_SPHERE)
				{
					renderSpheres(scena[i]);
				}
				if(vpar.viewer_render & ADDRENDER_AABB)
				{
					renderAABB(scena[i]);
				}
				continue;
			}
		}

		CSubObj3D * Iter=NULL;
		size_t vectorSubobjSize=scena[i]->getsubobjCount();
		for(size_t subId=0;subId<vectorSubobjSize;++subId)
		{
			Iter=scena[i]->getsubobj(subId);
			if(!Iter->isshow()) continue;

			switch(vpar.face)
			{
			case SHOW_TEXTURE:
				{
					glColor3f(Iter->getcolour().red/256.f, Iter->getcolour().green/256.f, Iter->getcolour().blue/256.f);
					OBB vectorBone;
					scena[i]->getBoundingBox(subId,vectorBone);
					renderObj3D_TEXTURE(vectorBone);
					break;
				}
			case SHOW_MESH:
				{
					glLineWidth(1.0f);
					glColor3f(1.0f, 1.0f, 1.0f);

					OBB vectorBone;
					scena[i]->getBoundingBox(subId,vectorBone);
					renderObj3D_BV(vectorBone);
					
					glBegin(GL_LINE_LOOP);
					glVertex3f(vectorBone[1].x, vectorBone[1].y, vectorBone[1].z);
					glVertex3f(vectorBone[2].x, vectorBone[2].y, vectorBone[2].z);
					glVertex3f(vectorBone[7].x, vectorBone[7].y, vectorBone[7].z);
					glVertex3f(vectorBone[4].x, vectorBone[4].y, vectorBone[4].z);
					glEnd();
					glBegin(GL_LINES);
					glVertex3f(vectorBone[1].x, vectorBone[1].y, vectorBone[1].z);
					glVertex3f(vectorBone[7].x, vectorBone[7].y, vectorBone[7].z);
					glVertex3f(vectorBone[2].x, vectorBone[2].y, vectorBone[2].z);
					glVertex3f(vectorBone[4].x, vectorBone[4].y, vectorBone[4].z);
					glEnd();
			
					break;
				}
			case SHOW_BV:
				{
					glLineWidth(1.0f);
					glColor3f(1.0f, 1.0f, 1.0f);

					OBB vectorBone;
					scena[i]->getBoundingBox(subId,vectorBone);
					renderObj3D_BV(vectorBone);
					break;
				}
			case SHOW_LINES:
			case SHOW_LINES_POINTS:
			  {
				int parentId = Iter->getParentId();
				if(parentId != -1)
				{
					glBegin(GL_LINES);
					CalVector translation = scena[i]->getsubobj(parentId)->getTranslationAbsolute();
					glVertex3f(translation.x,translation.y,translation.z);
					translation = Iter->getTranslationAbsolute();
					glVertex3f(translation.x,translation.y,translation.z);
					glEnd();
				}
				if(vpar.face==2)
					break;
			  }
			case SHOW_POINTS:
			  {
				glPointSize(4.0f);
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 1.0f);
				
				CalVector tab=Iter->getTranslationAbsolute();
				glVertex3f(tab.x,tab.y,tab.z);
				glEnd();
				break;
			  }
			}
		}  
	}
}

/*!
*	\brief Render number of animation frame
*/
void CglEngine::renderNrFrame()
{
	  setOrthographicProjection();
	  // invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, (GLdouble)-vpar.m_height, 0);

	 glColor3f(0.0f,1.0f,1.0f);
	 char text[10];
	 MiscFun::Convert::int2char(*m_frame,text);
	 renderBitmapString(30,30,(void *)font,text);
}

/*! 
*	\brief Render the cursor
*/
void CglEngine::renderCursor()
{
  setOrthographicProjection();

  // render the cursor
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex2i(vpar.m_mouseX, vpar.m_mouseY);
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glVertex2i(vpar.m_mouseX + 16, vpar.m_mouseY - 32);
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glVertex2i(vpar.m_mouseX + 32, vpar.m_mouseY - 16);
  glEnd();

  glDisable(GL_BLEND);
}

/*! 
*	\brief Render the character (Biped) - SHOW_TEXTURE
*/
void CglEngine::renderCharacterTexture(fACTRenderer *pCalRenderer)
{
	// set global OpenGL states
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// we will use vertex arrays, so enable them
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// get the number of meshes
	int meshCount;
	meshCount = pCalRenderer->getMeshCount();

	// render all meshes of the model
	int meshId;
	for(meshId = 0; meshId < meshCount; meshId++)
	{
	  // get the number of submeshes
	  int submeshCount;
	  submeshCount = pCalRenderer->getSubmeshCount(meshId);

	  // render all submeshes of the mesh
	  int submeshId;
	  for(submeshId = 0; submeshId < submeshCount; submeshId++)
	  {
		// select mesh and submesh for further data access
		if(pCalRenderer->selectMeshSubmesh(meshId, submeshId))
		{
		  unsigned char meshColor[4];
		  GLfloat materialColor[4];

		  // set the material ambient color
		  pCalRenderer->getAmbientColor(&meshColor[0]);
		  materialColor[0] = meshColor[0] / 255.0f;  
		  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

		  // set the material diffuse color
		  pCalRenderer->getDiffuseColor(&meshColor[0]);
		  materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

			// set the vertex color if we have no lights
			//if(!bLight){glColor4fv(materialColor);}

		  // set the material specular color
		  pCalRenderer->getSpecularColor(&meshColor[0]);
		  materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		  glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

		  // set the material shininess factor
		  float shininess;
		  shininess = 50.0f; //pCalRenderer->getShininess();
		  glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		  // get the transformed vertices of the submesh
		  static float meshVertices[30000][3];
		  int vertexCount;
		  vertexCount = pCalRenderer->getVertices(&meshVertices[0][0]);

		  // get the transformed normals of the submesh
		  static float meshNormals[30000][3];
		  pCalRenderer->getNormals(&meshNormals[0][0]);

		  // get the texture coordinates of the submesh
		  static float meshTextureCoordinates[30000][2];
		  int textureCoordinateCount;
		  textureCoordinateCount = pCalRenderer->getTextureCoordinates(0, &meshTextureCoordinates[0][0]);

		  // get the faces of the submesh
		  static int meshFaces[50000][3];
		  int faceCount;
		  faceCount = pCalRenderer->getFaces(&meshFaces[0][0]);

		  // set the vertex and normal buffers
		  glVertexPointer(3, GL_FLOAT, 0, &meshVertices[0][0]);
		  glNormalPointer(GL_FLOAT, 0, &meshNormals[0][0]);

		  // set the texture coordinate buffer and state if necessary
		  if((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
		  {
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_COLOR_MATERIAL);

			// set the texture id we stored in the map user data
			glBindTexture(GL_TEXTURE_2D, (GLuint)pCalRenderer->getMapUserData(0));

			// set the texture coordinate buffer
			glTexCoordPointer(2, GL_FLOAT, 0, &meshTextureCoordinates[0][0]);
			glColor3f(1.0f, 1.0f, 1.0f);
		  }

		  // draw the submesh
		  if(sizeof(int)==2)
			  glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_SHORT, &meshFaces[0][0]);
		  else
			  glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, &meshFaces[0][0]);

		  // disable the texture coordinate state if necessary
		  if((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
		  {
			glDisable(GL_COLOR_MATERIAL);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
		  }

		  // adjust the vertex and face counter
		  vpar.m_vertexCount += vertexCount;
		  vpar.m_faceCount += faceCount;

		}
	  }
	}

	// clear vertex array state
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// clear light
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

	// end the rendering
	pCalRenderer->endRendering();
}


/*! 
*	\brief Render the character (Biped) - SHOW_TEXTURE
*/
void CglEngine::renderCharacterMesh(fACTRenderer *pCalRenderer)
{
	// set global OpenGL states
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	// get the number of meshes
	int meshCount;
	meshCount = pCalRenderer->getMeshCount();

	// render all meshes of the model
	
	int meshId;
	for(meshId = 0; meshId < meshCount; meshId++)
	{
	  // get the number of submeshes
	  int submeshCount;
	  submeshCount = pCalRenderer->getSubmeshCount(meshId);

	  // render all submeshes of the mesh
	  int submeshId;
	  for(submeshId = 0; submeshId < submeshCount; submeshId++)
	  {
		// select mesh and submesh for further data access
		if(pCalRenderer->selectMeshSubmesh(meshId, submeshId))
		{
		  // get the transformed vertices of the submesh
		  static float meshVertices[30000][3];
		  int vertexCount;
		  vertexCount = pCalRenderer->getVertices(&meshVertices[0][0]);

		  // get the faces of the submesh
		  static int meshFaces[50000][3];
		  int faceCount;
		  faceCount = pCalRenderer->getFaces(&meshFaces[0][0]);



		 // draw the submesh
		  for(int i=0;i< faceCount;++i)
		  {
			glBegin(GL_LINES);
			glVertex3f(meshVertices[meshFaces[i][0]][0],meshVertices[meshFaces[i][0]][1],meshVertices[meshFaces[i][0]][2]);
			glVertex3f(meshVertices[meshFaces[i][1]][0],meshVertices[meshFaces[i][1]][1],meshVertices[meshFaces[i][1]][2]);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(meshVertices[meshFaces[i][1]][0],meshVertices[meshFaces[i][1]][1],meshVertices[meshFaces[i][1]][2]);
			glVertex3f(meshVertices[meshFaces[i][2]][0],meshVertices[meshFaces[i][2]][1],meshVertices[meshFaces[i][2]][2]);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(meshVertices[meshFaces[i][2]][0],meshVertices[meshFaces[i][2]][1],meshVertices[meshFaces[i][2]][2]);
			glVertex3f(meshVertices[meshFaces[i][0]][0],meshVertices[meshFaces[i][0]][1],meshVertices[meshFaces[i][0]][2]);
			glEnd();

		  }
		
		  // adjust the vertex and face counter
		  vpar.m_vertexCount += vertexCount;
		  vpar.m_faceCount += faceCount;

		}
	  }
	}
	// clear vertex array state
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// clear light
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

	// end the rendering
	pCalRenderer->endRendering();
}

/*! 
*	\brief Render the character (Biped)
*/
void CglEngine::renderCharacter()
{
	std::vector<CObj3D*> & objs= modelscene->getVectorObj3D();

	if(objs.empty())
	  return;
	
	// the renderer of the model
	fACTRenderer *pCalRenderer;

	//Biped *biped;
	CObj3D * biped;
	for(int i=0; i<objs.size();++i)
	{
		if(objs[i]==NULL) continue;
		
		if(!objs[i]->isactive()) continue;
		
		if(!objs[i]->isshow()) continue;
		
		//biped = dynamic_cast<Biped *>(objs[i]);

		biped=objs[i];

		if(biped==NULL) continue;

		biped->setTexture();

		if(objs[i]==NULL) continue;

		pCalRenderer = biped->getRenderer();

		switch(vpar.face)
		{
			case SHOW_TEXTURE:
			{
				if(pCalRenderer->beginRendering())
				  renderCharacterTexture(pCalRenderer);
				break;
			}
			case SHOW_BV:
			{
				//renderCharacterBV(biped);
				break;
			}
			case SHOW_LINES: 
			case SHOW_LINES_POINTS:
			{
				/*renderCharacterLine(biped);
				if(vpar.face==2) */
					break;
			}
			case SHOW_POINTS:
			{
				//renderCharacterPOINTS(biped);
				break;
			}
		}
	}
}

/*!
*	\brief Called
*/
void CglEngine::mouseFunc(int button, int state, int x, int y)
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
		
		displayFunc();
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
			displayFunc();
	}
}

/*!	
	\brief Set new width and height 
*/
void CglEngine::reshapeFunc(int width, int height)
{
	vpar.m_width = width;
	vpar.m_height = height;
	 glViewport(0, 0, vpar.m_width, vpar.m_height);
}

/*!	
	\brief Called when nothing happened
*/
void CglEngine::idleFunc()
{
	if (m_frame==NULL) return;
	static long k=-1;
	if(k!=*m_frame){
		k=*m_frame;
		glutPostRedisplay();
	}
}


/*!
*	 \brief Called when keyboard key is pressed
*/
void CglEngine::keyboardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
		// test for quit event
		case 27:
		case 'q':
		case 'Q':
			glutLeaveMainLoop();
			break;
		case 'H':
		case 'h':
			 distance_height=!distance_height;
			 break;
		case 'a':
		case 'A':
			vpar.viewer_render = vpar.viewer_render ^ 2;
			break;
		case 's':
		case 'S':
			vpar.viewer_render = vpar.viewer_render ^ 1;
			break;
							
	}
}

/*!
*	\brief Called when mouse was moved
*/
void CglEngine::motionFunc(int x, int y)
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
		// calculate new distance
		if(distance_height)
			 vpar.m_distance_height -= (float)(y - vpar.m_mouseY) / 3.0f;
		else
		{
			vpar.m_distance -= (float)(y - vpar.m_mouseY) / 3.0f;
			if(vpar.m_distance < 0.0f) vpar.m_distance = 0.0f;
		}

		vpar.m_distance_width-= (float)(x - vpar.m_mouseX) / 3.0f;
   }

	// update internal mouse position
	vpar.m_mouseX = x;
	 vpar.m_mouseY = y;
	displayFunc();
  
}




void CglEngine::setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	  glOrtho(0, (GLdouble)vpar.m_width, 0, (GLdouble)vpar.m_height, -1.0f, 1.0f);

//// invert the y axis, down is positive
//	glScalef(1, -1, 1);
//	// mover the origin from the bottom left corner
//	// to the upper left corner
//	glTranslatef(0, (GLdouble)-vpar.m_height, 0);

	  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	}

void CglEngine::renderBitmapString(float x, float y, void *font,char *string)
{
  
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void CglEngine::renderSpacedBitmapString(float x, float y,int spacing, void *font,char *string) {
  char *c;
  int x1=x;
  for (c=string; *c != '\0'; c++) {
	glRasterPos2f(x1,y);
    glutBitmapCharacter(font, *c);
	x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  }
}


void CglEngine::renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font,char *string)
{
  
  char *c;
  int i;
  for (c=string,i=0; *c != '\0'; i++,c++) {
	glRasterPos2f(x, y+bitmapHeight*i);
    glutBitmapCharacter(font, *c);
  }
}


/*! 
*	\brief Close visualisation window  
*/
void CglEngine::closeView()
{
	while(vpar.viewer_run==0);
	glutLeaveMainLoop();
}

/*! 
*	\brief Call when window is closed
*/
void CglEngine::closeWindowFunc()
{
	glutLeaveMainLoop();
}


/*! 
*  \brief Load and create texture from a given file for OpenGl
*  \param strFilename Name of file with information about texture
*  \return texture id for OpenGl
*/
int CglEngine::loadTexture(const std::string& strFilename)
{
  GLuint pId = 0;

  if (stricmp(strrchr(strFilename.c_str(),'.'),".raw")==0)
  {

    // open the texture file
    std::ifstream file;
    file.open(strFilename.c_str(), std::ios::in | std::ios::binary);
    if(!file)
    {
      std::cerr << "Texture file '" << strFilename << "' not found." << std::endl;
      return _fACT_ERROR;
    }

    // load the dimension of the texture
    int width;
    file.read((char *)&width, 4);
    int height;
    file.read((char *)&height, 4);
    int depth;
    file.read((char *)&depth, 4);

    // allocate a temporary buffer to load the texture to
    unsigned char *pBuffer;
    pBuffer = new unsigned char[width * height * depth];
    if(pBuffer == 0)
    {
      std::cerr << "Memory allocation for texture '" << strFilename << "' failed." << std::endl;
      return _fACT_ERROR;
    }

    // load the texture
    file.read((char *)pBuffer, width * height * depth);

    // explicitely close the file
    file.close();

    // generate texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &pId);
    glBindTexture(GL_TEXTURE_2D, pId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, (depth == 3) ? GL_RGB : GL_RGBA, width, height, 0, (depth == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, &pBuffer[0]);
  
    // free the allocated memory
    delete [] pBuffer;
  
  }
  else if (stricmp(strrchr(strFilename.c_str(),'.'),".tga")==0)
  {

    CTga *Tga;
    Tga = new CTga();

    //Note: This will always make a 32-bit texture
    if(Tga->ReadFile(strFilename.c_str())==0)
    {
      Tga->Release();
	  delete Tga;
      return false;
    }

    //Bind texture
    int width = Tga->GetSizeX();
    int height = Tga->GetSizeY();
    int depth = Tga->Bpp() / 8;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &pId);
      
    glBindTexture(GL_TEXTURE_2D, pId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
    glTexImage2D(GL_TEXTURE_2D, 0, ((depth == 3) ? GL_RGB : GL_RGBA), width, height, 0, ((depth == 3) ? GL_RGB : GL_RGBA) , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

	 Tga->Release();
	 delete Tga;
  }


  return pId;
}






#endif