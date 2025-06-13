/**
 * @file Interface.h
 * @brief Заголовочный файл пользовательского интерфейса
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "Maze.h"
#include "Player.h"
#include "Structs.h"
#include <fmt/core.h>
#include <libtcod.h>

namespace TEM {
/**
 * @struct InterfaceConfig
 * @brief Конфигурация интерфейса
 */
struct InterfaceConfig {
  short minimap_position_x, minimap_position_y; ///< Позиция миникарты
  int panel_size = 20; ///< Размер панели интерфейса
};

/**
 * @class Interface
 * @brief Класс для управления пользовательским интерфейсом
 */
class Interface {
private:
  int panel_size; ///< Размер панели интерфейса
  std::vector<std::vector<std::string>> asciiLines; ///< ASCII-графика
  const TCOD_ColorRGB COLOR_BG = {79, 32, 15}; ///< Цвет фона
  const TCOD_ColorRGB COLOR_FG = {188, 106, 60}; ///< Цвет переднего плана
  const TCOD_ColorRGB COLOR_DARK = {56, 23, 11}; ///< Темный цвет

public:
  /**
   * @brief Конструктор интерфейса
   * @param config Конфигурация интерфейса
   */
  Interface(InterfaceConfig config);
  
  Point2D MapPosition; ///< Позиция карты
  int weapon_delta; ///< Смещение оружия

  /**
   * @brief Рендерит карту
   * @param console Консоль для рендеринга
   * @param map Лабиринт
   * @param player Игрок
   */
  void DrawMap(tcod::Console &console, Maze &map, Player &player);
  
  /**
   * @brief Рендерит информацию об игроке
   * @param console Консоль для рендеринга
   * @param player Игрок
   */
  void DrawPlayerInfo(tcod::Console &console, Player &player);
  
  /**
   * @brief Рендерит сообщения
   * @param console Консоль для рендеринга
   */
  void DrawMessages(tcod::Console &console);
  
  /**
   * @brief Рендерит оружие
   * @param console Консоль для рендеринга
   */
  void DrawWeapon(tcod::Console &console);
};
} // namespace TEM
#endif // INTERFACE_H
