#include <SDL2/SDL.h>

#include "headers/sdl.h"

SDL_Window *InitWindow()
{
	SDL_Window *window = NULL;

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	window = SDL_CreateWindow( "Alien Invasion", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN );

	if( !window )
	{	
		printf("%s\n", SDL_GetError());
		return NULL;
	}
	
	return window;
}

SDL_Renderer *InitRenderer( SDL_Window *window )
{
	SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	if( !renderer )
	{
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	return renderer;
}

void Quit( SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

