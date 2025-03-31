#include <stdbool.h>
#include <SDL2/SDL.h>
#include "sdlhead.h"

bool sdl_Init( SDL_Surface *windowSurface, SDL_Window *window)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow( "New Window", SDL_WINDOWPOS_UNDEFINED,
		       		   SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN );

	if( !window )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	windowSurface = SDL_GetWindowSurface( window );

	if( !windowSurface )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool sdl_Load( SDL_surface *temp1, SLD_Suraface *temp2 )
{
	SDL_Surface *vt1, *vt2;

	vt1 = SDL_LoadBMP( "test1.bmp" );
	vt2 = SDL_LoadBMP( "test2.bmp" );

	if( !vt1 || !vt2 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	temp1 = SLD_ConvertSurface( vt1, windowSurface -> format, 0 );
	temp2 = SLD_ConvertSurface( vt2, windowSurface -> format, 0 );

	SDL_FreeSurface( vt1 );
	SDL_FreeSurface( vt2 );

	if( !temp1 || !temp2 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	return true;
}	


void sdl_Kill( SDL_Window *window )
{
	SDL_DestroyWindow( window );
	SDL_Quit();
}
