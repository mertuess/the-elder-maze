#ifndef ENGINE_H
#define ENGINE_H

#include "Interface.h"
#include "MainMenu.h"
#include "Maze.h"
#include "Player.h"
#include "Renderer3D.h"
#include <SDL3/SDL.h>
#include <libtcod.hpp>
#include <libtcod/console.h>

namespace TEM {
struct EngineConfig {
  int windowWidth, windowHeight;
};
class Engine {
private:
  EngineConfig conf;
  tcod::Console console;
  tcod::Context context;
  std::vector<Entity> entities;

  Maze &maze;
  Player &player;
  Interface &ui;
  Renderer3D &renderer;
  MainMenu &mmenu;

  Event next_event;
  bool _running;

  int mouseX, mouseY;
  bool mouseClick;

  void HandleKeydownEvent(const SDL_Event &event);
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
