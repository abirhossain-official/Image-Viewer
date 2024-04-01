#include <SDL.h>
#include <SDL_image.h> // Include the SDL_image header

int main(int argc, char* argv[]) {
    // Initialize SDL and SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load an image
    SDL_Surface* tempSurface = IMG_Load("path/to/your/image.png");
    if (!tempSurface) {
        SDL_Log("Unable to load image: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface); // No longer need the surface

    // Main loop flag
    int quit = 0;
    SDL_Event e;

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);
        // Render texture to screen
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Free resources and close SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
