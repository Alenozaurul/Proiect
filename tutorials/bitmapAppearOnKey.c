#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>
#include <unistd.h>
bool sdl_Init();
bool sdl_Load();
void sdl_Kill();
bool trueLoop();

SDL_Surface *windowSurface = NULL;
SDL_Window *window = NULL;
SDL_Surface *image1, *image2;



int main(int argc, char **argv)
{
	if( !sdl_Init() )
		return 1;

	if( !sdl_Load() )
		return 2;

	while ( trueLoop() )
	{
		SDL_Delay(20);
	}

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

bool trueLoop()
{
	static bool renderImage2;
	SDL_Event e;

	SDL_BlitSurface( image1, NULL, windowSurface, NULL );

	while( SDL_PollEvent( &e ) != 0 )
	{
		switch( e.type )
		{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				renderImage2 = true;
				break;
			case SDL_KEYUP:
				renderImage2 = false;
			case SDL_MOUSEMOTION:
				break;
		}
	}

	if( renderImage2 )
	{
		SDL_Rect dest;
		dest.x = 160;
		dest.y = 120;
		dest.h = 240;
		dest.w = 320;
		SDL_BlitScaled( image2, NULL, windowSurface, &dest);
	}

	SDL_UpdateWindowSurface( window );

	return true;
}

void sdl_Kill()
{
	SDL_DestroyWindow( window );
	SDL_FreeSurface( image1 );
	SDL_FreeSurface( image2 );
	SDL_Quit();
}
