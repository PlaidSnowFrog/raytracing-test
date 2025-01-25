#include "formulae/formulae.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

int findGradient(int xa, int ya, int xb, int yb) {
  return ((ya - yb) / (xa - xb));
}

int findY(int originX, int aX, int gradient) {
  int finalX = aX - originX;

  return gradient * finalX;
}

void findCentreOfRect(int *x, int *y, SDL_Rect rect) {
  // Check if pointers are valid
  if (x != NULL && y != NULL) {
    // Calculate center point
    *x = (rect.x + (rect.w / 2));
    *y = (rect.y + (rect.h / 2));
  } else {
    // Handle invalid pointer case
    printf("Error: Invalid pointer passed\n");
  }
}

void drawLines(int originX, int originY, const SDL_Rect *intersectRect,
               SDL_Renderer *renderer, int SCREENWIDTH, int SCREENHEIGHT) {
  // loops
  for (int i = 0; i <= SCREENWIDTH; i += 5) {
    int endX = i;
    int endY = SCREENHEIGHT;
    
    // Check for intersection before drawing the line
    if (SDL_IntersectRectAndLine(intersectRect, &originX, &originY, &endX, &endY) == SDL_FALSE) {
      SDL_RenderDrawLine(renderer, originX, originY, endX, endY);
    }
  }

  for (int i = SCREENWIDTH; i >= 0; i -= 5) {
    int endX = i;
    int endY = 0;

    // Check for intersection before drawing the line
    if (SDL_IntersectRectAndLine(intersectRect, &originX, &originY, &endX, &endY) == SDL_FALSE) {
      SDL_RenderDrawLine(renderer, originX, originY, endX, endY);
    }
  }

  for (int i = 0; i <= SCREENHEIGHT; i += 5) {
    int endX = SCREENWIDTH;
    int endY = i;

    // Check for intersection before drawing the line
    if (SDL_IntersectRectAndLine(intersectRect, &originX, &originY, &endX, &endY) == SDL_FALSE) {
      SDL_RenderDrawLine(renderer, originX, originY, endX, endY);
    }
  }

  for (int i = SCREENHEIGHT; i >= 0; i -= 5) {
    int endX = 0;
    int endY = i;

    // Check for intersection before drawing the line
    if (SDL_IntersectRectAndLine(intersectRect, &originX, &originY, &endX, &endY) == SDL_FALSE) {
      SDL_RenderDrawLine(renderer, originX, originY, endX, endY);
    }
  }
}


int main() {
  const int SCREENWIDTH = 600;
  const int SCREENHEIGHT = 400;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("raytracing", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, SCREENWIDTH,
                                        SCREENHEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect rect = {400, 200, 50, 50};
  SDL_Rect lightSource = {200, 200, 50, 50};

  int centreYLightSource;
  int centreXLightSource;
  int finalY;

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
    findCentreOfRect(&centreXLightSource, &centreYLightSource, lightSource);
    gradient =
        findGradient(centreXLightSource, centreYLightSource, rect.x, rect.y);
    finalY = findY(centreXLightSource, centreYLightSource, gradient);

    // Draw
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    drawLines(centreXLightSource, centreYLightSource, &rect, renderer,
              SCREENWIDTH, SCREENHEIGHT);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &lightSource);

    SDL_RenderPresent(renderer);

    SDL_Delay(25);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
