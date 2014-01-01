
#ifndef __phony_gstate_hpp_

#define __phony_gstate_hpp_

namespace phony {

   /* Defines a single game state */
   class game_state {
      public:
         game_state(void);
         virtual ~game_state(void);

         virtual const bool init(void);
         virtual const bool teardown(void);

         virtual const bool update(const sf::Time &elapsed);
         virtual const bool render(void);

         virtual void handleEvent(sf::Event event);

         virtual void keyPressed(const sf::Event::KeyEvent &key);
         virtual void keyReleased(const sf::Event::KeyEvent &key);
         virtual void mouseMoved(const sf::Event::MouseMoveEvent &mouse);
         virtual void mousePressed(const sf::Event::MouseButtonEvent &button);
         virtual void mouseReleased(const sf::Event::MouseButtonEvent &button);
         virtual void resize(const sf::Event::SizeEvent &size);

         virtual game_state* next(void);

      protected:
         static void resize2D(const sf::Event::SizeEvent &event);
         static void resize3D(const sf::Event::SizeEvent &event, const float fovy = 45.0f, const float zNear = 0.1f, const float zFar = 1000.0f);
   };

   inline game_state::game_state(void) {
   }

   inline game_state::~game_state(void) {
   }

   inline const bool game_state::init(void) {
      return true;
   }

   inline const bool game_state::teardown(void) {
      return true;
   }

   inline const bool game_state::update(const sf::Time &elapsed) {
      return true;
   }

   inline const bool game_state::render(void) {
      return true;
   }

   inline game_state* game_state::next(void) {
      return NULL;
   }

   inline void game_state::handleEvent(sf::Event event) {
   }

   inline void game_state::keyPressed(const sf::Event::KeyEvent &key) {
   }

   inline void game_state::keyReleased(const sf::Event::KeyEvent &key) {
   }

   inline void game_state::mouseMoved(const sf::Event::MouseMoveEvent &mouse) {
   }

   inline void game_state::mousePressed(const sf::Event::MouseButtonEvent &button) {
   }

   inline void game_state::mouseReleased(const sf::Event::MouseButtonEvent &button) {
   }

   inline void game_state::resize(const sf::Event::SizeEvent &size) {
   }
}

#endif //__phony_gstate_hpp_
