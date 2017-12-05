//Using SDL and standard IO
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Declare the window to be created and the window surfaces to be used
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *staticImage = nullptr;
	SDL_Surface *upImage = nullptr;
	SDL_Surface *downImage = nullptr;
	SDL_Surface *rightImage = nullptr;
	SDL_Surface *leftImage = nullptr;
	SDL_Surface *currentImage = nullptr;
	SDL_Surface *mleftImage = nullptr;
	SDL_Surface *mrightImage = nullptr;

	// Initialise SDL for video display
	SDL_Init(SDL_INIT_VIDEO);

	// Then create an application window and display in the centre of the screen
	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 344, 344, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);
	
	staticImage = SDL_LoadBMP("Arrow Keys.bmp");
	upImage = SDL_LoadBMP("Arrow Keys (UP).bmp");
	downImage = SDL_LoadBMP("Arrow Keys (Down).bmp");
	rightImage = SDL_LoadBMP("Arrow Keys (Right).bmp");
	leftImage = SDL_LoadBMP("Arrow Keys (Left).bmp");
	mleftImage = SDL_LoadBMP("Mouse (Left).bmp");
	mrightImage = SDL_LoadBMP("Mouse (Right).bmp");
	currentImage = staticImage;

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

			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_UP:
					currentImage = upImage;
					break;
				case SDLK_DOWN:
					currentImage = downImage;
					break;
				case SDLK_RIGHT:
					currentImage = rightImage;
					break;
				case SDLK_LEFT:
					currentImage = leftImage;
					break;
				}
			}
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
					currentImage = mleftImage;
				else if (ev.button.button == SDL_BUTTON_RIGHT)
					currentImage = mrightImage;
			}
			else
			{
				currentImage = staticImage;
			}
			
			SDL_BlitSurface(currentImage, NULL, windowSurface, NULL);

			// If the user has not quit the application yet, then update the application window
			SDL_UpdateWindowSurface(window);
		}
	}

	SDL_FreeSurface(staticImage);
	SDL_FreeSurface(upImage);
	SDL_FreeSurface(downImage);
	SDL_FreeSurface(rightImage);
	SDL_FreeSurface(leftImage);
	SDL_FreeSurface(mleftImage);
	SDL_FreeSurface(mrightImage);

	// Destroy the application window and Quit the console
	SDL_DestroyWindow(window);

	currentImage = staticImage = upImage = downImage = rightImage = leftImage = mleftImage = mrightImage = nullptr;
	window = nullptr;

	SDL_Quit();

	return 0;
}