
#ifndef __phony_smgr_hpp_

#define __phony_smgr_hpp_

namespace phony {

   class sound_effect {
      public:
         sound_effect(void);
         sound_effect(Mix_Chunk *sound);
         virtual ~sound_effect(void);

         Mix_Chunk* chunk(void);

      private:
         Mix_Chunk   *_chunk;
   };

   class music_piece {
      public:
         music_piece(void);
         music_piece(Mix_Music *sound);
         virtual ~music_piece(void);

         Mix_Music* music(void);

      private:
         Mix_Music   *_music;
   };

   /** Centralises sound and music management for the application */
   class sound_manager : public singleton_manager<sound_manager> {
      public:
         const bool loadSoundFromWAV(const std::string &key, const std::string &filename);
         const bool loadMusicFromWAV(const std::string &key, const std::string &filename);

         void toggleMusic(void);
         void stopMusic(void);
         const bool musicPlaying(void);

         void playSound(const std::string &key);
         void playMusic(const std::string &key);

         /** Removes and destroys all sounds from the store */
         virtual void clear(void);

      private:
         std::map<std::string, std::unique_ptr<sound_effect>> _sounds;
         std::map<std::string, std::unique_ptr<music_piece>> _musics;
   };

   inline sound_effect::sound_effect(void) : _chunk(nullptr) { }
   inline sound_effect::sound_effect(Mix_Chunk *sound) : _chunk(sound) { }
   inline Mix_Chunk* sound_effect::chunk() { return _chunk; }

   inline music_piece::music_piece(void) : _music(nullptr) { }
   inline music_piece::music_piece(Mix_Music *sound) : _music(sound) { }
   inline Mix_Music* music_piece::music() { return _music; }

}

#endif //__phony_smgr_hpp_
