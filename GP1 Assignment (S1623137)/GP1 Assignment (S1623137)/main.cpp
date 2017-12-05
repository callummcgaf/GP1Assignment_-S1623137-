// Include SDL and Standard IO headers
#include <SDL.h>
#include <stdio.h>

// Set constant integer variables for the application's window height and width
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window that will be rendered to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The image thta will be loaded and shown on the screen
SDL_Surface* gXOut = NULL;

bool init()
{

	// Initialisation flag
	bool success = true;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		// Create window
		gWindow = SDL_CreateWindow("SDL Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;

}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load splash image
	gXOut = SDL_LoadBMP("x.bmp");
	if (gXOut == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "x.bmp", SDL_GetError());
		success = false;
	}

	return success;

}

void close()
{

	// Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL Subsystems
	SDL_Quit();

}

int main( int argc, char* args[] ) 
{

	// Start up SDL and Create window
	if (!init())
	{

		printf("Failed to initialise!\n");

	}

	else
	{

		// Load Media
		if (!loadMedia())
		{

			printf("Failed to load media!\n");

		}

		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event Event;

			// While application is running
			while (!quit) 
			{
				// Handle events on queue
				while (SDL_WaitEvent(&Event) != 0)
				{
					// User requests quit
					if (Event.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				// Apply the image
				SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}

	}

	// Free resource and close SDL
	close();

	return 0;

}