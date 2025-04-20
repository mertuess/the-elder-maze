#include "MainMenu.h"
#include "include/Engine.h"
#include "include/Logger.h"
#include <iostream>
#include <toml++/toml.hpp>

using namespace std::literals;

int main(int argc, char *argv[]) {
  TEM::Logger::Print("Reading configuration file from ./config.toml\n");
  try {
    auto config = toml::parse_file("config.toml");
    TEM::Logger::Print("Config readed!\nCurrent config:\n\n");
    std::cout << config << "\n\n";

    TEM::Maze maze(config["maze"]["width"].value_or(8),
                   config["maze"]["height"].value_or(8));

    TEM::Player player(TEM::Creature(TEM::Entity({{1.5, 1.5}, .0}), "You"));

    TEM::Interface ui({5, 5, 11});
    TEM::MainMenu menu;
    TEM::Renderer3D renderer;
    TEM::Engine engine({config["window"]["width"].value_or(50),
                        config["window"]["height"].value_or(25),
                        config["input"]["sensitivity"].value_or(1.0)},
                       maze, player, ui, renderer, menu);

    TEM::Audio::SetMusicVolume(config["audio"]["music_volume"].value_or(1.0));
    TEM::Audio::SetSoundsVolume(config["audio"]["sounds_volume"].value_or(1.0));

    while (engine.IsRunning()) {
      engine.Input();
      engine.Render();
      engine.Update();
      TEM::Audio::Update();
    }

  } catch (const std::exception &ex) {
    TEM::Logger::Print("Exception catched: {0}", ex.what());
  }
  return 1;
}
