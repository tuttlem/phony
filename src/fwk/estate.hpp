
#ifndef __phony_estate_hpp_

#define __phony_estate_hpp_

namespace phony {

   class error_state : public game_state {
      public:
         error_state(const std::string &message);

         virtual const bool update(const sf::Time &elapsed);
         virtual const bool render(void);

      private:
         std::string _message;
   };


}

#endif //__phony_estate_hpp_
