#include <sdl/sdl.h>
#include <sdl/sdl_opengl.h>

#include "Sprites.h"
#include "Video.h"

SDL_Surface *main_screen;
int test_draw_cnt = 0;

bool InitVideo()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		//return false;
	}



	main_screen = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL  | SDL_GL_DOUBLEBUFFER | SDL_HWSURFACE);
	if (main_screen == NULL) {
		return false;
	}

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)640/480, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return true;
}

void TestDraw()
{
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(-1.5f,0.0f,-100.0f);					// Move Left 1.5 Units And Into The Screen 6.0

	glColor3f(255, 0, 0);

	glBegin(GL_TRIANGLES);						// Drawing Using Triangles
	glVertex3f( 0.0f, 1.0f, 0.0f);				// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
	glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
	glEnd();									// Finished Drawing The Triangle

	glTranslatef(3.0f,0.0f,0.0f);					// Move Right 3 Units

	glBegin(GL_QUADS);						// Draw A Quad
	glVertex3f(-1.0f, 1.0f, 0.0f);				// Top Left
	glVertex3f( 1.0f, 1.0f, 0.0f);				// Top Right
	glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
	glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
	glEnd();							// Done Drawing The Quad


	GLuint texID = 0;
	int r = 0,
		g = 255,
		b = 0,
		a = 255;

	//allocate a texture name
	glGenTextures(1, &texID);

	//select our current texture
	glBindTexture(GL_TEXTURE_2D, texID);

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;
	
	surface = SDL_LoadBMP("C:\\Users\\Ted\\Pictures\\BIG SCORE.bmp");

	// get the number of channels in the SDL surface
	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nOfColors == 3)     // no alpha channel
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}


	glTexImage2D( GL_TEXTURE_2D, 0, 32, surface->w, surface->h, 0,
		texture_format, GL_UNSIGNED_BYTE, surface->pixels );


	// Setting orthographic projection.  
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();    
	//glLoadIdentity();
	//glOrtho(0.0, 0.0, 0.0, 0.0, -2.0, -1.0);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();    
	//glLoadIdentity(); 

	// bind texture
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
		//glNormal3f(0.0f, 0.0f, 1.0f);
		//glColor4f(r, g, b, a);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(-57.0, -57.0);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(57.0, -57.0);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(57.0, 57.0);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(-57.0, 57.0);
	glEnd();

/*	glMatrixMode(GL_PROJECTION);
	glPopMatrix();  
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();   */ 

	// unbind texture
	//_gl.glBindTexture( GL.GL_TEXTURE_2D, 0 ); 


	//glRotatef(angle[Y], 1.0f, 0.0f, 0.0f);
	//glRotatef(angle[X], 0.0f, 1.0f, 0.0f);
	//glRotatef(angle[Z], 0.0f, 0.0f, 1.0f);

	//generateBoxes();
	//drawBoxes();

	SDL_GL_SwapBuffers();

	//void *buffer = main_screen->pixels;

	//int bpp = main_screen->format->BytesPerPixel;
	//int width = main_screen->w;
	//int height = main_screen->h;
	//
	//memset(buffer, 0, width * height * bpp);

	//test_draw_cnt = (test_draw_cnt + 1) % 8;
	//DrawSprite(200, 200, hspr, 7618 + test_draw_cnt);

	//SDL_Flip(main_screen);
}

void DrawPixel(int x, int y, int col)
{
	SDL_Colour *argb = (SDL_Colour*)&col;
	Uint32 colour = SDL_MapRGB(main_screen->format, argb->r, argb->g, argb->b);

	Uint32 *pixmem32;

	pixmem32 = (Uint32*)main_screen->pixels + (main_screen->w * y) + x;
	*pixmem32 = colour;
}