#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "headers/gamemodes.h"
#include "headers/sdl.h"
#include "headers/action.h"

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

	Player player;
	player.health = 100;
	player.atack = 35;
	player.body.h = 50;
	player.body.w = 50;
	player.body.x = ( WINDOW_WIDTH / 2 ) - ( player.body.w / 2 );
	player.body.y = ( WINDOW_HEIGHT / 2 ) - ( player.body.h / 2 );
	
	for( int i = 0; i < 20; ++i )
	{
		player.bullets[i].w = 0;
		player.bullets[i].y = 0;
		player.bullets[i].x = 0;
		player.bullets[i].h = 0;
	}

	Enemy enemy[20];
	for( int i = 0; i <20; ++i )
	{
		enemy[i].body.w = 0;
		enemy[i].body.h = 0;
		enemy[i].body.x = 0;
		enemy[i].body.y = 0;
		
		for( int j = 0; j < 20; ++j )
		{
			enemy[i].bullets[j].x = 0;
			enemy[i].bullets[j].h = 0;
			enemy[i].bullets[j].y = 0;
			enemy[i].bullets[j].w = 0;
		}
	}

	int reload = 0;
	int respawn = 50;
	int reload_enemy[20] = {0};

	int base_health = 4000;
	int score = 0;
	int time = 150;
	SDL_Rect buff;

	while( Loop(window, renderer, font, &player, enemy, &reload, reload_enemy, &respawn, &base_health, &score, &time, &buff) )
	{;

	}

	Quit( window, renderer );

	printf("\n\nGAME OVER\nSCORE: %i\n\n\n\n", score);
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
