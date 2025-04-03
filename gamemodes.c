#include <SDL2/SDL.h>
#include <stdbool.h>

#include "gamemodes.h"
#include "sdl.h"


void startGM1()
{
	SDL_Window *window = InitWindow();
	if( !window )
		return;

	SDL_Renderer *renderer = InitRenderer( window );
	if( !renderer )
		return;	


	Quit( window, renderer);
}

void startGM2()
{
	SDL_Window *window = InitWindow();
	if( !window )
		return;

	SDL_Renderer *renderer = InitRenderer( window );
	if( !renderer )
		return;	


	Quit( window, renderer);
}

