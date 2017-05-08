#include <cstdio>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    printf("SDL_Init: %d\n", SDL_Init(SDL_INIT_VIDEO));
    return 0;
}
