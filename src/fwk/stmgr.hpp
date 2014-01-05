
#ifndef __phony_stmgr_hpp_

#define __phony_stmgr_hpp_

namespace phony {

   class error_state;

   class state_manager {
      public:
         state_manager(void);
         virtual ~state_manager(void);

         void setState(std::shared_ptr<game_state> state);
         void setErrorState(const std::string &message);

         void update(const unsigned int elapsed, const int width, const int height);
         void render(void);
         void raiseEvent(const SDL_Event &event);

         const bool running(void) const { return this->_currentState != nullptr; }

         void keyPressed(const SDL_Event &event);
         void keyReleased(const SDL_Event &event);
         void mouseMoved(const SDL_Event &event);
         void mousePressed(const SDL_Event &event);
         void mouseReleased(const SDL_Event &event);
         void resize(const int width, const int height);

      private:
         std::shared_ptr<game_state> _currentState;
   };

   inline state_manager::state_manager(void) {
      this->_currentState = nullptr;
   }

   inline state_manager::~state_manager(void) {
   }

   inline void state_manager::setErrorState(const std::string &message) {
      this->_currentState = std::make_shared<error_state>(message);
   }

   inline void state_manager::setState(std::shared_ptr<game_state> state) {

      std::shared_ptr<game_state> old = this->_currentState;

      // if we already have a state to set, tear it down
      if (this->_currentState != nullptr) {
         try {
            if (!this->_currentState->teardown()) {
               this->setErrorState("Failed to teardown game state");
            }
         } catch (std::exception &e) {
            this->setErrorState("Teardown failed: " + std::string(e.what()));
         }
      }

      // change the state over
      this->_currentState = state;

      // if we have a valid state, init it
      if (this->_currentState != nullptr) {
         try {
            if (!this->_currentState->init()) {
               this->setErrorState("Failed to initialize game state");
            }
         } catch (std::exception &e) {
            this->setErrorState("Init failed: " + std::string(e.what()));
         }
      }

   }

   inline void state_manager::update(const unsigned int elapsed, const int width, const int height) {

      // make sure we have a state to work with
      if (this->_currentState != nullptr) {

         // update the state
         if (!this->_currentState->update(elapsed)) {

            // false, out the back-end of update means that
            // we're ready to move onto the next state
            this->setState(this->_currentState->next());

            // start all state changes with a resize event
            this->resize(width, height);

         } else {

            // render this state out now
            this->_currentState->render();

         }

      }

   }

   inline void state_manager::render(void) {

      // make sure that we have a valid state to work with
      if (this->_currentState != nullptr) {
         this->_currentState->render();
      }
   }

   inline void state_manager::raiseEvent(const SDL_Event &event) {

      // make sure we have a state to work with
      if (this->_currentState != nullptr) {
         this->_currentState->handleEvent(event);
      }

   }

   inline void state_manager::keyPressed(const SDL_Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->keyPressed(event);
      }
   }

   inline void state_manager::keyReleased(const SDL_Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->keyReleased(event);
      }
   }

   inline void state_manager::mouseMoved(const SDL_Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mouseMoved(event);
      }
   }

   inline void state_manager::mousePressed(const SDL_Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mousePressed(event);
      }
   }

   inline void state_manager::mouseReleased(const SDL_Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mouseReleased(event);
      }
   }

   inline void state_manager::resize(const int width, const int height) {
      if (this->_currentState != nullptr) {
         this->_currentState->resize(width, height);
      }
   }
}

#endif //__phony_stmgr_hpp_
