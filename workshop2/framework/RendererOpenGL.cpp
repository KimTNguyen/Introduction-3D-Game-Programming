// Implementation of RendererOpenGL.h
// Aim: To encapsulate all OpenGL specifics into one class
//      to enable easy replacement of OpenGL with other
//      graphics APIs (and enable placement of the renderer class into other programs)
//
// Created: 31 May 2005
// Modified: 3rd August 2005
// Author: Martin Masek - SCIS, Edith Cowan University
// Modified: 23 Feb 2010 - Kim Nguyen - SCIS, Edith Cowan University.

#include <windows.h>

#include "RendererOpenGL.h" // include the definition of the class

RendererOpenGL* RendererOpenGL::renderer = NULL;  // initialise the pointer to the class to NULL

RendererOpenGL* RendererOpenGL::Instance() // for returning a pointer to the renderer class (also instantiates it if it does not exist)
{
	// the class is implemented as a singleton, so create a new instance only if one does not exist already
	if (renderer==NULL)
	{
		// call the constructor (it was declared 'protected' in the header file (RendererOpenGL.h)
		// so users of the class cant instantiate new objects from this class (constructor can only be called from within the class)
		renderer = new RendererOpenGL; 
	}
	return renderer; // return the pointer to the renderer (to see how this is used, see the message processing function in windowCreator.cpp)
}

RendererOpenGL::RendererOpenGL() // constructor
{	
	hWnd = NULL; // current window handle
	hRC = NULL; // rendering context handle (drawing context for OpenGL
	hDC = NULL; // device context handle (device that is displaying the current window)

	rendererWidth = GLsizei(640);
	rendererHeight = GLsizei(480);
	fieldOfViewAngle = 120;
	nearClippingPlane = 0.1f;
	farClippingPlane = 1000.0f;
}

RendererOpenGL::~RendererOpenGL() // destructor
{
}


void RendererOpenGL::Render() // this does the drawing
{	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	
	/* create viewing matrix to do the viewing transformation by:
	   using the translation and rotation modeling commands glTranslatef() 
	   and glRotatef() */

	glTranslatef(-5, 0, 0);		// move the entire world 5 units to the left
	glRotatef(-45, 0, 1, 0);	// rotate the entire world -45 degrees around Y axis

	glPushMatrix();	// store the current position in world space
	glTranslatef(-0.5, 0, -10);	// move the first cube to (-0.5, 0, -10) in world space

	// draw the first cube in model space 
	glBegin(GL_QUADS);
		
		// draw red face 
		glColor3f(1, 0, 0);
		glVertex3f(-1, 1, 1);	
		glVertex3f(-1, -1, 1);
		glVertex3f(1, -1, 1);
		glVertex3f(1, 1, 1);

		// draw green face
		glColor3f(0, 1, 0);
		glVertex3f(1, 1, 1);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, 1, -1);

		// draw blue face 
		glColor3f(0, 0, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(1, 1, -1);
		glVertex3f(1, -1, -1);
		glVertex3f(-1, -1, -1);
		
		// draw yellow face 
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, -1, -1);
		glVertex3f(-1, -1, 1);

		// draw white face 
		glColor3f(1, 1, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, 1, 1);
		glVertex3f(1, 1, 1);
		glVertex3f(1, 1, -1);

		// draw purple face 
		glColor3f(0, 1, 1);
		glVertex3f(-1, -1, -1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, -1, 1);
		glVertex3f(-1, -1, 1);
	glEnd();
	glPopMatrix();	// go back to the previous position

	glPushMatrix();	
	glTranslatef(0.5, 0, -5);	// move the second cube to (0.5, 0, -5) in world space 
	glScalef(0.5, 0.5, 0.5);	// scale the cube down to a half of the original size.
	glRotatef(45,0.0,1.0,0.0);	// rotate the cube 45 degrees around y axis

	// draw the second cube in model space 
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(-1, 1, 1);
		glVertex3f(-1, -1, 1);
		glVertex3f(1, -1, 1);
		glVertex3f(1, 1, 1);

		glColor3f(0, 1, 0);
		glVertex3f(1, 1, 1);
		glVertex3f(1, -1, 1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, 1, -1);

		glColor3f(0, 0, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(1, 1, -1);
		glVertex3f(1, -1, -1);
		glVertex3f(-1, -1, -1);
		
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, -1, -1);
		glVertex3f(-1, -1, 1);

		glColor3f(1, 1, 1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, 1, 1);
		glVertex3f(1, 1, 1);
		glVertex3f(1, 1, -1);

		glColor3f(0, 1, 1);
		glVertex3f(-1, -1, -1);
		glVertex3f(1, -1, -1);
		glVertex3f(1, -1, 1);
		glVertex3f(-1, -1, 1);	
	glEnd();
	glPopMatrix();

	SwapBuffers(hDC); //swap the buffer that OpenGL has been drawing into with the frame buffer (buffer the screen is drawn from)
}


void RendererOpenGL::setUpViewingFrustum()  // set up the viewing volume
{
	// Select projection matrix and reset it to identity, subsequent operations are then performed on this matrix (gluPerspective)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// set up the perspective of the window
	GLdouble aspectRatio = (GLfloat)rendererWidth/(GLfloat)rendererHeight;
	gluPerspective(fieldOfViewAngle, aspectRatio, nearClippingPlane, farClippingPlane);

	// select the model-view matrix (to de-select the projection matrix) and reset it to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



bool RendererOpenGL::bindToWindow(HWND &windowHandle)
{
	//set up pixel format, rendering context
	// NOTE: this method uses 'wgl' commands - the MS Windows Operating system binding for OpenGL.
	// it must be over-written when porting this renderer to another OS.

	// Need to do 5 things before we can use OpenGL
	// First - get the device context of the game window (ie. what is the window being shown on eg. graphics adapter)
	// Second - set that device to some desired pixel format
	// Third - create a rendering context for OpenGL (something OpenGL draws to and maps to the device)
	// Fourth - make the rendering context 'current'
	// Fifth - Set the size of the OpenGL window.
	
	// First - get the device context of the game window
	hWnd = windowHandle;
	hDC = GetDC(hWnd); // get the device context of the window
	

	// Second - set the device to some desired pixel format
	// This is done be filling out a pixel format descriptor structure

	static PIXELFORMATDESCRIPTOR pfd; // pixel format descriptor

	// The pixel format discriptor has a lot of memembers (26) !
	// luckily we dont need most of them and set them to zero
	// we could go through the structure member by member and set them to zero
	// but a shortcut way is to use memset to initialise everything to zero

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)); // sets all memmbers of pfd to 0

	// now we change only the relevant pfd members
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits	= 16;
	pfd.cDepthBits	= 16;

	// based on the descriptor, choose the closest supported pixel format.
	int PixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (PixelFormat==0)
	{
		// error
		MessageBox (NULL,"Could not choose pixel format","Error",MB_OK);
		return (false);
	}

	// set the display device (device context) to the pixel format
	if (SetPixelFormat(hDC, PixelFormat, &pfd)==0)
	{
		// error
		MessageBox (NULL,"Could not set pixel format","Error",MB_OK);
		return (false);
	}

	

	// Third - create rendering context
 
	 hRC = wglCreateContext(hDC); // windows dependent OpenGL function (wgl)
	 if (hRC==NULL)
	 {
		 MessageBox (NULL,"Could not create GL rendering context","Error",MB_OK);
		 return (false);
	 }

	 // Fourth - Make the rendering context current	 
	 if (!wglMakeCurrent(hDC, hRC))
	 {
		 MessageBox (NULL,"Could not make rendering context current","Error",MB_OK);
		 return (false);
	 }

	 // Fifth - set the size of the OpenGL window

	 /*
	 ***** Note: this step is important, not setting an initial size
	 can cause the whole OS to crash (computer is re-set)
	 */

	 RECT rect; // structure to store the coordinates of the 4 corners of the window
	 GetClientRect (hWnd, &rect); // put the window coordinates in the structure
	 ResizeCanvas(long(rect.right-rect.left), long(rect.bottom-rect.top));
	 
	return (true);
}

void RendererOpenGL::getGLvendor()
{
	char *info;
	info = (char *)glGetString(GL_VENDOR);
	MessageBox (NULL,info,"Vendor",MB_OK);
}
void RendererOpenGL::getGLrenderer()
{
	char *info;
	info = (char *)glGetString(GL_RENDERER);
	MessageBox (NULL,info,"Renderer",MB_OK);
}
void RendererOpenGL::getGLversion()
{
	char *info;
	info = (char *)glGetString(GL_VERSION);
	MessageBox (NULL,info,"Version",MB_OK);
}
void RendererOpenGL::getGLextensions()
{
	char *info;
	info = (char *)glGetString(GL_EXTENSIONS);
	MessageBox (NULL,info,"Extensions",MB_OK);
}



void RendererOpenGL::initialise()
{
	glClearColor(0.0,0.0,0.0,0.0);						// select what colour the background is (here set to black)
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing (using Z-buffer)
	glEnable(GL_CULL_FACE);								// Turn on back-face culling 
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// give OpenGL a hint on which perspective calculation to use (here suggesting the nicest)
	SwapBuffers(hDC);									// draw the screen (will draw a black blank screen as no drawing has been done yet)
	
	// examples of other operations that could be good here in the future:
	//glEnable(GL_TEXTURE_2D);	// enable 2D texture mapping
	//glFrontFace(GL_CW); // indicate which side of a polygon is the front (defined in terms of the order vertices are given)
	//glEnable(GL_CULL_FACE); // enable back-face culling
}

bool RendererOpenGL::releaseFromWindow()
{
	if (hDC == NULL || hRC == NULL) 
	{
		MessageBox (NULL,"hDC or hRC already NULL!","Error",MB_OK);
		return (false);
	}

	if (wglMakeCurrent(NULL, NULL) == false)					
	{
		// error
		MessageBox (NULL,"Could not set hDC to NULL","Error",MB_OK);
		return (false);
	}

	if (wglDeleteContext(hRC) == false)						
	{
		// error deleting rendering context
		MessageBox (NULL,"Could not delete rendering context","Error",MB_OK);
		return (false);
	}

	// Windows releases the DC in the default message handler, if not passing all messages through it,
	// the releaseDC function must be called (we are, so its commented out - otherwise allways get the message box error)
	//if (releaseDC(hWnd,hDC)==false)
	//{
	//	MessageBox (NULL,"Could not release device context","Error",MB_OK);
	//	return (false);
	//}
	
	hRC	= NULL;
    hDC	= NULL;	

	// delete the renderer and set it to NULL (this is how the singleton gets deleted)
	delete renderer;
	renderer = NULL;

	return (true);

}

// re-size the viewport
void RendererOpenGL::ResizeCanvas(long widthRequest, long heightRequest)
{
	rendererWidth = (GLsizei)widthRequest;
	rendererHeight = (GLsizei)heightRequest;
    glViewport(0, 0, rendererWidth, rendererHeight);
	setUpViewingFrustum();	
}
