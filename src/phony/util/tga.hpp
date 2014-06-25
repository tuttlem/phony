
#ifndef __phony_tga_hpp_

#define __phony_tga_hpp_

namespace phony {

   /** Helper for loading tga graphics files */
   class tga {
      private:
         static void load_uncompressed(std::ifstream &f, std::shared_ptr<tga> t);
         static void load_compressed(std::ifstream &f, std::shared_ptr<tga> t);

      public:
         tga(void);
         virtual ~tga(void);

         static std::shared_ptr<tga> from_file(const std::string &filename);

         const unsigned int bpp(void) const { return _bpp; }
         const unsigned int width(void) const { return _width; }
         const unsigned int height(void) const { return _height; }
         const unsigned int image_size(void) const { return _image_size; }

         const unsigned int bytes_per_pixel(void) const { return _bpp >> 3; }
         const GLuint gl_type(void) const { return _gl_type; }

         const GLuint make_texture(void);

      private:
         unsigned char _header[6];

         unsigned int   _bpp, _width, _height;
         unsigned int   _image_size;
         GLuint         _gl_type;

         std::unique_ptr<unsigned char[]> _data;
   };

}

#endif //__phony_tga_hpp_
