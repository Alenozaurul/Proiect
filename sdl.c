#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "headers/action.h"
#include "headers/enemy.h"
#include "headers/sdl.h"
#include "headers/spaceships.h"
#include "headers/gamemodes.h"

int speed = 20;

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

int sc = -1;
int base_hp = -1;
int hp = -1;

bool Loop(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, Player *player, Enemy *enemy, int *reload,
	       	int *reload_enemy, int *respawn, int *base_health, int *score, int *time, SDL_Rect *buff)
{
	if( base_health <= 0 )
		return false;

	const unsigned char *keys = SDL_GetKeyboardState( NULL );
	SDL_Event event;
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
 	SDL_RenderClear ( renderer );
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	
	renderer = ShowScore( window, renderer, font, score );
	renderer = ShowPlayerHealth( window, renderer, player, font );
	renderer = ShowBaseHealth( window, renderer, font, base_health );

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	if( player -> health < 70 )
		SDL_SetRenderDrawColor( renderer, 217, 217, 217, 255 );
	if( player -> health < 50 )
		SDL_SetRenderDrawColor( renderer, 135, 135, 135, 255 );
	if( player -> health < 30 )
		SDL_SetRenderDrawColor( renderer, 69, 69, 69, 255 );
	
	SDL_RenderFillRect( renderer, &( player -> body ) );

	for( int i = 0; i < 20; ++i )
	{
		if( player -> bullets[i].w > 0 )
		{
			SDL_RenderFillRect( renderer, &( player -> bullets[i] ) );
		}
	}

	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_QUIT: 
				return false;
				break;
		}
	}	
	playerMovement( player, keys );
	playerShooting( player, keys, reload, speed );
	spawnEnemy( enemy, respawn );
	enemyShooting( enemy, reload_enemy );
	
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
	for( int i = 0; i < 20; ++i )
	{
		if( player -> bullets[i].w > 0 )
		{
			player -> bullets[i].y -= 10;
			for( int j = 0; j < 20; ++j )
			       if( enemy[j].body.w > 0 )
			       {
					checkCollPB( player, &enemy[j], i, score );
			       }
			SDL_RenderFillRect( renderer, &( player -> bullets[i] ) );
		}
		if( player -> bullets[i].y < 0 )
		{
			player -> bullets[i].w = 0;
			player -> bullets[i].h = 0;
		}
	}
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	for( int i = 0; i < 20; ++i )
	{	
		if( enemy[i].body.y >= WINDOW_HEIGHT && enemy[i].body.w > 0 )
		{
			enemy[i].body.w = 0;
			enemy[i].body.h = 0;
			*base_health -= 150;		
		}
		if( enemy[i].body.w > 0 )
		{
			enemy[i].body.y += 1;
			if( enemy[i].health <= 30 )
				SDL_SetRenderDrawColor( renderer, 56, 15, 64, 255 );
			if( enemy[i].health <= 60 )
				SDL_SetRenderDrawColor( renderer, 116, 30, 133, 255 );
			else
				SDL_SetRenderDrawColor( renderer, 169, 43, 194, 255 );
			SDL_RenderFillRect( renderer, &( enemy[i].body ) );
			SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
			
			if( playerEnemy( player, &enemy[i] ) )
				return false;
		}
		for( int j = 0; j < 20; ++j )
		{
			if( enemy[i].bullets[j].y >= WINDOW_HEIGHT && enemy[i].bullets[j].w > 0)
			{
				enemy[i].bullets[j].w = 0;
				enemy[i].bullets[j].h = 0;
				*base_health -= enemy[i].atack;
			}
				
			if( enemy[i].bullets[j].w > 0 )
			{
				if( checkColl( &enemy[i], player, j ) )
				{
					enemy[i].bullets[j].w = 0;
					enemy[i].bullets[j].h = 0;
					player -> health -= enemy[i].atack;	
					break;
				}
				enemy[i].bullets[j].y += 2;
				SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
				SDL_RenderFillRect( renderer, &( enemy[i].bullets[j] ) );
				SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
			}
		}
	}


		SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
		if( *time <= 0 )
		{
			*time = 800;
			buff -> x = ( rand() % 970 ) + 50;
			buff -> y = 300 + ( rand() % 300 );
			buff -> w = 50;
			buff -> h = 50;
		}
		if( buff -> w > 0 && ( rand() % 10 ) % 6 == 0 )
		{
			--buff -> w;
			--buff -> h;
		}
		if( buff -> x <= 0 )
		{
			buff -> x = 0;
			buff -> y = 0;
			buff -> w = 0;
			buff -> h = 0;
		}
		if( *time <= 400 )
			speed = 20;
		--*time;
		if( buff -> w > 0 )
		{
			SDL_RenderFillRect( renderer, buff );
			if( coll( player, buff ) )
			{
				buff -> w = 0;
				buff -> h = 0;
				*score += 100;
				speed = 10;
			}
		}


	SDL_RenderPresent( renderer );
	SDL_Delay(10);
	
	if( keys[SDL_SCANCODE_ESCAPE] )
	{
		return false;
	}
	
	if( player -> health <= 0 )
		 return false;

	return true;
}
bool coll( Player *player, SDL_Rect *enemy )
{
	if( player -> body.x > enemy -> x + enemy -> w )
		return false;
	if( player -> body.x + player -> body.w < enemy -> x )
		return false;
	if( player -> body.y > enemy -> h + enemy -> y )
		return false;
	if( player -> body.y + player -> body.h < enemy -> y )
		return false;

	return true;
}

SDL_Renderer *ShowScore( SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int *score )
{
	char sc[12];
	sprintf( sc, "%i", *score );

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid( font, sc, color );
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
	
	SDL_Rect text = { WINDOW_WIDTH - 150, 10, textSurface -> w, textSurface -> h };
	SDL_RenderCopy( renderer, textTexture, NULL, &text );

	return renderer;	
}

SDL_Renderer *ShowPlayerHealth( SDL_Window *window, SDL_Renderer *renderer, Player *player, TTF_Font *font )
{
	char health[4];
	sprintf( health, "%i", player -> health );

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid( font, health, color );
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
	
	SDL_Rect text = { 10, 10, textSurface -> w, textSurface -> h };
	SDL_RenderCopy( renderer, textTexture, NULL, &text );	
	return renderer;	
}

SDL_Renderer *ShowBaseHealth( SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, int *base_health )
{
	char health[5];
	sprintf( health, "%i", *base_health );

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid( font, health, color );
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
	
	SDL_Rect text = { 100, 10, textSurface -> w, textSurface -> h };
	SDL_RenderCopy( renderer, textTexture, NULL, &text );
	return renderer;	
}


bool playerEnemy( Player *player, Enemy *enemy )
{
	if( player -> body.x > enemy -> body.x + enemy -> body.w )
		return false;
	if( player -> body.x + player -> body.w < enemy -> body.x )
		return false;
	if( player -> body.y > enemy -> body.h + enemy -> body.y )
		return false;
	if( player -> body.y + player -> body.h < enemy -> body.y )
		return false;

	return true;
}
bool checkColl( Enemy *enemy, Player *player, int j )
{
	if( player -> body.x + player -> body.w < enemy -> bullets[j].x )
		return false;

	if( player -> body.x > enemy -> bullets[j].x + enemy -> bullets[j].w)
		return false;
	
	if( player -> body.y + player -> body.h < enemy -> bullets[j].y )
		return false;
	
	if( player -> body.y > enemy -> bullets[j].y + enemy -> bullets[j].h )
		return false;
	
	return true;
}

void checkCollPB( Player *player, Enemy *enemy, int i, int *score )

{
	if( player -> bullets[i].x > enemy -> body.x + enemy -> body.w )
		return;
	if( player -> bullets[i].x + player -> bullets[i].w < enemy -> body.x )
		return;
	if( player -> bullets[i].y > enemy -> body.y + enemy -> body.h )
		return;
	if( player -> bullets[i].h + player -> bullets[i].y < enemy -> body.y )
		return;

	enemy -> health -= player -> atack; 
	player -> bullets[i].w = 0;
	player -> bullets[i].h = 0;
	*score += 15;

	if( enemy -> health <= 0)
	{
		enemy -> body.w = 0;
		enemy -> body.h = 0;
		*score += 100;
	}

}

void Quit( SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}

