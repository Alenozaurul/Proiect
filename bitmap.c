#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>
#include <unistd.h>
bool sdl_Init();
bool sdl_Load();
void sdl_Kill();


SDL_Surface *windowSurface = NULL;
SDL_Window *window = NULL;
SDL_Surface *image1, *image2;



int main(int argc, char **argv)
{
	if( !sdl_Init() )
		return 1;

	if( !sdl_Load() )
		return 2;


	SDL_BlitSurface( image1, NULL, windowSurface, NULL );
		
	SDL_Rect dest;
	dest.x = 160;
	dest.y = 120;
	dest.w = 320;
	dest.h = 240;
	SDL_BlitScaled( image2, NULL, windowSurface, &dest );

	SDL_UpdateWindowSurface( window );
	system( "bash -c 'read -r -p \"Press something\" -n 1 ' " );

	sdl_Kill();
	return 0;
}

bool sdl_Init()
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

bool sdl_Load()
{
	SDL_Surface *temp1, *temp2;
	
	temp1 = SDL_LoadBMP("test1.bmp");
	temp2 = SDL_LoadBMP("test2.bmp");

	if( !temp1 || !temp2 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	image1 = SDL_ConvertSurface( temp1, windowSurface -> format, 0 );
	image2 = SDL_ConvertSurface( temp2, windowSurface -> format, 0 );

	SDL_FreeSurface( temp1 );
	SDL_FreeSurface( temp2 );

	if( !image1 || !image2 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	return true;
}

void sdl_Kill()
{
	SDL_DestroyWindow( window );
	SDL_Quit();
}
