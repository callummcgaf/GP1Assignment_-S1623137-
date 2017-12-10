//Using SDL and standard IO
#include <SDL.h>
#include <iostream>


SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	// Create Texture and load a surface
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());
	// If the surface was not loaded then return an error message to the console
	if (surface == NULL)
		std::cout << "Error: surface != NULL" << std::endl;
	else 
	{
		// Set the texture to the surface that was loaded
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		// If the texture is empty then return an error message to the console
		if (texture == NULL)
			std::cout << "Error: windowSurface != NULL" << std::endl;
	}

	// Free the loaded surface to become empty
	SDL_FreeSurface(surface);

	// Return the texture
	return texture;

}

int main(int argc, char *argv[])
{
	// Declare the window to be created and the textures to be used
	SDL_Window *window = nullptr;
	SDL_Texture *staticImage = nullptr;
	SDL_Texture *upImage = nullptr;
	SDL_Texture *downImage = nullptr;
	SDL_Texture *rightImage = nullptr;
	SDL_Texture *leftImage = nullptr;
	SDL_Texture *currentImage = nullptr;
	SDL_Texture *mleftImage = nullptr;
	SDL_Texture *mrightImage = nullptr;

	// Create a renderer to be used to display the textures
	SDL_Renderer *renderTarget = nullptr;

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
	// Set the renderer equal to the window that was created, using the first available driver and setting the rendering process to be carried out by the GPU instead of the CPU
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load images into corresponding textures
	staticImage = LoadTexture("TestSmall.bmp", renderTarget);
	upImage = LoadTexture("Arrow Keys (UP).bmp", renderTarget);
	downImage = LoadTexture("Arrow Keys (Down).bmp", renderTarget);
	rightImage = LoadTexture("Arrow Keys (Right).bmp", renderTarget);
	leftImage = LoadTexture("Arrow Keys (Left).bmp", renderTarget);
	mleftImage = LoadTexture("Mouse (Left).bmp", renderTarget);
	mrightImage = LoadTexture("Mouse (Right).bmp", renderTarget);
	currentImage = staticImage;

	// draw a rectangle for the Application window to strech any images to fit the full screen
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
			
			// Clears the last texture that was rendered
			SDL_RenderClear(renderTarget);
			// Copies the contents of the renderer and passes in the texture to be displayed 
			SDL_RenderCopy(renderTarget, currentImage, NULL, NULL);
			// Presents the rendered images to the user
			SDL_RenderPresent(renderTarget);
		}
	}

	// Destroy the textures as not to leave used memory floating after the application has closed
	SDL_DestroyTexture(staticImage);
	SDL_DestroyTexture(upImage);
	SDL_DestroyTexture(downImage);
	SDL_DestroyTexture(rightImage);
	SDL_DestroyTexture(leftImage);
	SDL_DestroyTexture(mleftImage);
	SDL_DestroyTexture(mrightImage);

	// Destroy the application window and Quit the console
	SDL_DestroyRenderer(renderTarget);

	// Checks if the SDL controller is empty
	if (controller != NULL)
	{
		// If not then close the controller and set the SDL controller to empty
		SDL_GameControllerClose(controller);
		controller = nullptr;
	}


	// Clear the image textures as not to leave media after the application has closed
	currentImage = staticImage = upImage = downImage = rightImage = leftImage = mleftImage = mrightImage = nullptr;
	// Clear the renderer
	renderTarget = nullptr;

	// Quit the application
	SDL_Quit();

	return 0;
}