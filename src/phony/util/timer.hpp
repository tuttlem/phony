
#ifndef __phony_timer_hpp_

#define __phony_timer_hpp_

namespace phony {

   typedef std::chrono::high_resolution_clock hrc;
   typedef std::chrono::milliseconds ms;

   class timer {
      public:
         timer(void);

         /** Retrieves the elapsed milliseconds */
         const unsigned int elapsed(void);

      private:
         hrc::time_point _last;
   };

   inline timer::timer(void) : _last(hrc::now()) {
   }

   inline const unsigned int timer::elapsed(void) {
      // get the time now
      hrc::time_point current = hrc::now();

      // calculate the elapsed difference
      long diff = std::chrono::duration_cast<ms>(current - _last).count();

      // new last is now current
      _last = current;

      return (unsigned int)diff;
   }

}

#endif //__phony_timer_hpp_
