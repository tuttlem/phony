
#include "../stdinc.hpp"

namespace phony {

   const bool game_state_async::init(void) {

      // define the function to run
      auto func = std::bind(
         &game_state_async::update_internal,
         this
      );

      // run the thread off here
      this->_updater = std::async(
         std::launch::async,
         func
      );

      return true;

   }

   const bool game_state_async::teardown(void) {
      return true;
   }

   const bool game_state_async::update(const unsigned int elapsed) {
      return this->_updater.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
   }

}
