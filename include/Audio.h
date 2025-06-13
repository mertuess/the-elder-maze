```cpp
#ifndef AUDIO_H
#define AUDIO_H

#include "Structs.h"
#include <SDL3/SDL_audio.h>
#include <vector>

namespace TEM {

/**
 * @class Audio
 * @brief Класс для управления аудио в приложении.
 *
 * Отвечает за загрузку, воспроизведение и настройку громкости музыки и звуковых эффектов.
 * Поддерживает как однократное воспроизведение звуков, так и зацикленную музыку.
 */
class Audio {
private:
  static std::vector<AudioClip> audio_clips;      ///< Вектор загруженных аудиоклипов.
  static AudioClip current_loop;                 ///< Текущий зацикленный аудиоклип.
  static SDL_AudioStream *music_stream;          ///< Аудиопоток для воспроизведения музыки.
  static SDL_AudioStream *sounds_stream;         ///< Аудиопоток для воспроизведения звуковых эффектов.
  static double music_volume;                    ///< Уровень громкости музыки (от 0.0 до 1.0).
  static double sounds_volume;                   ///< Уровень громкости звуковых эффектов (от 0.0 до 1.0).
  static SDL_AudioSpec spec;                     ///< Аудио параметры для воспроизведения.

public:
  /**
   * @brief Инициализирует аудиосистему.
   *
   * Настраивает аудиопотоки и подготавливает систему к воспроизведению.
   */
  static void Init();

  /**
   * @brief Загружает аудиоклип в память.
   *
   * Клип можно воспроизвести позднее с помощью методов PlayOneShot или Play.
   */
  static void LoadClip();

  /**
   * @brief Воспроизводит аудиоклип однократно.
   * @param name Имя аудиоклипа для воспроизведения.
   */
  static void PlayOneShot(char *name);

  /**
   * @brief Воспроизводит аудиоклип в цикле.
   * @param name Имя аудиоклипа для воспроизведения.
   */
  static void Play(char *name);

  /**
   * @brief Обновляет состояние аудиосистемы.
   *
   * Должен вызываться регулярно для обработки аудио событий.
   */
  static void Update();

  /**
   * @brief Устанавливает громкость музыки.
   * @param volume Уровень громкости (от 0.0 до 1.0).
   */
  static void SetMusicVolume(double volume);

  /**
   * @brief Устанавливает громкость звуковых эффектов.
   * @param volume Уровень громкости (от 0.0 до 1.0).
   */
  static void SetSoundsVolume(double volume);

  /**
   * @brief Возвращает текущую громкость музыки.
   * @return Уровень громкости музыки (от 0.0 до 1.0).
   */
  static double GetMusicVolume();

  /**
   * @brief Возвращает текущую громкость звуковых эффектов.
   * @return Уровень громкости звуковых эффектов (от 0.0 до 1.0).
   */
  static double GetSoundsVolume();
};
} // namespace TEM

#endif // AUDIO_H
```
