/**
 * @file Entity.h
 * @brief Заголовочный файл базовой сущности
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "Structs.h"

namespace TEM {
/**
 * @class Entity
 * @brief Базовый класс для всех сущностей игры
 */
class Entity {
public:
  Entity(); ///< Конструктор по умолчанию
  
  /**
   * @brief Конструктор из системных данных
   * @param System Системные данные сущности
   */
  Entity(Entity_System System);
  
  Entity_System System; ///< Системные данные
  
  /**
   * @brief Конвертирует позицию в целочисленные координаты
   * @return Точка с целыми координатами
   */
  Point2D ConvertPosition();
};
} // namespace TEM
#endif // !ENTITY_H
