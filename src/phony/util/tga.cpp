
#include "../stdinc.hpp"

namespace phony {


   tga::tga(void) {
   }

   tga::~tga(void) {
   }

   std::shared_ptr<tga> tga::from_file(const std::string &filename) {

      // open the tga file
      std::ifstream tgaFile(filename, std::ios::binary | std::ios::in);

      // check that the file opened
      if (!tgaFile.is_open()) {
         throw std::runtime_error("Unable to open the file " + filename);
      }

      unsigned char uncompHeader[12] = { 0, 0, 2 , 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      unsigned char compHeader[12]   = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

      unsigned char header[12];

      // read the header out
      tgaFile.read((char *)header, 12);

      if (!tgaFile) {
         throw std::runtime_error("TGA header not long enough");
      }

      std::shared_ptr<tga> t = std::make_shared<tga>();

      // read out the rest of the header
      tgaFile.read((char *)t->_header, 6);

      if (!tgaFile) {
         throw std::runtime_error("TGA header not long enough");
      }

      t->_width  = t->_header[1] * 256 + t->_header[0];
      t->_height = t->_header[3] * 256 + t->_header[2];
      t->_bpp    = t->_header[4];

      if (t->_width <= 0 || t->_height <= 0 || (t->_bpp != 24 && t->_bpp != 32)) {
         throw std::runtime_error("TGA attributes are not valid");
      }

      if (t->_bpp == 24) {
         t->_gl_type = GL_BGR;
      } else {
         t->_gl_type = GL_BGRA;
      }

      t->_image_size = t->bytes_per_pixel() * t->_width * t->_height;
      t->_data = std::unique_ptr<unsigned char[]>(
         new unsigned char[t->_image_size]
      );

      // check if it's an uncompressed or compressed tga
      if (memcmp(uncompHeader, header, 12) == 0) {
         tga::load_uncompressed(tgaFile, t);
      } else if (memcmp(compHeader, header, 12) == 0) {
         tga::load_compressed(tgaFile, t);
      } else {
         throw std::runtime_error("An invalid TGA header was encountered");
      }

      // close the file
      tgaFile.close();

      return t;
   }

   void tga::load_uncompressed(std::ifstream &f, std::shared_ptr<tga> t) {

      // read the image data now
      f.read((char *)t->_data.get(), t->_image_size);

      if (!f) {
         throw std::runtime_error("Not enough TGA data was available");
      }

   }

   void tga::load_compressed(std::ifstream &f, std::shared_ptr<tga> t) {

      unsigned int currentByte = 0;

      auto colourBuffer = std::unique_ptr<unsigned char>(
         new unsigned char[t->bytes_per_pixel()]
      );

      do {
         unsigned char chunkHeader = 0;

         f.read((char *)&chunkHeader, sizeof(unsigned char));

         // determine if it was a raw header
         if (chunkHeader < 128) {
            // add one to the header to get the total number of
            // raw pixels
            chunkHeader ++;

            unsigned int bytes = chunkHeader * t->bytes_per_pixel();

            // read out the pixels
            f.read((char *)&t->_data.get()[currentByte], bytes);

            // advance the byte pointer by how many bytes we just read
            currentByte += bytes;
         } else {
            // subtract 127 to remove the id bit
            chunkHeader -= 127;

            // read the next pixel
            f.read((char *)colourBuffer.get(), t->bytes_per_pixel());

            // set the pixels
            for (int index = 0; index < chunkHeader; index ++) {
               for (unsigned int b = 0; b < t->bytes_per_pixel(); b ++) {
                  t->_data.get()[currentByte] = colourBuffer.get()[b];
                  currentByte ++;
               }
            }
         }

      } while (currentByte < t->_image_size);

   }

   const GLuint tga::make_texture(void) {

      GLuint textureId;
      glGenTextures(1, &textureId);

      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexImage2D(
         GL_TEXTURE_2D, 0,
         GL_RGB, this->_width, this->_height, 0,
         this->_gl_type, GL_UNSIGNED_BYTE, this->_data.get()
      );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      return textureId;
   }
}
