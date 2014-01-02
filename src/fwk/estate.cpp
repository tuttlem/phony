
#include "../stdinc.hpp"

namespace phony {

   error_state::error_state(const std::string &message) : _message(message) {
   }

   const bool error_state::update(const sf::Time &elapsed) {
      std::cerr << this->_message << std::endl;
      return false;
   }

   const bool error_state::render(void) {
      std::cerr << this->_message << std::endl;
      return false;
   }

}
