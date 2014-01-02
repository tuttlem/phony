
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

         float ambientLight[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
         float diffuseLight[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
         float lightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

         glEnable(GL_LIGHTING);
         glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
         glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
         glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
         glEnable(GL_LIGHT1);


         angle = 0.0f;

         return true;
      }

      const bool render() {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         glMatrixMode(GL_MODELVIEW);

         glLoadIdentity();
         glTranslatef(0.0f, 0.0f, -6.0f);
         glRotatef(angle, 1.0f, 1.0f, 1.0f);
         glBegin(GL_QUADS);
            primitive::cube(1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
         glEnd();

         glLoadIdentity();
         glTranslatef(0.0f, 0.0f, -5.0f);
         glRotatef(angle, 1.0f, 1.0f, 1.0f);
         glTranslatef(0.0f, 0.0f, -2.0f);
         glBegin(GL_QUADS);
            primitive::cube(1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
         glEnd();

         return true;
      }

      const bool update(const sf::Time &elapsed) {
         float perc = elapsed.asMilliseconds() / 1000.0f;
         angle += (perc * 10.0f) * (2.0f * 3.14159f);
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
      float angle;
};

int main(int argc, char *argv[]) {

   // create the game object
   phony::game g;

   g.init(640, 480, "Phony");
   g.run(new blank_state());
   g.teardown();

   return 0;
}
