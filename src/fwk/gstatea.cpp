
#include "../stdinc.hpp"

namespace phony {

   const bool game_state_async::init(void) {

      // define the function to run
      auto func = std::bind(
         &game_state_async::updateInternal,
         this
      );

      // run the thread off here
      this->updater = std::async(
         std::launch::async,
         func
      );

      return true;

   }

   const bool game_state_async::teardown(void) {
      return true;
   }

   const bool game_state_async::update(const sf::Time &elapsed) {
      return this->updater.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
   }

}
