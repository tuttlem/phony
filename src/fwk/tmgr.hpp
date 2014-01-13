
#ifndef __phony_tmgr_hpp_

#define __phony_tmgr_hpp_

namespace phony {

   class texture {
      public:
         texture(void);
         texture(const GLuint t);

         virtual ~texture(void);

         const GLuint reference();

      private:
         GLuint _reference;
   };

   /** Centralises texture management for the application */
   class texture_manager : public singleton_manager<texture_manager> {
      public:
         /** Loads a texture from tga file into the manager */
         const bool loadTGA(const std::string &key, const std::string &filename);

         void use(const std::string &key);

         /** Removes and destroys all textures from the store */
         void clear(void);

      private:
         std::map<std::string, std::unique_ptr<texture>> _textures;
   };


   inline texture::texture(void) : _reference(0) { }
   inline texture::texture(const GLuint t) : _reference(t) { }

   inline const GLuint texture::reference() {
      return this->_reference;
   }
}

#endif //__phony_tmgr_hpp_
