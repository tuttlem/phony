
#include "../stdinc.hpp"

namespace phony {

   const bool sound_manager::loadSoundFromWav(const std::string &key, const std::string &filename) {
      return true;
   }

   const bool sound_manager::loadMusicFromWav(const std::string &key, const std::string &filename) {
      return true;
   }

   void sound_manager::toggleMusic(void) {
   }

   void sound_manager::stopMusic(void) {
   }

   const bool sound_manager::musicPlaying(void) {
      return true;
   }

   void sound_manager::playSound(const std::string &key) {
   }

   void sound_manager::playMusic(const std::string &key) {
   }

   /** Removes and destroys all sounds from the store */
   template<>
   void singleton_manager<sound_manager>::clear(void) {
   }

}
