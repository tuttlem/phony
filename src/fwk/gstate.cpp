
#include "../stdinc.hpp"

namespace phony {

   void game_state::resize2D(const sf::Event::SizeEvent &event) {

      // setup the projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, event.width, event.height, 0, -1, 1);

      // reset the model view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   }

   void game_state::resize3D(const sf::Event::SizeEvent &event, const float fovy, const float zNear, const float zFar) {

      // setup the projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glViewport(0, 0, event.width, event.height);
      gluPerspective(fovy, (float)event.width/(float)event.height, zNear, zFar);

      // reset the model view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   }

}

