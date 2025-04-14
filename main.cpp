#include "include/Maze.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <libtcod.hpp>
#include <libtcod/console.h>

int main(int argc, char *argv[]) {
  TEM::Maze maze(16, 16);
  maze.Generate();

  auto console = tcod::Console{200, 100}; // Main console.

  auto params = TCOD_ContextParams{};
  params.console =
      console.get(); // Derive the window size from the console size.
  params.window_title = "The Elder Maze";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;
  params.argc = argc; // This allows some user-control of the context.
  params.argv = argv;

  auto context = tcod::Context(params);

  while (1) {
    console.clear();
    for (int h = 0; h < maze.GetH(); h++) {
      for (int w = 0; w < maze.GetW(); w++) {
        console.at({w, h}).ch = maze.View[h * maze.GetW() + w];
      }
    }

    context.present(console); // Updates the visible display.

    SDL_Event event;
    SDL_WaitEvent(nullptr); // Optional, sleep until events are available.
    while (SDL_PollEvent(&event)) {
      context.convert_event_coordinates(
          event); // Optional, converts pixel coordinates into tile coordinates.
      switch (event.type) {
      case SDL_EVENT_QUIT:
        return 0; // Exit.
      }
    }
  }
}
