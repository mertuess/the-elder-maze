/**
 * @file Player.h
 * @brief Заголовочный файл игрока
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

namespace TEM {
/**
 * @class Player
 * @brief Класс игрока, наследуется от Creature
 */
class Player : public Creature {
private:
  double step_treshold = 2.0; ///< Порог для шага
  double step_timer = 0.0; ///< Таймер шага

public:
  Player(); ///< Конструктор по умолчанию
  Player(Creature creature); ///< Конструктор из существа
  
  /**
   * @brief Создает луч для рендеринга
   * @param x Позиция X на экране
   * @param width Ширина экрана
   * @return Луч для рендеринга
   */
  Ray MakeRay(int x, int width);
  
  double weapon_delta = 75; ///< Смещение оружия
  const double FieldOfView = M_PI / 4; ///< Поле зрения
  const double Depth = 16.0; ///< Глубина прорисовки
  
  /**
   * @brief Проверяет, может ли игрок сделать шаг
   * @return true если может, иначе false
   */
  bool CanStep();
  
  /**
   * @brief Обновляет таймер шага
   * @param speed Скорость движения
   */
  void UpdateStepTimer(double speed);
};
} // namespace TEM
#endif // !PLAYER_H
