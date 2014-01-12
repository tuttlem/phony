
#ifndef __phony_tmgr_hpp_

#define __phony_tmgr_hpp_

namespace phony {

   /** Centralises texture management for the application */
   class texture_manager : public singleton_manager<texture_manager> {
      public:
         /** Loads a texture from tga file into the manager */
         const bool loadTGA(const std::string &key, const std::string &filename);

         void use(const std::string &key);

         /** Removes and destroys all textures from the store */
         void clear(void);

      private:
         std::map<std::string, GLuint> _textures;
   };

}

#endif //__phony_tmgr_hpp_
