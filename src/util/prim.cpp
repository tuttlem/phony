
#include "../stdinc.hpp"

namespace phony {

   void primitive::cuboid(
      const glm::vec3 &v1,
      const glm::vec3 &v2,
      const side s
   ) {

      float x1 = v1.x, y1 = v1.y, z1 = v1.z;
      float x2 = v2.x, y2 = v2.y, z2 = v2.z;

      if ((s & side::BACK) != side::NONE) {
         primitive::poly(
            x1, y1, z1,
            x2, y1, z1,
            x2, y2, z1,
            x1, y2, z1,
            0.0f, 0.0f, -1.0f
         );
      }

      if ((s & side::FRONT) != side::NONE) {
         primitive::poly(
            x1, y1, z2,
            x2, y1, z2,
            x2, y2, z2,
            x1, y2, z2,
            0.0f, 0.0f, 1.0f
         );
      }

      if ((s & side::LEFT) != side::NONE) {
         primitive::poly(
            x1, y1, z1,
            x1, y1, z2,
            x1, y2, z2,
            x1, y2, z1,
            -1.0f, 0.0f, 0.0f
         );
      }

      if ((s & side::RIGHT) != side::NONE) {
         primitive::poly(
            x2, y1, z1,
            x2, y1, z2,
            x2, y2, z2,
            x2, y2, z1,
            1.0f, 0.0f, 0.0f
         );
      }

      if ((s & side::BOTTOM) != side::NONE) {
         primitive::poly(
            x1, y1, z1,
            x2, y1, z1,
            x2, y1, z2,
            x1, y1, z2,
            0.0f, -1.0f, 0.0f
         );
      }

      if ((s & side::TOP) != side::NONE) {
         primitive::poly(
            x1, y2, z1,
            x2, y2, z1,
            x2, y2, z2,
            x1, y2, z2,
            0.0f, 1.0f, 0.0f
         );
      }
   }

   void primitive::cuboid(
      const glm::vec3 &v,
      const side s
   ) {
      glm::vec3 v2 = -v;
      primitive::cuboid(v2, v, s);
   }

   void primitive::cube(
      const glm::vec3 &v1,
      const float f,
      const side s
   ) {
      glm::vec3 v2(v1.x + f, v1.y + f, v1.z + f);
      primitive::cuboid(v1, v2, s);
   }

   void primitive::cube(
      const float f,
      const side s
   ) {
      float hf = f / 2.0f;
      primitive::cube(
         glm::vec3(-hf, -hf, -hf),
         f,
         s
      );
   }

   void primitive::poly(
      const float x1, const float y1, const float z1,
      const float x2, const float y2, const float z2,
      const float x3, const float y3, const float z3,
      const float x4, const float y4, const float z4,
      const float nx, const float ny, const float nz
   ) {

      glNormal3f(nx, ny, nz);

      glTexCoord2d(0.0f, 0.0f);
      glVertex3f(x1, y1, z1);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x2, y2, z2);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x3, y3, z3);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x4, y4, z4);
   }
}


