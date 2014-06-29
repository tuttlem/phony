
#include "../stdinc.hpp"

namespace phony {

   void scene::resize_2d(const int width, const int height) {

      // setup the projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, width, height, 0, -1, 1);

      // reset the model view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   }

   void scene::resize_3d(
      const int width, const int height,
      const float fovy, const float zNear, const float zFar
   ) {

      // setup the projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glViewport(0, 0, width, height);
      gluPerspective(fovy, (float)width/(float)height, zNear, zFar);

      // reset the model view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   }

}
