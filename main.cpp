#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include "formulae/formulae.hpp"

#include <iostream>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       600, 400, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect rect = {400, 200, 50, 50};
  SDL_Rect lightSource = {200, 200, 50, 50};

  int gradient;
  int intersections[2];

  bool running = true;

  while (running) { // Game Loop
    SDL_Event event;

    // event listener
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: // close window
        running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&lightSource.x, &lightSource.y);
        break;
      }
    }
    
    // Game Logic
    //gradient = findGradient();

    // TODO: Get rect center and use coordinates of that to find the intersections with
    //      the edge of the screen and then use those and the edges of the rect to 
    //      cast shadows

    // Draw
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &lightSource);

    SDL_RenderPresent(renderer);

    SDL_Delay(10);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
