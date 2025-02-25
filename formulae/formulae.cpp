#include "formulae.hpp"
#include <SDL2/SDL.h>

int findGradient(int xa, int ya, int xb, int yb) {
  return ((ya - yb) / (xa - xb));
}

int findY(int originX, int aX, float gradient) {
  int finalX = {aX - originX};

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