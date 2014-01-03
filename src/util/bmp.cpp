
#include "../stdinc.hpp"

namespace phony {

   bmp bmp::fromFile(const std::string &filename) {

      bmp result;

      // get the file
      std::ifstream file(filename, std::ios::in | std::ios::binary);

      // we opened the file ok
      if (file.is_open()) {

         // read the file header
         file.read((char *)result._header, 54);

         if (!file) {
            // throw an exception (header not long enough)
         }

         // test that the header is valid
         if (result._header[0] != 'B' || result._header[1] != 'M') {
            // throw an exception (invalid header)
         }

         // pull out image info from the header
         result._dataPos   = *(int*)&(result._header[0x0A]);
         result._imageSize = *(int*)&(result._header[0x22]);
         result._width     = *(int*)&(result._header[0x12]);
         result._height    = *(int*)&(result._header[0x16]);

         // due to some mis-formatting, details are sometimes left out
         // we'll fix these here by guessing
         if (result._imageSize == 0) {
            result._imageSize = result._width * result._height * 3;
         }

         if (result._dataPos == 0) {
            result._dataPos = 54; /* just after the header */
         }

         result._data = std::unique_ptr<unsigned char[]>(
            new unsigned char[result._imageSize]
         );
         // read the data
         file.read((char *)result._data.get(), result._imageSize);

         // close the file
         file.close();
      }

      return result;
   }

   const GLuint bmp::makeTexture(void) {

      GLuint textureId;
      glGenTextures(1, &textureId);

      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexImage2D(
         GL_TEXTURE_2D, 0,
         GL_RGB, this->_width, this->_height, 0,
         GL_BGR, GL_UNSIGNED_BYTE, this->_data.get()
      );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      return textureId;
   }
}
