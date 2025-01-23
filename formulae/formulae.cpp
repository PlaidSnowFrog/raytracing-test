#include "formulae.hpp"
#include <SDL2/SDL.h>

int findGradient(int A[2], int B[2]) {
    return ((A[1] - B[1]) / (A[0] - B[0]));
}

int findY(int originX, int aX, float gradient) {
    int finalX = {aX-originX};
     
    return gradient*finalX;
}

void findCentreOfRect(int *x, int *y, SDL_Rect rect) {
    x = (rect.x + (rect.w/2);
    y = (rect.y + (rect.h/2);
}