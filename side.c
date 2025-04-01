#include<stdbool.h>
#include<stdio.h>
#include<SDL2/SDL.h>
#include <unistd.h>
bool sdl_Init();
void sdl_Kill();
bool trueLoop();

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;



int main(int argc, char **argv)
{
	if( !sdl_Init() )
		return 1;
	while ( trueLoop() )
	{
		SDL_Delay(5);
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
			SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN );

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

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	return true;
}

bool trueLoop()
{
	const static unsigned char* keys = NULL;
	keys = SDL_GetKeyboardState( NULL );

	SDL_Event e;
	SDL_Rect r;
	// For mouse rectangle (static to presist between function calls)
	static int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

	// Clear the window to white
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	// Event loop
	while ( SDL_PollEvent( &e ) != 0 ) {
		switch ( e.type ) {
			case SDL_QUIT:
				return false;
			case SDL_MOUSEBUTTONDOWN:
				mx0 = e.button.x;
				my0 = e.button.y;
				break;
			case SDL_MOUSEMOTION:
				mx1 = e.button.x;
				my1 = e.button.y;
				break;
			case SDL_MOUSEBUTTONUP:
				mx0 = my0 = mx1 = my1 = -1;
				break;
		}
	}

	// Set drawing color to black
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

	// Test key states - this could also be done with events
	if ( keys[SDL_SCANCODE_1] ) {
		SDL_RenderDrawPoint( renderer, 10, 10 );
	}
	if ( keys[SDL_SCANCODE_2] ) {
		SDL_RenderDrawLine( renderer, 10, 20, 10, 100 );
	}
	if ( keys[SDL_SCANCODE_3] ) {
		r.x = 20;
		r.y = 20;
		r.w = 100;
		r.h = 100;
		SDL_RenderFillRect( renderer, &r );
	}

	// Render mouse rectangle
	if ( mx0 != -1 ) {
		r.x = mx0;
		r.y = my0;
		r.w = mx1 - mx0;
		r.h = my1 - my0;
		SDL_RenderDrawRect( renderer, &r );
	}

	// Update window
	SDL_RenderPresent( renderer );
	return true;
}

void sdl_Kill()
{
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_Quit();
}
