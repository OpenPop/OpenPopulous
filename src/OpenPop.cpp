
#include <windows.h>

#include "Input.h"
#include "OpenPop.h"
#include "Sprites.h"
#include "Video.h"
#include "Camera.h"

#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800								// We want our screen width 800 pixels
#define SCREEN_HEIGHT 600								// We want our screen height 600 pixels
#define SCREEN_DEPTH 16									// We want 16 bits per pixel

int pressed_button;

//camera object
Camera cam;

//Ted's ////////////////////////////////////

bool ready_to_quit;

void Initialization()
{
	InitVideo();

	//Load sprites
	LoadSpriteCollections();
}

void GameLoop()
{
	Uint32 last_tick = SDL_GetTicks();

	ready_to_quit = false;

	while (!ready_to_quit) {
		CheckInput();

		if (SDL_GetTicks() > last_tick + 70) {
			last_tick = SDL_GetTicks();

			TestDraw();
		}
	}
}

void Deinitalization()
{
	
}


void QuitGame()
{
	ready_to_quit = true;
}

//Ted's Main (Windows)
//
////int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
////{
////	Initialization();
////	GameLoop();
////	Deinitalization();
////}
//
//int main(){
//{
//	Initialization();
//	GameLoop();
//	Deinitalization();
//}


//Victor's Stuff

// stuff for lighting
GLfloat lAmbient[] = {0.3,0.3,0.3,1.0};
GLfloat lDiffuse[] = {1.0,1.0,1.0,1.0};
GLfloat lSpecular[] = {0.0,0.0,0.0,1.0};
GLfloat lPosition[] = {0.0,100.0,0.0,1.0};

// materials
GLfloat mSpecular[] = {1.0,1.0,1.0,1.0};
// the smaller the larger the specular area is
GLfloat mShininess[] = {128.0};

//colors
GLfloat cBlack[] = {0.0,0.0,0.0,1.0};
GLfloat cOrange[] = {1.0,0.5,0.5,1.0}; 
GLfloat cGreen[] = {0.2,0.7,0.2,1.0}; 
GLfloat cGrey[] = {0.1,0.1,0.1,1.0};
GLfloat cLightGrey[] = {0.9,0.9,0.9,1.0};




void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//terrainDL = terrainCreateDL(0,0,0);
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,lAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lDiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lSpecular);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

//	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    //init engine here
    //engine->init()?
    
	//set clear color
	glClearColor (1.0, 1.0, 1.0, 0.0);

	//enable z-buffer
    //glEnable (GL_DEPTH_TEST);

    //showCursor(false); //hide the cursor

	cam.setCam(10.0, 10.0, 10.0,
               0.0, 0.0, 0.0, 
               0.0, 1.0, 0.0);
}


/////////////////////////////////

void OrthoMode(int left, int top, int right, int bottom)
{
	// This function takes in rectangle coordinates for our 2D view port.
	// What happens below is, we need to change our projection matrix.  To do this,
	// we call glMatrixMode(GL_PROJECTION) to tell OpenGL the current mode we want.
	// Then we push on a new matrix so we can just call glPopMatrix() to return us
	// to our previous projection matrix, but first we will render in ortho mode.
	//  Next, we load a new identity matrix so that everything is initialize before
	// we go into ortho mode.  One we switch to ortho by calling glOrth(), we then
	// want to set our matrix mode to GL_MODELVIEW, which puts us back and ready to
	// render our world using the model matrix.  We also initialize this new model view
	// matrix for our 2D rendering before drawing anything.

	// Switch to our projection matrix so that we can change it to ortho mode, not perspective.
	glMatrixMode(GL_PROJECTION);						

	// Push on a new matrix so that we can just pop it off to go back to perspective mode
	glPushMatrix();									
	
	// Reset the current matrix to our identify matrix
	glLoadIdentity();								

	//Pass in our 2D ortho screen coordinates.like so (left, right, bottom, top).  The last
	// 2 parameters are the near and far planes.
	glOrtho( left, right, bottom, top, 0, 1 );	
	
	// Switch to model view so that we can render the scope image
	glMatrixMode(GL_MODELVIEW);								

	// Initialize the current model view matrix with the identity matrix
	glLoadIdentity();										
}


///////////////////////////////// PERSPECTIVE MODE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function changes our returns our projection mode from 2D to 3D
/////
///////////////////////////////// PERSPECTIVE MODE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void PerspectiveMode()										// Set Up A Perspective View
{
	// This function doesn't really go to perspective mode, since we aren't
	// using gluPerspective(), but if you look in OrthoMode(), we push on
	// a matrix once we change to our projection matrix.  All we need to do is
	// pop that matrix off of our stack and it will return to our original perspective
	// matrix.  So, before we pop the current matrix, we need to tell OpenGL which
	// matrix we want to use by changing our current matrix mode to perspective.
	// Then we can go back to our model view matrix and render normally.

	// Enter into our projection matrix mode
	glMatrixMode( GL_PROJECTION );							

	// Pop off the last matrix pushed on when in projection mode (Get rid of ortho mode)
	glPopMatrix();											

	// Go back to our model view matrix like normal
	glMatrixMode( GL_MODELVIEW );							

	// We should be in the normal 3D perspective mode now
}


void draw3D(){


	int num_segmentos=10;
	int _size=20;

	int i=0;
	int x_ini=_size/2;
	int z_ini=_size/2;


	glColor3f(1.0,0.0,0.3);

	for (i=0; i<=num_segmentos; i++){
		glBegin(GL_LINES);
			glVertex3f(-x_ini, 0.0, z_ini-(_size/num_segmentos)*i);
			glVertex3f(x_ini, 0.0, z_ini-(_size/num_segmentos)*i);
		glEnd();
	}

	for (i=0; i<=num_segmentos; i++){
		glBegin(GL_LINES);
			glVertex3f(x_ini-(_size/num_segmentos)*i, 0.0, -z_ini);
			glVertex3f(x_ini-(_size/num_segmentos)*i, 0.0, z_ini);
		glEnd();
	}

}


//display function
void display(void)
{

    int i=0;

	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightfv(GL_LIGHT0,GL_POSITION,lPosition);

    //store vis. matrix
    //	glPushMatrix();

	//locate cam correctly
    
	gluLookAt(cam.mPosition.x, cam.mPosition.y, cam.mPosition.z,	
			  cam.mView.x,	   cam.mView.y,     cam.mView.z,	
			  cam.mUp.x,       cam.mUp.y,       cam.mUp.z);

		
	glTranslatef(0.0, 0.0, 0.0);


    // Draw ground

	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS,mShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cGrey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cGreen);

	//glCallList(terrainDL); //call the terrain DL

	glDisable(GL_LIGHTING);
    //draw something (lightless)

	//without light
	draw3D();

    //now on 2D mode
	OrthoMode(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //draw 2D stuff here
	//engine->drawGui or whatever
	PerspectiveMode();

    glutSwapBuffers(); //swap the buffers - no glitches!
}


//when reshaping the window this is called
void reshape (int w, int h)
{

	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	// Volumen de visualización perspectivo
	gluPerspective (40.0, w/h, 1.0, 200.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


//inactivity
void idle()
{
	glutPostRedisplay ();
}

//función de teclado
void teclado (unsigned char key, int x, int y)
{
	switch (key) {

		case 'w':{
			cam.setOffset(0.0, 0.0, 0.1);
		break;}

		case's' :{
			cam.setOffset(0.0, 0.0, -0.1);
 		break;}
		
		case 'a':{
			cam.setOffset(0.1, 0.0, 0.0);
 		break;}
		
        case'd' :{
			cam.setOffset(-0.1, 0.0, 0.0);
		break;}


		case 27:{
			exit(-1);
		}

		}
}


void mouse (int button, int state, int x, int y)
{


	if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
	{
		pressed_button = 0;
	}


	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
	    pressed_button = 1;
	}
}

//main function
int StartOpenPop(int argc, char* argv[])
{

	// Inicializamos GLUT y su modo de funcionamiento
	glutInit (&argc, argv);

    //definimos el modo de visualización
	glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

	// Abrimos una ventana con su título
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("OpenPop");

//	if (terrainLoadFromImage("3dtech.tga",1) != TERRAIN_OK)
//		return(-1);
//	terrainScale(0,4); //scale terrain - min and max heights

	init ();

	// Registramos las funciones de respuesta
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc(teclado);
	glutIdleFunc (idle);
	glutMouseFunc(mouse);

	// Iniciamos el bucle infinito
	glutMainLoop ();
	return 0;
}


//old code

//#include <cstdio>
//
//#include "Language.h"
//#include "Sprites.h"
//
//int main()
//{
//	LoadLanguage();
//	LoadSpriteCollections();
//
//	for (int i = 0; i < 1000; i++) {
//		wprintf(L"%d. %s\n", i, GetString(i));
//	}
//
//	return 0;
//}
