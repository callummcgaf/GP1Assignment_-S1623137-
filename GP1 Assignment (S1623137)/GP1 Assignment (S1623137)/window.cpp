//Using SDL and standard IO
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Declare the window to be created and the window surfaces to be used
	SDL_Window *window = nullptr;

	// Initialise SDL for video display
	SDL_Init(SDL_INIT_VIDEO);

	// Then create an application window and display in the centre of the screen
	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	
	//Set up the game loop
	bool isRunning = true;
	// Create a variable to record events input by the user
	SDL_Event ev;

	// While the boolean 'isRunning' is equal to true
	while (isRunning)
	{
		// And While the events given by the user are not equal to 0
		while (SDL_PollEvent(&ev) != 0)
		{
			// Check if the user has clicked the quit application button, if they have then set the variable 'isRunning' to false, causing the game loop to end
			if (ev.type == SDL_QUIT)
			{
				isRunning = false;
			}
			
			// If the user has not quit the application yet, then update the application window
			SDL_UpdateWindowSurface(window);
		}
	}

	// Destroy the application window and Quit the console
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}