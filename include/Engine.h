#ifndef ENGINE_H
#define ENGINE_H

#include "Audio.h"
#include "Enums.h"
#include "Interface.h"
#include "MainMenu.h"
#include "Maze.h"
#include "Player.h"
#include "Renderer3D.h"
#include <libtcod.hpp>
#include <libtcod/console.h>

namespace TEM {
struct EngineConfig {
  int windowWidth, windowHeight;
  double sensitivity;
};
class Engine {
private:
  EngineConfig conf;
  tcod::Console console;
  tcod::Context context;
  SDL_Window *sdl_window;
  std::vector<Entity> entities;

  Maze &maze;
  Player &player;
  Interface &ui;
  Renderer3D &renderer;
  MainMenu &mmenu;

  Event next_event;
  bool _running;

  int mouseX, mouseY;
  float mouse_delta_x, mouse_delta_y;
  bool mouseClick;

  void HandleKeyboard(const bool *keystate);
  void HandleMouse(SDL_MouseButtonFlags flags, float x, float y);
  void Quit();
  void NewGame();

public:
  Engine(EngineConfig conf, Maze &maze, Player &player, Interface &ui,
         Renderer3D &renderer, MainMenu &mmenu);

  void Input();
  void Render();
  void Update();
  tcod::Console &GetConsole();
  bool IsRunning() const;
};
} // namespace TEM

#endif // ENGINE_H
