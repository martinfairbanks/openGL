	/* Linking */
	#pragma comment(lib, "SDL2.lib")
	#pragma comment(lib, "SDL2main.lib")
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")

	/* Includes */
	#include <Sdl2/SDL.h>
	#include <sdl2/SDL_opengl.h>
	#include <gl/glu.h>				
	#include <stdio.h>
	
	/* Globals */
	SDL_Window *window = 0;
	SDL_Event event; 
	int screenWidth = 960;
	int screenHeight = 540;
	float angle = 0;								//rotation
	unsigned long long performanceFrequency;		//the frequency of the performance counter in counts per seonds
	bool running = true;
	bool fullscreen = false;
	#define PI32 3.14159265359f

void set3dProjection()
{
	//set viewport to window dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	//switch to the projection matrix and reset it
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set camera perspective
	gluPerspective(45.0f,								//camera angle, field of view in degrees, set to 45 degrees viewing angle
		(GLfloat)screenWidth / (GLfloat)screenHeight,	//aspect ratio
		1.0f,											//near z clipping coordinate
		500.0f);										//far z clipping coordinate
														//1.0f - 500.0f is the start and end point for how deep we can draw into the screen

	//switch to GL_MODELVIEW, tells OGL that all future transformations will affect what we draw
	//reset the modelview matrix, wich is where the object information is stored, sets x,y,z to zero
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//enable depth buffer
	glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv)
{
	performanceFrequency = SDL_GetPerformanceFrequency();
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL/* | SDL_WINDOW_FULLSCREEN_DESKTOP*/);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//use doublebuffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//use vsync
	SDL_GL_SetSwapInterval(1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	set3dProjection();

	unsigned long long  lastCounter = SDL_GetPerformanceCounter();

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_WINDOWEVENT:
				{
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						screenWidth = event.window.data1;
						screenHeight = event.window.data2;
						set3dProjection();
					}
				} break;

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_RETURN:
						{
							if (fullscreen)
							{
								SDL_SetWindowFullscreen(window, SDL_FALSE);
								fullscreen = false;
							}
							else
							{
								SDL_SetWindowFullscreen(window, SDL_TRUE);
								fullscreen = true;
							}
						} break;
					}
				} break;

				case SDL_KEYUP:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
						running = false;
				} break;

				case SDL_QUIT:
				{
					running = false;
				}	break;
			}
		}

		angle += 1;

		//clear screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		glTranslatef(2.0f, 0.0f, -7.0f);
		glRotatef(angle, 1.0f, 1.0f, 0.5f);

		//draw cube
		glBegin(GL_QUADS);
			//front 
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

			//left 
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);

			//back 
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);

			//right 
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);

			//top 
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);

			//bottom 
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();

		glLoadIdentity();
		glTranslatef(-2.0f, 0.0f, -7.0f);
		glRotatef(angle, 1.0f, 1.0f, 0.5f);

		//draw pyramid
		glBegin(GL_TRIANGLES);                  
			//front
			glColor3f(1.0f, 0.0f, 0.0f);          
			glVertex3f(0.0f, 1.0f, 0.0f);		//top
			glColor3f(0.0f, 1.0f, 0.0f);          
			glVertex3f(-1.0f, -1.0f, 1.0f);     //left
			glColor3f(0.0f, 0.0f, 1.0f);          
			glVertex3f(1.0f, -1.0f, 1.0f);      //right

			//right
			glColor3f(1.0f, 0.0f, 0.0f);          
			glVertex3f(0.0f, 1.0f, 0.0f);          
			glColor3f(0.0f, 0.0f, 1.0f);          
			glVertex3f(1.0f, -1.0f, 1.0f);         
			glColor3f(0.0f, 1.0f, 0.0f);          
			glVertex3f(1.0f, -1.0f, -1.0f);        

			//back
			glColor3f(1.0f, 0.0f, 0.0f);          
			glVertex3f(0.0f, 1.0f, 0.0f);          
			glColor3f(0.0f, 1.0f, 0.0f);          
			glVertex3f(1.0f, -1.0f, -1.0f);         
			glColor3f(0.0f, 0.0f, 1.0f);          
			glVertex3f(-1.0f, -1.0f, -1.0f);		

			//left
			glColor3f(1.0f, 0.0f, 0.0f);          
			glVertex3f(0.0f, 1.0f, 0.0f);          
			glColor3f(0.0f, 0.0f, 1.0f);          
			glVertex3f(-1.0f, -1.0f, -1.0f);      
			glColor3f(0.0f, 1.0f, 0.0f);          
			glVertex3f(-1.0f, -1.0f, 1.0f);  
		glEnd();

		//bottom of pyramid
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);          
			glVertex3f(1.0f, -1.0f, 1.0f); 
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f); 
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();                      

		//update screen
		SDL_GL_SwapWindow(window);

		unsigned long long endCounter = SDL_GetPerformanceCounter();
		unsigned long long counterElapsed = endCounter - lastCounter;
		double msPerFrame = (((1000.0f * (double)counterElapsed) / (double)performanceFrequency));
		double fps = (double)performanceFrequency / (double)counterElapsed;
		lastCounter = endCounter;

		char message[256];
		sprintf_s(message, "%.03fms, %.03fFPS\0", msPerFrame, fps);
		SDL_SetWindowTitle(window, message);
	}
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
