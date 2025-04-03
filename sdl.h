#ifndef __SDL_H__
#define __SDL_H__

SDL_Renderer *InitRenderer( SDL_Window *window);
SDL_Window *InitWindow();
void Quit( SDL_Window *window, SDL_Renderer *renderer);

#endif
