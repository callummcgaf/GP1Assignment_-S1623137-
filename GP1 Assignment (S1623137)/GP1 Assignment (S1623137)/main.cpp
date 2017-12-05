// Include SDL and Standard IO headers
#include <SDL.h>
#include <stdio.h>

// Set constant integer variables for the application's window height and width
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ) 
{

	// The window we'll be rendering to
	SDL_Window *window = nullptr;

	// The surface contained by the window
	SDL_Surface *screenSurface = NULL;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
	}

	else
	{
		
		// Create window
		window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			printf("Window could not be created!SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			// Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

			// Update the surface
			SDL_UpdateWindowSurface(window);
			
			// Wait two seconds
			SDL_Delay(2000);
		}

		// Destroy window
		SDL_DestroyWindow(window);

		// Quit SDL subsystems
		SDL_Quit();

	}

	return 0;

}