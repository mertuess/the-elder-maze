/**
 * @file Engine.h
 * @brief Заголовочный файл игрового движка
 */
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
/**
 * @struct EngineConfig
 * @brief Конфигурация движка
 */
struct EngineConfig {
  int windowWidth, windowHeight; ///< Размеры окна
  double sensitivity; ///< Чувствительность управления
};

/**
 * @class Engine
 * @brief Основной класс игрового движка
 */
class Engine {
private:
  EngineConfig conf; ///< Конфигурация
  tcod::Console console; ///< Консоль для рендеринга
  std::vector<Entity> entities; ///< Список сущностей

public:
  /**
   * @brief Конструктор движка
   * @param conf Конфигурация
   * @param maze Лабиринт
   * @param player Игрок
   * @param ui Интерфейс
   * @param renderer Рендерер
   * @param mmenu Главное меню
   */
  Engine(EngineConfig conf, Maze &maze, Player &player, Interface &ui,
         Renderer3D &renderer, MainMenu &mmenu);

  /**
   * @brief Обрабатывает ввод
   */
  void Input();
  
  /**
   * @brief Выполняет рендеринг
   */
  void Render();
  
  /**
   * @brief Обновляет состояние игры
   */
  void Update();
  
  /**
   * @brief Получает консоль
   * @return Ссылка на консоль
   */
  tcod::Console &GetConsole();
  
  /**
   * @brief Проверяет, работает ли движок
   * @return true если работает, иначе false
   */
  bool IsRunning() const;
};
} // namespace TEM
#endif // ENGINE_H
