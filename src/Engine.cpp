#include "../include/Engine.h"
#include "Global.h"
#include "Logger.h"
#include "Renderer3D.h"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_render.h>

namespace TEM {
Engine::Engine(EngineConfig conf, Maze &maze, Player &player, Interface &ui,
               Renderer3D &renderer, MainMenu &mmenu)
    : conf(conf), ui(ui), maze(maze), player(player), _running(true),
      renderer(renderer), mmenu(mmenu), mouseX(0), mouseY(0) {
  console = tcod::Console{conf.windowWidth, conf.windowHeight};

  auto params = TCOD_ContextParams{};
  params.console = console.get();
  params.window_title = "The Elder Maze";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;
  context = tcod::Context(params);
  sdl_window = context.get_sdl_window();
  Audio::Init();
  Audio::Play((char *)"menu");
}

void Engine::Input() {
  SDL_Event event;

  float mx, my;
  SDL_MouseButtonFlags f = SDL_GetMouseState(&mx, &my);
  const bool *keystate = SDL_GetKeyboardState(NULL);
  HandleKeyboard(keystate);
  HandleMouse(f, mx, my);

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      Quit();
    default:
      break;
    }
  }
}

void Engine::Render() {
  console.clear();
  if (mmenu.IsActive) {
    mmenu.Render(console);
    int selected = mmenu.Update(mouseX, mouseY, mouseClick);
    if (selected >= 0) {
      switch (selected) {
      case 0:
        next_event = Event::NewGame;
        break;
      case 1:
        next_event = Event::LoadGame;
        break;
      case 2:
        next_event = Event::Quit;
        break;
      }
    }
  } else {
    renderer.RenderWalls(console, player, maze);
    ui.weapon_delta = static_cast<int>(abs(player.weapon_delta));
    ui.DrawWeapon(console);
    ui.DrawMap(console, maze, player);
    ui.DrawPlayerInfo(console, player);
    ui.DrawMessages(console);
  }
  context.present(console);
}

void Engine::Update() {
  player.UpdateAttack();
  player.UpdateStepTimer(0.1);
  switch (next_event) {
  case Event::Quit:
    Quit();
    break;
  case Event::ExitToMenu:
    Audio::Play((char *)"menu");
    mouseClick = false;
    mmenu.IsActive = true;
    next_event = Event::None;
    break;
  case Event::NewGame:
    Audio::Play((char *)"ambient");
    mouseClick = false;
    NewGame();
    mmenu.IsActive = false;
    next_event = Event::None;
    break;
  case Event::LoadGame:
    break;
  default:
    break;
  }
}

bool Engine::IsRunning() const { return _running; }

void Engine::NewGame() {
  maze.Generate();
  player.System.Position = {1.5, 1.5};
}

void Engine::HandleKeyboard(const bool *keystate) {
  if (keystate[SDL_SCANCODE_UP] ||
      keystate[SDL_SCANCODE_W] && !mmenu.IsActive) {
    if (player.CanStep())
      Audio::PlayOneShot((char *)"step");
    player.Move(maze, .025, 0.0);
  }
  if (keystate[SDL_SCANCODE_DOWN] ||
      keystate[SDL_SCANCODE_S] && !mmenu.IsActive) {
    if (player.CanStep())
      Audio::PlayOneShot((char *)"step");
    player.Move(maze, -.0125, 0.0);
  }
  if (keystate[SDL_SCANCODE_LEFT] ||
      keystate[SDL_SCANCODE_A] && !mmenu.IsActive) {
    if (player.CanStep())
      Audio::PlayOneShot((char *)"step");
    player.Move(maze, 0.0, .025);
  }
  if (keystate[SDL_SCANCODE_RIGHT] ||
      keystate[SDL_SCANCODE_D] && !mmenu.IsActive) {
    if (player.CanStep())
      Audio::PlayOneShot((char *)"step");
    player.Move(maze, 0.0, -.025);
  }
  if (keystate[SDL_SCANCODE_ESCAPE] && !mmenu.IsActive) {
    next_event = Event::ExitToMenu;
  }
  if (keystate[SDL_SCANCODE_SPACE] || mouseClick && !mmenu.IsActive) {
    if (player.Attack() != -1)
      player.weapon_delta = -75;
    mouseClick = false;
  }
}

void Engine::HandleMouse(SDL_MouseButtonFlags flags, float x, float y) {
  SDL_ShowCursor();
  int _w, _h;
  SDL_GetWindowSize(sdl_window, &_w, &_h);
  std::array<int, 2> mouse_cord = {static_cast<int>(x), static_cast<int>(y)};
  mouse_delta_x = (int)(_w / 2) - x;
  mouse_delta_y = (int)(_h / 2) - y;
  if (!mmenu.IsActive) {
    SDL_HideCursor();
    SDL_WarpMouseInWindow(sdl_window, (int)(_w / 2), (int)(_h / 2));
    player.Rotate(mouse_delta_x * conf.sensitivity / 1500.0);
  }
  std::array<int, 2> coord = context.pixel_to_tile_coordinates(mouse_cord);
  mouseX = coord[0];
  mouseY = coord[1];
  if (flags == 1) {
    mouseClick = true;
  }
}

void Engine::Quit() { _running = false; }

tcod::Console &Engine::GetConsole() { return console; }

} // namespace TEM
