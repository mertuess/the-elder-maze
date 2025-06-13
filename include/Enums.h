/**
 * @file Enums.h
 * @brief Заголовочный файл с перечислениями
 */
#ifndef ENUMS_H
#define ENUMS_H

namespace TEM {
/**
 * @enum ItemType
 * @brief Типы предметов
 */
enum class ItemType : int { 
  Undefined = -1, ///< Неопределенный тип
  Equipable = 0, ///< Экипируемый предмет
  Usable = 1 ///< Используемый предмет
};

/**
 * @enum EquipType
 * @brief Типы экипировки
 */
enum class EquipType : int {
  Undefined = -1, ///< Неопределенный тип
  Armor = 0, ///< Броня
  Weapon = 1, ///< Оружие
  Shield = 2, ///< Щит
  Boots = 3, ///< Ботинки
  Helm = 4 ///< Шлем
};

/**
 * @enum Event
 * @brief События игры
 */
enum class Event : int {
  None = 0, ///< Нет события
  MoveUp, ///< Движение вверх
  MoveDown, ///< Движение вниз
  MoveLeft, ///< Движение влево
  MoveRight, ///< Движение вправо
  Attack, ///< Атака
  Inventory, ///< Инвентарь
  Quit, ///< Выход
  NewGame, ///< Новая игра
  LoadGame, ///< Загрузка игры
  ExitToMenu ///< Выход в меню
};
} // namespace TEM
#endif // ENUMS_H
