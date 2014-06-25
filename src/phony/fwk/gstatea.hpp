
#ifndef __phony_gstatea_hpp_

#define __phony_gstatea_hpp_

namespace phony {

   /** Defines an asynchronous game state */
   class game_state_async : public game_state {
      public:

         virtual const bool init(void);
         virtual const bool teardown(void);

         const bool update(const unsigned int elapsed);

         virtual bool update_internal(void) = 0;

      private:
         std::future<bool> _updater;
   };


}

#endif //__phony_gstatea_hpp_
