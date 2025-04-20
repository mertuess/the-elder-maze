#ifndef AUDIO_H
#define AUDIO_H

#include "Structs.h"
#include <SDL3/SDL_audio.h>
#include <vector>

namespace TEM {
class Audio {
private:
  static std::vector<AudioClip> audio_clips;
  static AudioClip current_loop;
  static SDL_AudioStream *music_stream;
  static SDL_AudioStream *sounds_stream;
  static double music_volume;
  static double sounds_volume;
  static SDL_AudioSpec spec;

public:
  static void Init();
  static void LoadClip();
  static void PlayOneShot(char *name);
  static void Play(char *name);
  static void Update();

  static void SetMusicVolume(double volume);
  static void SetSoundsVolume(double volume);
  static double GetMusicVolume();
  static double GetSoundsVolume();
};
} // namespace TEM

#endif // AUDIO_H
