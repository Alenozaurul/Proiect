#ifndef __SDL_H__
#define __SDL_H__

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768 


SDL_Renderer *InitRenderer( SDL_Window *window);
TTF_Font *InitFont();
SDL_Window *InitWindow();
void Quit( SDL_Window *window, SDL_Renderer *renderer);

bool StartGame( TTF_Font *font, SDL_Renderer *renderer );

#endif
