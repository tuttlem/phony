
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

         virtual const bool update(const unsigned int elapsed);
         virtual const bool render(void);

         virtual void handleEvent(SDL_Event event);

         virtual void keyPressed(const SDL_Event &key);
         virtual void keyReleased(const SDL_Event &key);
         virtual void mouseMoved(const SDL_Event &mouse);
         virtual void mousePressed(const SDL_Event &button);
         virtual void mouseReleased(const SDL_Event &button);
         virtual void resize(const int height, const int width);

         virtual std::shared_ptr<game_state> next(void);

      protected:
         static void resize2D(const int width, const int height);
         static void resize3D(const int width, const int height, const float fovy = 45.0f, const float zNear = 0.1f, const float zFar = 1000.0f);
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

   inline const bool game_state::update(const unsigned int elapsed) {
      return true;
   }

   inline const bool game_state::render(void) {
      return true;
   }

   inline std::shared_ptr<game_state> game_state::next(void) {
      return nullptr;
   }

   inline void game_state::handleEvent(SDL_Event event) {
   }

   inline void game_state::keyPressed(const SDL_Event &key) {
   }

   inline void game_state::keyReleased(const SDL_Event &key) {
   }

   inline void game_state::mouseMoved(const SDL_Event &mouse) {
   }

   inline void game_state::mousePressed(const SDL_Event &button) {
   }

   inline void game_state::mouseReleased(const SDL_Event &button) {
   }

   inline void game_state::resize(const int width, const int height) {
   }
}

#endif //__phony_gstate_hpp_
