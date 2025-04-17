#ifndef __SDL_H__
#define __SDL_H__


#include "spaceships.h"

SDL_Renderer *InitRenderer( SDL_Window *window);
TTF_Font *InitFont();
SDL_Window *InitWindow();
void Quit( SDL_Window *window, SDL_Renderer *renderer);
bool Loop( SDL_Window *window, SDL_Renderer *renderer, Player *player, int *reload);
bool StartGame( TTF_Font *font, SDL_Renderer *renderer);

#endif
