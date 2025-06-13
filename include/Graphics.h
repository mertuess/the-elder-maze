/**
 * @file Graphics.h
 * @brief Заголовочный файл для работы с графическими эффектами
 */
#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace TEM {
/**
 * @class Graphics
 * @brief Класс для управления графическими эффектами, особенно тенями стен
 */
class Graphics {
private:
  static int _wallShadeSymb[4]; ///< Массив символов для отображения теней стен
  Graphics() {} ///< Приватный конструктор (статический класс)

public:
  /**
   * @brief Получает символ тени стены на основе глубины и расстояния
   * @param depth Глубина стены
   * @param distanceToWall Расстояние до стены
   * @return Символ для отображения тени
   */
  static int GetWallShade(double depth, double distanceToWall);
  
  /**
   * @brief Получает массив символов теней
   * @return Указатель на массив символов теней
   */
  static int *GetWallShadeArr();
};
} // namespace TEM
#endif // GRAPHICS_H
