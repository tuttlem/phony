
#ifndef __phony_stmgr_hpp_

#define __phony_stmgr_hpp_

namespace phony {

   class error_state;

   class state_manager {
      public:
         state_manager(void);
         virtual ~state_manager(void);

         void set_state(std::shared_ptr<game_state> state);
         void set_error_state(const std::string &message);

         void update(const unsigned int elapsed, const int width, const int height);
         void render(void);
         void raise_event(const SDL_Event &event);

         const bool running(void) const { return this->_current_state != nullptr; }

         void key_pressed(const SDL_Event &event);
         void key_released(const SDL_Event &event);
         void mouse_moved(const SDL_Event &event);
         void mouse_pressed(const SDL_Event &event);
         void mouse_released(const SDL_Event &event);
         void resize(const int width, const int height);

      private:
         std::shared_ptr<game_state> _current_state;
   };

   inline state_manager::state_manager(void) {
      this->_current_state = nullptr;
   }

   inline state_manager::~state_manager(void) {
   }

   inline void state_manager::set_error_state(const std::string &message) {
      this->_current_state = std::make_shared<error_state>(message);
   }

   inline void state_manager::set_state(std::shared_ptr<game_state> state) {

      std::shared_ptr<game_state> old = this->_current_state;

      // if we already have a state to set, tear it down
      if (this->_current_state != nullptr) {
         try {
            if (!this->_current_state->teardown()) {
               this->set_error_state("Failed to teardown game state");
            }
         } catch (std::exception &e) {
            this->set_error_state("Teardown failed: " + std::string(e.what()));
         }
      }

      // change the state over
      this->_current_state = state;

      // if we have a valid state, init it
      if (this->_current_state != nullptr) {
         try {
            if (!this->_current_state->init()) {
               this->set_error_state("Failed to initialize game state");
            }
         } catch (std::exception &e) {
            this->set_error_state("Init failed: " + std::string(e.what()));
         }
      }

   }

   inline void state_manager::update(const unsigned int elapsed, const int width, const int height) {

      // make sure we have a state to work with
      if (this->_current_state != nullptr) {

         // update the state
         if (!this->_current_state->update(elapsed)) {

            // false, out the back-end of update means that
            // we're ready to move onto the next state
            this->set_state(this->_current_state->next());

            // start all state changes with a resize event
            this->resize(width, height);

         } else {

            // render this state out now
            this->_current_state->render();

         }

      }

   }

   inline void state_manager::render(void) {

      // make sure that we have a valid state to work with
      if (this->_current_state != nullptr) {
         this->_current_state->render();
      }
   }

   inline void state_manager::raise_event(const SDL_Event &event) {

      // make sure we have a state to work with
      if (this->_current_state != nullptr) {
         this->_current_state->handle_event(event);
      }

   }

   inline void state_manager::key_pressed(const SDL_Event &event) {
      if (this->_current_state != nullptr) {
         this->_current_state->key_pressed(event);
      }
   }

   inline void state_manager::key_released(const SDL_Event &event) {
      if (this->_current_state != nullptr) {
         this->_current_state->key_released(event);
      }
   }

   inline void state_manager::mouse_moved(const SDL_Event &event) {
      if (this->_current_state != nullptr) {
         this->_current_state->mouse_moved(event);
      }
   }

   inline void state_manager::mouse_pressed(const SDL_Event &event) {
      if (this->_current_state != nullptr) {
         this->_current_state->mouse_pressed(event);
      }
   }

   inline void state_manager::mouse_released(const SDL_Event &event) {
      if (this->_current_state != nullptr) {
         this->_current_state->mouse_released(event);
      }
   }

   inline void state_manager::resize(const int width, const int height) {
      if (this->_current_state != nullptr) {
         this->_current_state->resize(width, height);
      }
   }
}

#endif //__phony_stmgr_hpp_
