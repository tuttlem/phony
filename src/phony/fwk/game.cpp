
#include "../stdinc.hpp"

namespace phony {

   bool           _running;
   int            _width, _height;
   unsigned int   _target_ms;
   std::string    _title;

   state_manager  _state_manager;

   SDL_Window     *_window;
   SDL_GLContext   _gl_context;

   void setup_video(void);
   void setup_audio(void);

   void set_framerate(const int fps);


   void phony_run(std::shared_ptr<game_state> initial_state) {

      // manages the current game time
      timer game_timer;

      set_framerate(30);

      _state_manager.set_state(initial_state);
      _state_manager.resize(_width, _height);

      _running = true;

      while (_running && _state_manager.running()) {

         SDL_Event event;

         while (SDL_PollEvent(&event)) {

            switch (event.type) {
               case SDL_QUIT:
                  _running = false;
                  break;

               case SDL_WINDOWEVENT:

                  switch (event.window.event) {
                     case SDL_WINDOWEVENT_RESIZED:
                        _width = event.window.data1;
                        _height = event.window.data2;

                        _state_manager.resize(_width, _height);
                        break;
                  }

                  break;

               case SDL_KEYDOWN:
                  _state_manager.key_pressed(event);
                  break;

               case SDL_KEYUP:
                  _state_manager.key_released(event);
                  break;

               case SDL_MOUSEMOTION:
                  _state_manager.mouse_moved(event);
                  break;

               case SDL_MOUSEBUTTONDOWN:
                  _state_manager.mouse_pressed(event);
                  break;

               case SDL_MOUSEBUTTONUP:
                  _state_manager.mouse_released(event);
                  break;

               default:
                  _state_manager.raise_event(event);
                  break;
            }

         }

         // get the elapsed ms
         unsigned int elapsed = game_timer.elapsed();

         // check if we have time to wait
         if (elapsed < _target_ms) {
            // burn what ever ms remains to stablise the framerate
            unsigned int diff = _target_ms - elapsed;
            std::this_thread::sleep_for(std::chrono::milliseconds(diff));
         }

         // update logic for the state
         _state_manager.update(
            game_timer.elapsed(),
            _width,
            _height
         );

         // render this state to screen
         _state_manager.render();

         // flip the back buffer
         SDL_GL_SwapWindow(_window);
      }
   }

   const bool phony_init(const int width, const int height, const std::string &title) {
      _width = width;
      _height = height;
      _title = title;

      _window = nullptr;
      _gl_context = nullptr;

      if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
         throw std::runtime_error(SDL_GetError());
      }

      setup_video();
      setup_audio();

      return true;
   }

   const bool phony_teardown(void) {

      // teardown the audio mixer
      Mix_CloseAudio();

      // teardown the window
      if (_window != nullptr) {
         SDL_DestroyWindow(_window);
         _window = nullptr;
      }

      // get out of sdl
      Mix_Quit();
      SDL_Quit();

      return true;
   }

   void setup_video(void) {

      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

      _window = SDL_CreateWindow(
         _title.c_str(),
         100, 100,
         _width, _height,
         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
      );

      if (_window == nullptr) {
         throw std::runtime_error(SDL_GetError());
      }

      _gl_context = SDL_GL_CreateContext(_window);

      if (_gl_context == nullptr) {
         throw std::runtime_error(SDL_GetError());
      }

      // use v-sync
      SDL_GL_SetSwapInterval(1);
   }

   void setup_audio(void) {
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
         throw std::runtime_error("Unable to open audio mixer");
      }
   }

   void set_framerate(const int fps) {
      _target_ms = 1000 / fps;
   }
}
