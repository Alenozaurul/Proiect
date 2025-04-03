#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>


const int screen_width = 1024;
const int screen_height = 768;

int gamemode = -1;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool Init();
void Quit();
bool Loop();

int main( int argc, char **argv )
{	
	system("cat begin.txt");
	
	while( gamemode )
	{
		printf("Gamemode: ");
		scanf("%i", &gamemode);
		printf("\n");
		
		switch( gamemode )
		{
			case 1:
				if( !Init() )
					return 1;

				while( Loop() )
				{
					;
				}
				
				Quit();
				break;

			case 2:
				if( !Init() )
					return 1;

				while( Loop() )
				{
					;
				}
				
				Quit();
				break;
		}


	}

	return 0;
}

bool Init()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow( "Alien Invasion", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );

	if( !window )
	{	
		printf("%s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	if( !renderer )
	{	
		printf("%s\n", SDL_GetError());
		return false;
	}

	return true;
}

void Quit()
{
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}

bool Loop()
{
	const unsigned char *keys = SDL_GetKeyboardState( NULL );
	SDL_Event event;


	return true;
}

