
#include "../stdinc.hpp"

namespace phony {

   texture::~texture(void) {
      if (this->_reference != 0) {
         glDeleteTextures(1, &this->_reference);
         this->_reference = 0;
      }
   }

   /** Loads a texture from tga file into the manager */
   const bool texture_manager::load_tga(const std::string &key, const std::string &filename) {
      if (_textures.find(key) != _textures.end()) {
         return false;
      }

      _textures[key] = std::unique_ptr<texture>(new texture(tga::from_file(filename)->make_texture()));

      return true;
   }

   /** Removes and destroys all textures from the store */
   void texture_manager::clear(void) {
      // empty the map
      _textures.clear();
   }

   void texture_manager::use(const std::string &key) {
      glBindTexture(GL_TEXTURE_2D, _textures[key]->reference());
   }
}
