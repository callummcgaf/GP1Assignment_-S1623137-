//Using SDL and standard IO
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Declare the window to be created and the window surfaces to be used
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurface = nullptr;

	// Initialise SDL for video display
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Video Initialisation Error: " << SDL_GetError() << std::endl;
	}
	// If initialisation returns with no errors
	else
	{
		// Then create an application window and display in the centre of the screen
		window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		// If there is no window then display error to the console
		if (window == NULL)
		{
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		}
		// Else, Pass windowSurface on to the application window to display and load the image for the image surface to use
		else
		{
			windowSurface = SDL_GetWindowSurface(window);
			imageSurface = SDL_LoadBMP("hello_world.bmp");
			// If there is no image of the specified name, then return an error message to the console
			if (imageSurface == NULL)
			{
				std::cout << "Image could not be loaded, Loading Error: " << SDL_GetError() << std::endl;
			}
			// If image was successfully loaded, then merge windowSurface with ImageSurface to display the image in the application window on screen
			else
			{
				SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
				SDL_UpdateWindowSurface(window);
				// Wait for 2 seconds
				SDL_Delay(2000);
			}
			
		}
	}

	// Free the media in the image surface as not to cause a memory leak
	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	// After the image has been displayed for 2 Seconds, reset the window and windowSurface, destroy the application window and quit the console 
	SDL_DestroyWindow(window);
	window = nullptr;
	windowSurface = nullptr;
	SDL_Quit();

	return 0;
}