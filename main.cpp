#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <libtcod.hpp>

int main(int argc, char *argv[]) {
  auto console = tcod::Console{100, 50}; // Main console.

  auto params = TCOD_ContextParams{};
  params.console =
      console.get(); // Derive the window size from the console size.
  params.window_title = "The Elder Maze";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;
  params.argc = argc; // This allows some user-control of the context.
  params.argv = argv;

  // Set up a font
  auto tileset =
      tcod::load_tilesheet("./resources/fonts/terminal16x16_gs_ro.png",
                           {16, 16}, tcod::CHARMAP_CP437);
  params.tileset = tileset.get();

  auto context = tcod::Context(params);

  while (1) {
    console.clear();
    tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
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
