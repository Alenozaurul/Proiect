#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "headers/sdl.h"
#include "headers/spaceships.h"


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

TTF_Font *InitFont()
{
	if( TTF_Init() < 0 )
	{
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	TTF_Font *font = TTF_OpenFont( "Normal.ttf", 36 );

	if( !font )
	{
		printf("%s\n", SDL_GetError());
		return NULL;
	}	

	return font;
}	

bool StartGame( TTF_Font *font, SDL_Renderer *renderer )
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid( font, "9", textColor );
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

	if( !textTexture  || !textSurface ) 
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_Rect textRect; 
	textRect.h = textSurface -> h;
	textRect.w = textSurface -> w;
	textRect.x = ( WINDOW_WIDTH / 2 ) - ( textRect.w / 2 );
	textRect.y = ( WINDOW_HEIGHT / 2 ) - ( textRect.h / 2 );
	for( int i = 3; i >= 0; --i )
	{		
		if( !i ) 
		{
			textSurface = TTF_RenderText_Solid( font, "Start!", textColor );
			textRect.h = textSurface -> h;
			textRect.w = textSurface -> w;
			textRect.x = ( WINDOW_WIDTH / 2 ) - ( textRect.w / 2 );
			textRect.y = ( WINDOW_HEIGHT / 2 ) - ( textRect.h / 2 );
			textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		}
		else
		{
			char countdown[2];
			sprintf( countdown, "%i", i );
			textSurface = TTF_RenderText_Solid( font, countdown, textColor );
			textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		}
	        SDL_RenderClear( renderer );	
		SDL_RenderCopy( renderer, textTexture, NULL, &textRect );
		SDL_RenderPresent( renderer );	
		SDL_Delay( 1000 );
	}
	
	SDL_DestroyTexture( textTexture );
	return true;
}

bool Loop(SDL_Window *window, SDL_Renderer *renderer)
{
	const unsigned char *keys = SDL_GetKeyboardState( NULL );
	SDL_Event event;
	Player player;
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear ( renderer );


	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	
	player.body.h = 50;
	player.body.w = 50;
	player.body.x = ( WINDOW_WIDTH / 2 ) - ( player.body.w / 2 );
	player.body.y = ( WINDOW_HEIGHT / 2 ) - ( player.body.h / 2 );
	
	SDL_RenderFillRect( renderer, &player.body );
	SDL_RenderPresent( renderer );

	SDL_Delay(1000);

	while( SDL_PollEvent( &event ) )
	{
		if( event.type == SDL_QUIT )
			return false;
		if( keys[SDL_SCANCODE_ESCAPE] )
			return false;
					

	}


	return true;
}


void Quit( SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

