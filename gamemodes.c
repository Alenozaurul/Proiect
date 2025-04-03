#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>

#include "headers/gamemodes.h"
#include "headers/sdl.h"


void startGM1()
{
	SDL_Window *window = InitWindow();
	if( !window )
		return;

	SDL_Renderer *renderer = InitRenderer( window );
	if( !renderer )
		return;	
	
	TTF_Font *Sans = TTF_OpenFont( "Sans.ttf", 24 );
	SDL_Color White = { 255, 255, 255 };

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid( Sans, "3", White );
	SDL_Texture *message = SDL_CreateTextureFromSurface( renderer, surfaceMessage );

	SDL_Rect Message_rect;
	Message_rect.w = 100;
	Message_rect.h = 40;
	Message_rect.y = ( WINDOW_WIDTH / 2 ) - ( Message_rect.h / 2 );
	Message_rect.x = ( WINDOW_HEIGHT/ 2 ) - ( Message_rect.w / 2 ); 

	SDL_RenderCopy( renderer, message, NULL, &Message_rect );
	sleep(2);
	SDL_FreeSurface( surfaceMessage );
	SDL_DestroyTexture( message );

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	sleep(2);

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

