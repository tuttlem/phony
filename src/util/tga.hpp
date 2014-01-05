
#ifndef __phony_tga_hpp_

#define __phony_tga_hpp_

namespace phony {

   /** Helper for loading tga graphics files */
   class tga {
      private:
         static void loadUncompressed(std::ifstream &f, std::shared_ptr<tga> t);
         static void loadCompressed(std::ifstream &f, std::shared_ptr<tga> t);

      public:
         tga(void);
         virtual ~tga(void);

         static std::shared_ptr<tga> fromFile(const std::string &filename);

         const unsigned int bpp(void) const { return _bpp; }
         const unsigned int width(void) const { return _width; }
         const unsigned int height(void) const { return _height; }
         const unsigned int imageSize(void) const { return _imageSize; }

         const unsigned int bytesPerPixel(void) const { return _bpp >> 3; }
         const GLuint glType(void) const { return _glType; }

         const GLuint makeTexture(void);

      private:
         unsigned char _header[6];

         unsigned int   _bpp, _width, _height;
         unsigned int   _imageSize;
         GLuint         _glType;

         std::unique_ptr<unsigned char[]> _data;
   };

}

#endif //__phony_tga_hpp_
