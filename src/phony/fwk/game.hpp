
#ifndef __phony_game_hpp_

#define __phony_game_hpp_

namespace phony {

   extern bool    _running;
   extern int     _width, _height;
   extern unsigned int _real_fps;
   extern SDL_Window     *_window;
   extern SDL_GLContext   _gl_context;

   const bool phony_init(const int width, const int height, const std::string &title);
   void phony_run(std::shared_ptr<game_state> initial_state);
   const bool phony_teardown(void);

   void setup_for_2d(void);
   void setup_for_3d(void);

   inline const int window_width(void) { return _width; }
   inline const int window_height(void) { return _height; }
   inline const bool game_running(void) { return _running; }
   inline const unsigned int fps(void)  { return _real_fps; }

   inline SDL_Window* game_window(void) { return _window; }
   inline SDL_GLContext gl_context(void) { return _gl_context; }
}

#endif //__phony_game_hpp_
