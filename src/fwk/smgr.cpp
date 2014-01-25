
#include "../stdinc.hpp"

namespace phony {

   sound_effect::~sound_effect(void) {
      if (_chunk != nullptr) {
         Mix_FreeChunk(_chunk);
         _chunk = nullptr;
      }
   }

   music_piece::~music_piece(void) {
      if (_music != nullptr) {
         Mix_FreeMusic(_music);
         _music = nullptr;
      }
   }

   const bool sound_manager::load_sound_from_wav(const std::string &key, const std::string &filename) {
      if (_sounds.find(key) != _sounds.end()) {
         return false;
      }

      Mix_Chunk *chunk = Mix_LoadWAV(filename.c_str());

      if (chunk == nullptr) {
         return false;
      }

      _sounds[key] = std::unique_ptr<sound_effect>(new sound_effect(chunk));
      return true;
   }

   const bool sound_manager::load_music_from_wav(const std::string &key, const std::string &filename) {
      if (_musics.find(key) != _musics.end()) {
         return false;
      }

      Mix_Music *music = Mix_LoadMUS(filename.c_str());

      if (music == nullptr) {
         return false;
      }

      _musics[key] = std::unique_ptr<music_piece>(new music_piece(music));
      return true;
   }

   void sound_manager::toggle_music(void) {
      if (music_playing()) {
         Mix_PauseMusic();
      } else {
         Mix_ResumeMusic();
      }
   }

   void sound_manager::stop_music(void) {
      Mix_HaltMusic();
   }

   const bool sound_manager::music_playing(void) {
      return (bool)Mix_PausedMusic() != 1;
   }

   void sound_manager::play_sound(const std::string &key) {
      Mix_PlayChannel(-1, _sounds[key]->chunk(), 0);
   }

   void sound_manager::play_music(const std::string &key) {
      Mix_PlayMusic(_musics[key]->music(), -1);
   }

   /** Removes and destroys all sounds from the store */
   void sound_manager::clear(void) {
      _sounds.clear();
      _musics.clear();
   }

}
