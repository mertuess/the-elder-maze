#include "../include/Engine.h"
#include "Renderer3D.h"

namespace TEM {
Engine::Engine(EngineConfig conf, Maze &maze, Player &player, Interface &ui,
               Renderer3D &renderer, MainMenu &mmenu)
    : conf(conf), ui(ui), maze(maze), player(player), _running(true),
      renderer(renderer), mmenu(mmenu) {
  console = tcod::Console{conf.windowWidth, conf.windowHeight};

  auto params = TCOD_ContextParams{};
  params.console = console.get();
  params.window_title = "The Elder Maze";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;

  context = tcod::Context(params);
}

void Engine::Input() {
  SDL_Event event{};

  SDL_WaitEvent(&event);

  switch (event.type) {
  case SDL_EVENT_QUIT:
    next_event = Event::Quit;
    break;
  case SDL_EVENT_KEY_DOWN:
    HandleKeydownEvent(event);
    break;
  case SDL_EVENT_MOUSE_MOTION:
    mouseX = event.motion.x / 8;
    mouseY = event.motion.y / 8;
    break;
  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      mouseX = event.button.x / 8;
      mouseY = event.button.y / 8;
      mouseClick = true;
    }
    break;
  default:
    next_event = Event::None;
    break;
  }

  SDL_FlushEvent(SDL_EVENT_KEY_DOWN);
}

void Engine::Render() {
  console.clear();
  if (mmenu.IsActive) {
    mmenu.Render(console);
    int selected = mmenu.Update(mouseX, mouseY, mouseClick);
    if (selected >= 0) {
      switch (selected) {
      case 0: // New Game
        next_event = Event::NewGame;
        break;
      case 1: // Load Game
        next_event = Event::LoadGame;
        break;
      case 2: // Exit
        next_event = Event::Quit;
        break;
      }
    }
  } else {
    renderer.RenderWalls(console, player, maze);
    ui.OutMap(console, maze, player);
  }
  context.present(console);
}

void Engine::Update() {
  switch (next_event) {
  case Event::MoveUp:
    player.Move(maze, .1);
    break;
  case Event::MoveDown:
    player.Move(maze, -.05);
    break;
  case Event::MoveLeft:
    player.Rotate(.025);
    break;
  case Event::MoveRight:
    player.Rotate(-.025);
    break;
  case Event::Quit:
    Quit();
    break;
  case Event::ExitToMenu:
    mouseClick = false;
    mmenu.IsActive = true;
    break;
  case Event::NewGame:
    mouseClick = false;
    NewGame();
    mmenu.IsActive = false;
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
  player.Position = {1.5, 1.5};
  player.level = 1;
  player.exp = 0;
  player.Inventory = {};
  player.health = 100;
}

void Engine::HandleKeydownEvent(const SDL_Event &event) {
  TEM::Logger::Print("Pressed key: {}\n", event.key.key);
  switch (event.key.key) {
  case SDLK_UP:
    next_event = Event::MoveUp;
    break;
  case SDLK_DOWN:
    next_event = Event::MoveDown;
    break;
  case SDLK_LEFT:
    next_event = Event::MoveLeft;
    break;
  case SDLK_RIGHT:
    next_event = Event::MoveRight;
    break;
  case SDLK_W:
    next_event = Event::MoveUp;
    break;
  case SDLK_S:
    next_event = Event::MoveDown;
    break;
  case SDLK_A:
    next_event = Event::MoveLeft;
    break;
  case SDLK_D:
    next_event = Event::MoveRight;
    break;
  case SDLK_ESCAPE:
    next_event = Event::ExitToMenu;
    break;
  }
}

void Engine::Quit() { _running = false; }

tcod::Console &Engine::GetConsole() { return console; }

} // namespace TEM
