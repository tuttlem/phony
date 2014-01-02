
#include "../stdinc.hpp"

namespace phony {

   void primitive::vertex(const float x,  const float y,  const float z,
                      const float tx, const float ty) {
      glVertex3f(x, y, z);
      glTexCoord2f(tx, ty);
   }


   void primitive::poly(const float x1, const float y1, const float z1,
                        const float x2, const float y2, const float z2,
                        const float x3, const float y3, const float z3,
                        const float x4, const float y4, const float z4,
                        const float nx, const float ny, const float nz) {

      glNormal3f(nx, ny, nz);
      primitive::vertex(x1, y1, z1, 0.0f, 0.0f);
      primitive::vertex(x2, y2, z2, 1.0f, 0.0f);
      primitive::vertex(x3, y3, z3, 1.0f, 1.0f);
      primitive::vertex(x4, y4, z4, 0.0f, 1.0f);

   }

   void primitive::cube(const float s,
                    const float r, const float g, const float b, const float a) {
      primitive::cuboid(s, s, s, r, g, b, a);
   }

   void primitive::cube(const float s) {
      primitive::cuboid(s, s, s);
   }

   void primitive::cuboid(const float sx, const float sy, const float sz,
                      const float r,  const float g,  const float b, const float a) {

      glColor4f(r, g, b, a);
      primitive::cuboid(sx, sy, sz);

   }

   void primitive::cuboid(const float sx, const float sy, const float sz) {

      float x1 = -(sx / 2.0f), y1 = -(sy / 2.0f), z1 = -(sz / 2.0f);
      float x2 =  -x1,         y2 = -y1         , z2 = -z1;

      // back
      primitive::poly(x1, y1, z1,
                      x2, y1, z1,
                      x2, y2, z1,
                      x1, y2, z1,
                      0.0f, 0.0f, -1.0f);
      // front
      primitive::poly(x1, y1, z2,
                      x2, y1, z2,
                      x2, y2, z2,
                      x1, y2, z2,
                      0.0f, 0.0f, 1.0f);

      // top
      primitive::poly(x1, y1, z1,
                      x2, y1, z1,
                      x2, y1, z2,
                      x1, y1, z2,
                      0.0f, -1.0f, 0.0f);

      // bottom
      primitive::poly(x1, y2, z1,
                      x2, y2, z1,
                      x2, y2, z2,
                      x1, y2, z2,
                      0.0f, 1.0f, 0.0f);

      // left
      primitive::poly(x1, y1, z1,
                      x1, y1, z2,
                      x1, y2, z2,
                      x1, y2, z1,
                      -1.0f, 0.0f, 0.0f);

      // right
      primitive::poly(x2, y1, z1,
                      x2, y1, z2,
                      x2, y2, z2,
                      x2, y2, z1,
                      1.0f, 0.0f, 0.0f);
   }

}


