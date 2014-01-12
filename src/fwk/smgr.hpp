
#ifndef __phony_smgr_hpp_

#define __phony_smgr_hpp_

namespace phony {

   /** Centralises sound and music management for the application */
   class sound_manager : public singleton_manager<sound_manager> {
      public:
         const bool loadSoundFromWav(const std::string &key, const std::string &filename);
         const bool loadMusicFromWav(const std::string &key, const std::string &filename);

         void toggleMusic(void);
         void stopMusic(void);
         const bool musicPlaying(void);

         void playSound(const std::string &key);
         void playMusic(const std::string &key);

         /** Removes and destroys all sounds from the store */
         virtual void clear(void);
   };

}

#endif //__phony_smgr_hpp_
