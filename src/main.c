#include <SDL.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("toto");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    char str[20];
    scanf("%1s", str);
    return 0;
}