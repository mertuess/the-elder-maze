#ifndef AUDIO_H
#define AUDIO_H

#include "Structs.h"
#include <vector>

namespace TEM {
class Audio {
private:
  static std::vector<AudioClip> audioClips;
  static SDL_AudioStream *music_stream;
  static SDL_AudioStream *sounds_stream;
  static double music_volume;
  static double sounds_volume;
  SDL_AudioSpec spec;

public:
  static void LoadClip();
  static void PlayOneShot(char *name);
  static void Play(char *name, bool loop = false);
};
} // namespace TEM

#endif // AUDIO_H
