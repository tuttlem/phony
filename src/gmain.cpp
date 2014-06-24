
#include "phony.hpp"

using namespace phony;

class blank_state : public game_state {
   public:
      blank_state() : light1(GL_LIGHT1) {
         pressed = false;
      }

      const bool init() {
         glShadeModel(GL_SMOOTH);
         glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
         glClearDepth(1.0f);
         glEnable(GL_DEPTH_TEST);
         glDepthFunc(GL_LEQUAL);
         glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

         light1.ambient(rgba(0.5f, 0.5f, 0.5f, 1.0f));
         light1.diffuse(rgba(1.0f, 1.0f, 1.0f, 1.0f));
         light1.position(glm::vec4(0.0f, 0.0f, 2.0f, 1.0f));

         glEnable(GL_LIGHTING);
         light1.enable();

         glEnable(GL_TEXTURE_2D);

         angle = 0.0f;

         texture_manager::instance()->load_tga("test", "data/test.tga");

         return true;
      }

      const bool render() {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         light1.set();

         glMatrixMode(GL_MODELVIEW);

         texture_manager::instance()->use("test");

         glLoadIdentity();
         glTranslatef(0.0f, 0.0f, -6.0f);
         glRotatef(angle, 1.0f, 1.0f, 1.0f);
         glBegin(GL_QUADS);
            primitive::cube(1.0f);
         glEnd();

         glLoadIdentity();
         glTranslatef(0.0f, 0.0f, -5.0f);
         glRotatef(angle, 1.0f, 1.0f, 1.0f);
         glTranslatef(0.0f, 0.0f, -2.0f);
         glBegin(GL_QUADS);
            primitive::cube(1.0f);
         glEnd();

         return true;
      }

      const bool update(const unsigned int elapsed) {
         float perc = elapsed / 1000.0f;
         angle += (perc * 10.0f) * (2.0f * 3.14159f);
         return !pressed;
      }

      void key_pressed(const SDL_Event &key) {
         pressed = true;
      }

      void resize(const int width, const int height) {
         std::cout << "resized to " << width << ", " << height << std::endl;
         game_state::resize_3d(width, height);
      }

   private:
      bool pressed;
      float angle;
      GLuint textureId;
      light light1;
};

int main(int argc, char *argv[]) {

   // create the game object
   phony::game g;
   auto config = phony::lua_config::from_file("data/config.lua");

   g.init(
      config->get_int("window.width"),
      config->get_int("window.height"),
      config->get_string("window.title")
   );

   g.run(std::make_shared<blank_state>());
   g.teardown();

   return 0;
}
