
#include "../stdinc.hpp"

namespace phony {

   void game::run(std::shared_ptr<game_state> initialState) {
      // manages the current game time
      sf::Clock clock;
      sf::Clock fpsClock;

      this->_stateManager.setState(initialState);
      this->_running = true;

      this->_window->setVerticalSyncEnabled(true);
      this->_window->setFramerateLimit(60);

      while (this->_running && this->_stateManager.running()) {
         sf::Event event;

         while (this->_window->pollEvent(event)) {

            switch (event.type) {
               case sf::Event::Closed:
                  this->_running = false;
                  break;

               case sf::Event::Resized:
                  this->_width = event.size.width;
                  this->_height = event.size.height;

                  this->_stateManager.resize(event);
                  break;

               case sf::Event::KeyPressed:
                  this->_stateManager.keyPressed(event);
                  break;

               case sf::Event::KeyReleased:
                  this->_stateManager.keyReleased(event);
                  break;

               case sf::Event::MouseMoved:
                  this->_stateManager.mouseMoved(event);
                  break;

               case sf::Event::MouseButtonPressed:
                  this->_stateManager.mousePressed(event);
                  break;

               case sf::Event::MouseButtonReleased:
                  this->_stateManager.mouseReleased(event);
                  break;

               default:
                  this->_stateManager.raiseEvent(event);
                  break;
            }

         }

         // get the current elapsed time
         sf::Time elapsed = clock.restart();

         this->_stateManager.update(elapsed);
         this->_stateManager.render();

         this->_window->display();
      }
   }

   const bool game::setupVideo(void) {
      // create the game window
      this->_window = new sf::Window(
         sf::VideoMode(this->_width, this->_height),
         this->_title.c_str(),
         sf::Style::Default,
         sf::ContextSettings(32)
      );

      this->_window->setVerticalSyncEnabled(true);

      return true;
   }

}
