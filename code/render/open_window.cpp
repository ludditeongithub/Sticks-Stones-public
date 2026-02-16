#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>
#include <format>
#include <iostream>
#include <memory>

void initialize_sdl();
void close_sdl();

class Window
{
public:
    Window();

    void init();
    void run();

  constexpr static int width {800};
  constexpr static int height {600};
private:
    const std::string title;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};

Window::Window() : title{"Open Window"}, window{nullptr, SDL_DestroyWindow}, renderer{nullptr, SDL_DestroyRenderer} {}

void Window::init() {
  this->window.reset(SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0));
  if (!this->window) {
    auto error = std::format("Error Creating Window: {}", SDL_GetError());
    throw std::runtime_error(error);
  }

  this->renderer.reset(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (!this->window) {
    auto error = std::format("Error Creating Renderer: {}", SDL_GetError());
    throw std::runtime_error(error);
  }

}

void Window::run() {
  while (true) {
    SDL_RenderClear(this->renderer.get());

    SDL_RenderPresent(this->renderer.get());

    SDL_Delay(16);  // for 60fps  

    SDL_PollEvent();
  }
}

void initialize_sdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    auto error = std::format("Error initialize SDL_2: {}", SDL_GetError());
    throw std::runtime_error(error);
  }
}

void close_sdl() {
  SDL_Quit();
}

int main() {
  int exit_val = EXIT_SUCCESS;

  try {
    initialize_sdl();
    Window w;
    w.init();
    w.run();
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    exit_val = EXIT_FAILURE;
  }

  close_sdl();
  
  return exit_val;
}
