#include <SDL2/SDL.h>
#include <common.h>
#include <universe.h>

#include <iostream>

// function `log` and SDL usage were modified from 
// Tyler Brock's implementation of 
// Conway's Game of Life which is published under MIT license: 
// https://github.com/TylerBrock/game-of-life

inline void log(const std::string& msg) {
  std::cout << "[  Langton's Ant  ] " << msg << std::endl;
}

int main() {
  log("initializing...");

  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Init(SDL_INIT_VIDEO);

  log("creating window...");
  window = SDL_CreateWindow("Langton's Ant", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE,
                            HEIGHT * SCALE, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    log("cannot create window.\n SDL_Error: " + std::string(SDL_GetError()));
    return 1;
  }

  log("creating renderer...");
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_RenderClear(renderer);

  log("creating texture...");
  SDL_Texture* texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  Universe universe(HEIGHT, WIDTH, INIT_ROW, INIT_COL, INIT_DIR);
  SDL_UpdateTexture(texture, NULL, universe.output(ON_COLOR, OFF_COLOR).get(),
                    WIDTH * sizeof(uint32_t));

  bool quit = false;
  uint32_t step = 0;

  SDL_Event event;
  cells_output_t cells_output;

  while (!quit) {
    step++;

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      quit = true;
    }

    if (!quit) {
      log(std::to_string(step) + ": evolving to next generation...");
      universe.evolve();
      SDL_UpdateTexture(texture, NULL,
                        universe.output(ON_COLOR, OFF_COLOR).get(),
                        WIDTH * sizeof(uint32_t));
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
