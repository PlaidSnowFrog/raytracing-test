#ifdef FORMULAE_HPP
#define FORMULAE_HPP
float find_gradient(int A[2], int B[2]);
int find_y(int origin_x, int a_x, float gradient);
void findCentreOfRect(int *x, int *y, SDL_Rect rect);

#endif