
#ifndef __phony_stmgr_hpp_

#define __phony_stmgr_hpp_

namespace phony {

   class state_manager {
      public:
         state_manager(void);
         virtual ~state_manager(void);

         void setState(std::shared_ptr<game_state> state);
         void update(const sf::Time &elapsed);
         void render(void);
         void raiseEvent(const sf::Event &event);

         const bool running(void) const { return this->_currentState != nullptr; }

         void keyPressed(const sf::Event &event);
         void keyReleased(const sf::Event &event);
         void mouseMoved(const sf::Event &event);
         void mousePressed(const sf::Event &event);
         void mouseReleased(const sf::Event &event);
         void resize(const sf::Event &event);

      private:
         std::shared_ptr<game_state> _currentState;
   };

   inline state_manager::state_manager(void) {
      this->_currentState = nullptr;
   }

   inline state_manager::~state_manager(void) {
   }

   inline void state_manager::setState(std::shared_ptr<game_state> state) {

      std::shared_ptr<game_state> old = this->_currentState;

      // if we already have a state to set, tear it down
      if (this->_currentState != nullptr) {
         this->_currentState->teardown();
      }

      // change the state over
      this->_currentState = state;

      // if we have a valid state, init it
      if (this->_currentState != nullptr) {
         this->_currentState->init();
      }

   }

   inline void state_manager::update(const sf::Time &elapsed) {

      // make sure we have a state to work with
      if (this->_currentState != nullptr) {

         // update the state
         if (!this->_currentState->update(elapsed)) {

            // false, out the back-end of update means that
            // we're ready to move onto the next state
            this->setState(this->_currentState->next());

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

   inline void state_manager::raiseEvent(const sf::Event &event) {

      // make sure we have a state to work with
      if (this->_currentState != nullptr) {
         this->_currentState->handleEvent(event);
      }

   }

   inline void state_manager::keyPressed(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->keyPressed(event.key);
      }
   }

   inline void state_manager::keyReleased(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->keyReleased(event.key);
      }
   }

   inline void state_manager::mouseMoved(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mouseMoved(event.mouseMove);
      }
   }

   inline void state_manager::mousePressed(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mousePressed(event.mouseButton);
      }
   }

   inline void state_manager::mouseReleased(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->mouseReleased(event.mouseButton);
      }
   }

   inline void state_manager::resize(const sf::Event &event) {
      if (this->_currentState != nullptr) {
         this->_currentState->resize(event.size);
      }
   }
}

#endif //__phony_stmgr_hpp_
