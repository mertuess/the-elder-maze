#include "Audio.h"
#include "Logger.h"
#include "Structs.h"
#include <SDL3/SDL_audio.h>
#include <cstddef>

namespace TEM {
std::vector<AudioClip> Audio::audio_clips;
AudioClip Audio::current_loop;
SDL_AudioStream *Audio::music_stream = nullptr;
SDL_AudioStream *Audio::sounds_stream = nullptr;
double Audio::music_volume = 0.0;
double Audio::sounds_volume = 0.0;
SDL_AudioSpec Audio::spec = {};

void Audio::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    TEM::Logger::Print("Couldn't initialize SDL: {}\n", SDL_GetError());
  }

  // Load Clips
  audio_clips.push_back({(char *)"ambient",
                         (char *)"./resources/audio/ambient.wav",
                         NULL,
                         0,
                         {}});
  audio_clips.push_back({(char *)"startup",
                         (char *)"./resources/audio/startup.wav",
                         NULL,
                         0,
                         {}});
  audio_clips.push_back(
      {(char *)"enter", (char *)"./resources/audio/enter.wav", NULL, 0, {}});
  audio_clips.push_back(
      {(char *)"press", (char *)"./resources/audio/press.wav", NULL, 0, {}});
  audio_clips.push_back(
      {(char *)"menu", (char *)"./resources/audio/menu.wav", NULL, 0, {}});
  audio_clips.push_back(
      {(char *)"miss", (char *)"./resources/audio/miss.wav", NULL, 0, {}});
  audio_clips.push_back(
      {(char *)"attack", (char *)"./resources/audio/attack.wav", NULL, 0, {}});
  audio_clips.push_back(
      {(char *)"step", (char *)"./resources/audio/step.wav", NULL, 0, {}});

  for (AudioClip &clip : audio_clips) {
    TEM::Logger::Print(
        "Load {}.wav file: {}\n", clip.name,
        SDL_LoadWAV(clip.path, &clip.spec, &clip.wav_data, &clip.wav_data_len)
            ? "Successful"
            : "Error");
  }

  if (!audio_clips.empty()) {
    music_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                             &audio_clips[0].spec, NULL, NULL);
    sounds_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                              &audio_clips[0].spec, NULL, NULL);
  }
}

void Audio::Play(char *name) {
  TEM::Logger::Print("Try to play '{}' audio clip\n", name);
  for (auto &clip : audio_clips) {
    if (strcmp(name, clip.name) == 0) {
      TEM::Logger::Print("Clip '{}' founded\n", name);
      if (music_stream) {
        SDL_DestroyAudioStream(music_stream);
      }
      music_stream = SDL_OpenAudioDeviceStream(
          SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &clip.spec, NULL, NULL);
      if (music_stream) {
        TEM::Logger::Print("Play audio clip: {}\n", name);
        SDL_PutAudioStreamData(music_stream, clip.wav_data, clip.wav_data_len);
        SDL_SetAudioStreamGain(music_stream, music_volume);
        SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(music_stream));
      }
      current_loop = clip;
      break;
    }
  }
}

void Audio::PlayOneShot(char *name) {
  for (auto &clip : audio_clips) {
    if (strcmp(name, clip.name) == 0) {
      if (sounds_stream) {
        SDL_DestroyAudioStream(sounds_stream);
      }
      sounds_stream = SDL_OpenAudioDeviceStream(
          SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &clip.spec, NULL, NULL);
      if (sounds_stream) {
        SDL_PutAudioStreamData(sounds_stream, clip.wav_data, clip.wav_data_len);
        SDL_SetAudioStreamGain(sounds_stream, sounds_volume);
        SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(sounds_stream));
      }
      break;
    }
  }
}

void Audio::Update() {
  if (music_stream && current_loop.wav_data) {
    if (SDL_GetAudioStreamQueued(music_stream) <
        (int)current_loop.wav_data_len) {
      SDL_PutAudioStreamData(music_stream, current_loop.wav_data,
                             current_loop.wav_data_len);
      SDL_SetAudioStreamGain(music_stream, music_volume);
    }
  }
}

void Audio::SetMusicVolume(double volume) {
  music_volume = SDL_clamp(volume, 0.0, 1.0);
  if (music_stream) {
    SDL_SetAudioStreamGain(music_stream, music_volume);
  }
}

void Audio::SetSoundsVolume(double volume) {
  sounds_volume = SDL_clamp(volume, 0.0, 1.0);
  if (sounds_stream) {
    SDL_SetAudioStreamGain(sounds_stream, sounds_volume);
  }
}

double Audio::GetMusicVolume() { return music_volume; }

double Audio::GetSoundsVolume() { return sounds_volume; }
} // namespace TEM
