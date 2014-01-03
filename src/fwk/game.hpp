
#ifndef __phony_game_hpp_

#define __phony_game_hpp_

namespace phony {

   /** Basic game flow control object */
   class game {
      public:
         game(void);
         virtual ~game(void);

         const bool init(const int width, const int height, const std::string &title);
         void run(std::shared_ptr<game_state> initialState);
         const bool teardown(void);

         void setupFor2D(void);
         void setupFor3D(void);

         const int width(void) const    { return _width; }
         const int height(void) const   { return _height; }
         const bool running(void) const { return _running; }

      private:
         const bool setupVideo(void);
         void setFramerate(const int fps);

         bool        _running;
         int         _width, _height;
         std::string _title;

         sf::Window  *_window;

         state_manager _stateManager;
   };


   inline game::game(void) {
   }

   inline game::~game(void) {
      this->teardown();
   }

   inline const bool game::init(const int width, const int height, const std::string &title) {
      this->_width = width;
      this->_height = height;
      this->_title = title;

      this->_window = NULL;

      return this->setupVideo();
   }

   inline const bool game::teardown(void) {

      // if we have a built window, destroy it
      if (this->_window != NULL) {
         delete this->_window;
         this->_window = NULL;
      }

      return true;
   }

}

#endif //__phony_game_hpp_
