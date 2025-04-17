#include <SDL2/SDL.h>

#include "headers/action.h"
#include "headers/gamemodes.h"

void playerMovement( Player *player, const unsigned char *keys )
{

	if( keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP] )
	{
		if( player -> body.y >= 0 )
			player -> body.y = player -> body.y - 10;
	}
						
	if( keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN] )
	{
		if( player -> body.y <= WINDOW_HEIGHT - player -> body.h )
			player -> body.y = player -> body.y + 10;
	}

	if( keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT] )
	{
		if( player -> body.x >= 0 )
			player -> body.x = player -> body.x - 10;
	}
						
	if( keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT] )
	{
		if( player -> body.x <= WINDOW_WIDTH - player -> body.w )
			player -> body.x = player -> body.x + 10;
	}
}

void playerShooting( Player *player, const unsigned char *keys, int *reload )
{
	if ( keys[SDL_SCANCODE_SPACE] )
	{
		if( *reload <= 0 )
		{
			*reload = 30;
			playerShoot( player );
		}
		else
		{
			--( *reload );
		}
	}
}

void playerShoot( Player *player )
{
	for( int i = 0; i < 30; ++i )
	{
		if( player -> bullets[i].w != 0)
			continue;

		player -> bullets[i].w = 20;
		player -> bullets[i].h = 20;
		player -> bullets[i].x = player -> body.x + player -> body.w / 2;
		player -> bullets[i].y = player -> body.y + player -> body.h / 2;
		break;
	}
}

