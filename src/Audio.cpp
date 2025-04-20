#include "Audio.h"

namespace TEM {
SDL_AudioStream *Audio::music_stream = SDL_OpenAudioDeviceStream(
    SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &Audio::spec, NULL, NULL);
SDL_AudioStream *Audio::sounds_stream = SDL_OpenAudioDeviceStream(
    SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &Audio::spec, NULL, NULL);
} // namespace TEM
