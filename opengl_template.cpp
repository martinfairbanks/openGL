	/* TODO: 
	
	*/

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
	const int screenWidth = 960;
	const int screenHeight = 540;
	#define PI32 3.14159265359f

	SDL_Window *window = 0;
	SDL_Event event;
	unsigned long long performanceFrequency;		//the frequency of the performance counter in counts per seonds
	bool running = true;
	bool fullscreen = false;

int main(int argc, char** argv)
{
	performanceFrequency = SDL_GetPerformanceFrequency();
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("openGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/SDL_WINDOW_OPENGL);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//use vsync
	SDL_GL_SetSwapInterval(1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//reset projection matrix, wich is responsible for adding perspective the scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set camera perspective
	gluPerspective(45.0f,								//camera angle, field of view in degrees, set to 45 degrees viewing angle
		(GLfloat)screenWidth / (GLfloat)screenHeight,	//aspect ratio
		1.0f,											//near z clipping coordinate
		500.0f);										//far z clipping coordinate
														//1.0f - 500.0f is the start and end point for how deep we can draw into the screen

	//reset the modelview matrix, wich is where the object information is stored, sets x,y,z to zero
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	unsigned long long  lastCounter = SDL_GetPerformanceCounter();

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:
						case SDLK_RIGHT:
						case SDLK_UP:
						case SDLK_DOWN:
						case SDLK_n:
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

		//clear window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT);
		
		//set drawing color
		glColor3f(0.0f, 1.0f, 0.0f);

		//begin triangle coordinates
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 2.0f, -5.0f);
			glVertex3f(-2.0f, -2.0f, -5.0f);
			glVertex3f(2.0f, -2.0f, -5.0f);
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
