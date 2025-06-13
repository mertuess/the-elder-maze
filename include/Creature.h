/**
 * @file Creature.h
 * @brief Заголовочный файл класса существ
 */
#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include "Maze.h"

namespace TEM {
/**
 * @class Creature
 * @brief Класс существ, наследуется от Entity
 */
class Creature : public Entity {
private:
  Scalable scalable; ///< Данные для масштабирования
  Characteristics characteristics; ///< Характеристики
  std::string name; ///< Имя существа

public:
  /**
   * @brief Конструктор существа
   * @param name Имя существа
   */
  Creature(std::string name);
  
  /**
   * @brief Конструктор из сущности
   * @param entity Базовая сущность
   * @param name Имя существа
   */
  Creature(Entity entity, std::string name);
  
  /**
   * @brief Расширенный конструктор
   * @param entity Базовая сущность
   * @param name Имя существа
   * @param StartLevel Начальный уровень
   * @param Equip Экипировка
   */
  Creature(Entity entity, std::string name, unsigned int StartLevel,
           struct Equip Equip);

  bool IsAlive = true; ///< Флаг жизни
  Equip Equip; ///< Экипировка

  /**
   * @brief Двигает существо
   * @param maze Лабиринт
   * @param speedX Скорость по X
   * @param speedY Скорость по Y
   */
  void Move(TEM::Maze &maze, double speedX, double speedY);
  
  /**
   * @brief Поворачивает существо
   * @param speed Скорость поворота
   */
  void Rotate(double speed);
  
  /**
   * @brief Добавляет опыт
   * @param exp Количество опыта
   */
  void AddExp(unsigned int exp);
  
  /**
   * @brief Изменяет здоровье
   * @param modificator Модификатор здоровья
   */
  void ChangeHealth(int modificator);
  
  /**
   * @brief Атакует
   * @return Нанесенный урон
   */
  short Attack();
  
  /**
   * @brief Обновляет состояние атаки
   */
  void UpdateAttack();

  /**
   * @brief Получает урон
   * @return Текущий урон
   */
  unsigned int GetDamage() const;
  
  /**
   * @brief Получает данные масштабирования
   * @return Структура Scalable
   */
  struct Scalable GetScalable() const;
  
  /**
   * @brief Получает характеристики
   * @return Структура Characteristics
   */
  struct Characteristics GetCharacteristics() const;
};
} // namespace TEM
#endif // !CREATURE_H
