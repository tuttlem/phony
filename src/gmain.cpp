
#include "stdinc.hpp"

using namespace phony;

class blank_state : public game_state {
   public:
      blank_state() {
         keypressed = false;
      }

      const bool init() {
         glShadeModel(GL_SMOOTH);
         glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
         glClearDepth(1.0f);
         glEnable(GL_DEPTH_TEST);
         glDepthFunc(GL_LEQUAL);
         glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

         return true;
      }

      const bool render() {
         glClear(GL_COLOR_BUFFER_BIT);

         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();

         return true;
      }

      const bool update(const sf::Time &elapsed) {
         return !keypressed;
      }

      void keyPressed(const sf::Event::KeyEvent &key) {
         keypressed = true;
      }

      void resize(const sf::Event::SizeEvent &size) {
         game_state::resize3D(size);
      }

   private:
      bool keypressed;
};

int main(int argc, char *argv[]) {

   // create the game object
   phony::game g;

   g.init(640, 480, "Phony");
   g.run(new blank_state());
   g.teardown();

   return 0;
}
