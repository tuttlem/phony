
#ifndef __phony_bmp_hpp_

#define __phony_bmp_hpp_

namespace phony {

   /** Helper class for working with BMP files */
   class bmp {
      public:
         bmp(void);

         static bmp fromFile(const std::string &filename);

         const int width(void) const { return _width; }
         const int height(void) const { return _height; }

         const GLuint makeTexture(void);

      private:
         unsigned char _header[54];
         unsigned int _dataPos;
         unsigned int _width, _height;
         unsigned int _imageSize;
         std::unique_ptr<unsigned char[]> _data;
   };

   inline bmp::bmp(void) : _dataPos(0), _width(0), _height(0), _imageSize(0), _data(nullptr) {
   }

}

#endif //__phony_bmp_hpp_
