
#include "../stdinc.hpp"

namespace phony {

   landscape::landscape(const int w, const int h) {
      this->_width = w; this->_height = h;
      this->_map = new float[this->_width * this->_height];
      this->_step = 1;

      for (int x = 0; x < w; x ++) {
         for (int y = 0; y < h; y ++) {
            float xx = (float)x / (float)this->_width;
            float yy = (float)y / (float)this->_height;

            _map[x + (y * w)] = perlin::perlin_2d(
                  xx, yy,
                  6, 1.02f
                  );
         }
      }
   }

   landscape::~landscape(void) {
      delete[] this->_map;
   }

   void landscape::set_colour(const int x, const int y) {
      glColor3f(1.0f, 0.0f, this->get_height(x, y));
   }

   void landscape::render(GLenum mode) {

      float nHalfHeight = -((float)this->_height / 2.0f);
      float nHalfWidth  = -((float)this->_width  / 2.0f);
      float xx = 0.0f, yy = 0.0f, zz = 0.0f;
      float heightFactor = 1.0f;

      glBegin(mode);

      for (int x = 0; x < (this->_width - this->_step); x += this->_step) {
         for (int y = 0; y < (this->_height - this->_step); y += this->_step) {

            xx = nHalfWidth + x;
            yy = this->get_height(x, y) * heightFactor;
            zz = nHalfHeight + y;

            this->set_colour(x, y);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x + this->_step;
            yy = this->get_height(x + this->_step, y) * heightFactor;
            zz = nHalfHeight + y;

            this->set_colour(x + this->_step, y);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x + this->_step;
            yy = this->get_height(x + this->_step, y + this->_step) * heightFactor;
            zz = nHalfHeight + y + this->_step;

            this->set_colour(x + this->_step, y + this->_step);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x;
            yy = this->get_height(x, y + this->_step) * heightFactor;
            zz = nHalfHeight + y + this->_step;

            this->set_colour(x, y + this->_step);
            glVertex3f(xx, yy, zz);

         }
      }

      glEnd();

   }

}
