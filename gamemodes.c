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

	//if( !StartGame( font, renderer ) )
	//{
	//	return;
	//}

	Player player;
	player.body.h = 50;
	player.body.w = 50;
	player.body.x = ( WINDOW_WIDTH / 2 ) - ( player.body.w / 2 );
	player.body.y = ( WINDOW_HEIGHT / 2 ) - ( player.body.h / 2 );
	
	for( int i = 0; i < 30; ++i )
	{
		player.bullets[i].w = 0;
		player.bullets[i].y = 0;
		player.bullets[i].x = 0;
		player.bullets[i].h = 0;
	}
	int reload = 30;
	while( Loop(window, renderer, &player, &reload) )
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
