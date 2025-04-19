#ifndef __SPACESHIPS_H__
#define __SPACESHIPS_H__

#include <SDL2/SDL.h>

typedef struct{
	int health;
	int atack;
	SDL_Rect body;
	SDL_Rect bullets[30];
} Player;

typedef struct{
	int health;
	int atack;
	SDL_Rect body;
	SDL_Rect bullets[30];
}Enemy;


#endif
