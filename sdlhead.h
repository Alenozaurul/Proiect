#ifndef __SDLHEAD_H__
#define __SDLHEAD_H__

bool sdl_Init( SDL_Surface *windowSurface, SDL_Window *window);
bool sdl_Load();
void sdl_Kill( SDL_Window *window );

#endif
