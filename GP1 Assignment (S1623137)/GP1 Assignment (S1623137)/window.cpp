//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	// Create Texture and load a surface
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filePath.c_str());
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

	// Create float values to be used for various reasons later in the script
	float frameTime = 0;
	float prevTime = 0;
	float currentTime = 0;
	float deltaTime = 0;
	float moveSpeed = 3.0f;
	// Set up a variable to record the state of keys inbetween refreshes.
	const Uint8*keyState;

	// Declare the window to be created and the textures to be used
	SDL_Window *window = nullptr;

	// Create a renderer to be used to display the textures
	SDL_Renderer *renderTarget = nullptr;

	// Create texture to be used later
	SDL_Texture *currentImage = nullptr;

	// Create an unseen rectangle in the screen to skew images loaded within it
	SDL_Rect playerRect;
	// Create a rectagle to represent the players position on-screen and pass in values for x,y,width and Height
	SDL_Rect playerPosition = { 0.0f, 0.0f, 46, 50};
	// Create new integers to be used later
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	// Initialise SDL for video display and game contollers
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	// Initialise SDL image to load png images
	int imgFlags = IMG_INIT_PNG;
	if (IMG_Init(imgFlags) != imgFlags)
	{
		// If an error while initialising SDL image is found, return error message to console
		std::cout << "Error: " << IMG_GetError << std::endl;
	}

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
	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	// Set the renderer equal to the window that was created, using the first available driver and setting the rendering process to be carried out by the GPU instead of the CPU, Update the renderer based on the verical sync of the monitior
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Load png image into a texture
	currentImage = LoadTexture("playerSprite.png", renderTarget);

	// Retreive image properties such as heigth and width, from the image currently loaded in the renderer
	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	// Set frame width and height to only contain 1 graphical instance of the character from the original texture
	frameWidth = textureWidth / 8;
	frameHeight = textureHeight / 3;

	// Create values for the before declared player rectangle to be equal to the height and width of before mentioned character texture
	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	// Draw a basic ectangle across the whole screen to contrast with loaded image
	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	//Set up the game loop
	bool isRunning = true;
	// Create a variable to record events input by the user
	SDL_Event ev;

	// While the boolean 'isRunning' is equal to true
	while (isRunning)
	{
		// Gets time frame that has past since  the program was launched
		currentTime = SDL_GetTicks();
		// Sets a timer to be used to create a standard refresh rate for loading new images based on a timer
		deltaTime = (currentTime - prevTime)/ 1000.0f;
		// Set previously recorded time to new current time to use next time the program repeates this loop
		prevTime = currentTime;
		// And While the events given by the user are not equal to 0
		while (SDL_PollEvent(&ev) != 0)
		{
			// Check if the user has clicked the quit application button, if they have then set the variable 'isRunning' to false, causing the game loop to end
			if (ev.type == SDL_QUIT)
			{
				isRunning = false;
			}

		}

		// Checks keyboard to find if any buttons have been pressed since last loop
		keyState = SDL_GetKeyboardState(NULL);
		// If they have and match the arrows used for movement, then move the players sprite a certain number of pixels to either the right or the left, depending on which movement key was pressed
		if (keyState[SDL_SCANCODE_RIGHT])
			playerPosition.x += moveSpeed;
		if (keyState[SDL_SCANCODE_LEFT])
			playerPosition.x -= moveSpeed;

		// Set frame time equal to recorded runtime
		frameTime += deltaTime;

		// If runtime is more than or equal to a 10th of a second
		if (frameTime >= 0.10f)
		{
			// Then reset the frametime to reset timer
			frameTime = 0;
			// Cycle to next stage in the sprite animation via moving to the next section of the image
			playerRect.x += frameWidth;
			// If the rectangle has reached the edge of the sprite sheet, then reset to the first part of the sprite sheet
			if (playerRect.x >= textureWidth)
				playerRect.x = 0;
		}

		// Clears the last texture that was rendered
		SDL_RenderClear(renderTarget);
		// Copies the contents of the renderer and passes in the texture to be displayed 
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		// Presents the rendered images to the user
		SDL_RenderPresent(renderTarget);
	}

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
	currentImage = nullptr;
	// Clear the renderer
	renderTarget = nullptr;

	// Quit the application
	SDL_Quit();

	return 0;
}