
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
         void setupVideo(void);
         void setupAudio(void);

         void setFramerate(const int fps);

         bool        _running;
         int         _width, _height;
         std::string _title;

         state_manager _stateManager;

         SDL_Window     *_window;
         //SDL_Renderer   *_renderer;
         SDL_GLContext   _glContext;
   };


   inline game::game(void) {
   }

   inline game::~game(void) {
      this->teardown();
   }

}

#endif //__phony_game_hpp_
