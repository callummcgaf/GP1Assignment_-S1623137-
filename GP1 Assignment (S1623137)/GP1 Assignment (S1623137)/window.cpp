//Using SDL and standard IO
#include <SDL.h>
#include <iostream>

SDL_Surface *OptimizedSurface(std::string filePath, SDL_Surface *windowSurface)
{
	SDL_Surface *optimizedSurface = nullptr;
	SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error: surface != NULL" << std::endl;
	else 
	{
		optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
		if (optimizedSurface == NULL)
			std::cout << "Error: windowSurface != NULL" << std::endl;
	}

	SDL_FreeSurface(surface);

	return optimizedSurface;

}

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

	// Initialise SDL for video display and game contollers
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	// Writes in console how many controllers are connected to the PC
	SDL_Log("%d number of controllers are connected", 0);

	// Creates a controller to be used later
	SDL_GameController *controller = nullptr;

	// Sets up a for loop equal to the amount of Joysticks connected to the PC
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		// Checks if the joystick is a game controller
		if (SDL_IsGameController(i))
		{
			// Sets SDL controller to the physical controller
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}

	// Records in console the name of the console
	std::cout << "Contorller Name: " << SDL_GameControllerName(controller) << std::endl;

	// Then create an application window and display in the centre of the screen
	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 344, 344, SDL_WINDOW_SHOWN);
	windowSurface = SDL_GetWindowSurface(window);
	
	// Load images into corresponding surfaces
	staticImage = OptimizedSurface("TestSmall.BMP", windowSurface);
	upImage = SDL_LoadBMP("Arrow Keys (UP).bmp");
	downImage = SDL_LoadBMP("Arrow Keys (Down).bmp");
	rightImage = SDL_LoadBMP("Arrow Keys (Right).bmp");
	leftImage = SDL_LoadBMP("Arrow Keys (Left).bmp");
	mleftImage = SDL_LoadBMP("Mouse (Left).bmp");
	mrightImage = SDL_LoadBMP("Mouse (Right).bmp");
	currentImage = staticImage;

	SDL_Rect drawingRect;
	drawingRect.x = drawingRect.y = 0;
	drawingRect.w = drawingRect.h = 344;

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

			// Check if the user has pressed one of the arrow keys, if they have, then the image corresponding to that input will be displayed on the screen as it is being pressed
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
			// Similar to the last check, find if the user is inputing from the mouse and display the images corresponding to that event
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
					currentImage = mleftImage;
				else if (ev.button.button == SDL_BUTTON_RIGHT)
					currentImage = mrightImage;
			}

			// Similar to the prevoius checks, find if the user has pressed a button on the physical game controller and record in the console which button has been pressed in its numerical format
			else if (ev.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (ev.cbutton.which == 0)
				{
					std::cout << (int)ev.cbutton.button << std::endl;
				}
			}
			// If the user has not pressed anything this frame, then change the image displayed to the default image
			else
			{
				currentImage = staticImage;
			}
			
			// Display the current image onto the window surface
			SDL_BlitScaled(currentImage, NULL, windowSurface, &drawingRect);

			// If the user has not quit the application yet, then update the application window
			SDL_UpdateWindowSurface(window);
		}
	}

	// Free the surfaces as not to leave used memory floating after the application has closed
	SDL_FreeSurface(staticImage);
	SDL_FreeSurface(upImage);
	SDL_FreeSurface(downImage);
	SDL_FreeSurface(rightImage);
	SDL_FreeSurface(leftImage);
	SDL_FreeSurface(mleftImage);
	SDL_FreeSurface(mrightImage);

	// Destroy the application window and Quit the console
	SDL_DestroyWindow(window);

	// Checks if the SDL controller is empty
	if (controller != NULL)
	{
		// If not then close the controller and set the SDL controller to empty
		SDL_GameControllerClose(controller);
		controller = nullptr;
	}


	// Clear the image and window surfaces as not to leave media after the application has closed
	currentImage = staticImage = upImage = downImage = rightImage = leftImage = mleftImage = mrightImage = windowSurface = nullptr;
	window = nullptr;

	// Quit the application
	SDL_Quit();

	return 0;
}