
#include "../stdinc.hpp"

namespace phony {

   /** Loads a texture from tga file into the manager */
   const bool texture_manager::loadTGA(const std::string &key, const std::string &filename) {
      if (_textures.find(key) != _textures.end()) {
         return false;
      }

      _textures[key] = tga::fromFile(filename)->makeTexture();

      return true;
   }

   /** Removes and destroys all textures from the store */
   void texture_manager::clear(void) {

      for (auto it = _textures.begin(); it != _textures.end(); ++it) {
         glDeleteTextures(1, &it->second);
      }

      // empty the map
      _textures.clear();

   }

   void texture_manager::use(const std::string &key) {
      glBindTexture(GL_TEXTURE_2D, _textures[key]);
   }
}
