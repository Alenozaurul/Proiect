#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>

#include "headers/gamemodes.h"
#include "headers/sdl.h"


void startGM1()
{

	SDL_Window *window = InitWindow();
	SDL_Renderer *renderer = InitRenderer( window ); 
	TTF_Font *font = InitFont();
	if( !window || !renderer || !font )
	{
		Quit( window, renderer );
		return;
	}

	if( !StartGame( font, renderer ) )
	{
		return;
	}

	while( Loop(window, renderer) )
	{
		;
	}

	Quit( window, renderer );
}

void startGM2()
{
	SDL_Window *window = InitWindow();
	SDL_Renderer *renderer = InitRenderer( window ); 
	TTF_Font *font = InitFont();
	if( !window || !renderer || !font )
	{
		Quit( window, renderer );
		return;
	}

	if( !StartGame( font, renderer ) )
	{
		return;
	}

	Quit( window, renderer );
}
