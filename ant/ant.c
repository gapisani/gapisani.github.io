#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define W 1000
#define H 700

#define ANTS_COUNT 1000

int main(int argc, char** argv) {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(W, H, 0, &window, &renderer);
    static SDL_Color space[W][H];
    for(int x = 0; x < W; x++) {
        for(int y = 0; y < H; y++) {
            space[x][y] = (SDL_Color) { 0 };
        }
    }
    struct {
        int x, y, direction;
        SDL_Color color;
    } ants[ANTS_COUNT];
    for(int i=0; i < ANTS_COUNT; i++) {
        ants[i].x = rand() % W;
        ants[i].y = rand() % H;
        ants[i].color.r = rand() % 255;
        ants[i].color.g = rand() % 255;
        ants[i].color.b = rand() % 255;
    }
    bool running = true;
    while(running) {
        for(int i=0; i<ANTS_COUNT; i++) {
            switch(ants[i].direction) {
            case(0):
                ants[i].y += 1;
                break;
            case(1):
                ants[i].x += 1;
                break;
            case(2):
                ants[i].y -= 1;
                break;
            case(3):
                ants[i].x -= 1;
                break;
            }
            if(ants[i].x < 0) ants[i].x = W-1;
            if(ants[i].y < 0) ants[i].y = H-1;
            if(ants[i].x >= W) ants[i].x = 0;
            if(ants[i].y >= H) ants[i].y = 0;
            if(space[ants[i].x][ants[i].y].a) ants[i].direction++;
            else ants[i].direction--;
            if(ants[i].direction < 0) ants[i].direction = 3;
            if(ants[i].direction > 3) ants[i].direction = 0;
            space[ants[i].x][ants[i].y].a = 1 - space[ants[i].x][ants[i].y].a;
            space[ants[i].x][ants[i].y].r = ants[i].color.r;
            space[ants[i].x][ants[i].y].g = ants[i].color.g;
            space[ants[i].x][ants[i].y].b = ants[i].color.b;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for(int x=0; x < W; x++) {
            for(int y=0; y < H; y++) {
                if(space[x][y].a) {
                    SDL_SetRenderDrawColor(renderer, space[x][y].r, space[x][y].g, space[x][y].b, space[x][y].a);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case(SDL_QUIT):
                running = false;
                break;
            }
        }
    }
    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return(0);
}
