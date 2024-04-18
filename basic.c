#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Cube SVG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Load SVG image
    SDL_Surface* surface = IMG_Load("cube.svg");
    if (surface == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        printf("IMG_Load Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Convert surface to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Clear the window
    SDL_RenderClear(renderer);

    // Draw the texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Render to the screen
    SDL_RenderPresent(renderer);

    // Wait for user to close the window
    SDL_Event e;
    while (1) {
        if (SDL_PollEvent(&e) && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN))
            break;
        SDL_Delay(100);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
