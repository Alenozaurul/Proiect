#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>

#include "sdlhead.h"

SDL_Surface *windowSurface = NULL;
SDL_Window *window = NULL;

SDL_Surface *temp1, *temp2;

int main(int argc, char **argv)
{
	if( !sdl_Init( windowSurface, window ) )
		return 1;

	if( !sdl_Load( SLD_surface *temp1, *temp2 ) )
		return 2;


	SDL_BlitSurface( temp1, NULL, windowSurface, NULL );
		
	SLD_React dest;
	dest.x = 160;
	dest.y = 120;
	dest.w = 320;
	dest.h = 240;
	SDL_BlitScaled( temp2, NULL, windowSurface, &dest );

	SDL_UpdateWindowSurface( window );
	system( "pause" );
	

	sdl_Kill( window );
	return 0;
}
