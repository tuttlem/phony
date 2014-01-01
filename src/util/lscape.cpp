
#include "../stdinc.hpp"

namespace phony {

   landscape::landscape(const int w, const int h) {
      this->width = w; this->height = h;
      this->map = new float[this->width * this->height];
      this->step = 1;

      for (int x = 0; x < w; x ++) {
         for (int y = 0; y < h; y ++) {
            float xx = (float)x / (float)this->width;
            float yy = (float)y / (float)this->height;

            map[x + (y * w)] = perlin::perlin2d(
                  xx, yy,
                  6, 1.02f
                  );
         }
      }
   }

   landscape::~landscape(void) {
      delete[] this->map;
   }

   void landscape::setColour(const int x, const int y) {
      glColor3f(1.0f, 0.0f, getHeight(x, y));
   }

   void landscape::render(GLenum mode) {

      float nHalfHeight = -((float)this->height / 2.0f);
      float nHalfWidth  = -((float)this->width  / 2.0f);
      float xx = 0.0f, yy = 0.0f, zz = 0.0f;
      float heightFactor = 1.0f;

      glBegin(mode);

      for (int x = 0; x < (this->width - this->step); x += this->step) {
         for (int y = 0; y < (this->height - this->step); y += this->step) {

            xx = nHalfWidth + x;
            yy = this->getHeight(x, y) * heightFactor;
            zz = nHalfHeight + y;

            this->setColour(x, y);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x + this->step;
            yy = this->getHeight(x + this->step, y) * heightFactor;
            zz = nHalfHeight + y;

            this->setColour(x + this->step, y);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x + this->step;
            yy = this->getHeight(x + this->step, y + this->step) * heightFactor;
            zz = nHalfHeight + y + this->step;

            this->setColour(x + this->step, y + this->step);
            glVertex3f(xx, yy, zz);

            xx = nHalfWidth + x;
            yy = this->getHeight(x, y + this->step) * heightFactor;
            zz = nHalfHeight + y + this->step;

            this->setColour(x, y + this->step);
            glVertex3f(xx, yy, zz);

         }
      }

      glEnd();

   }

}
