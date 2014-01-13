
#include "../stdinc.hpp"

namespace phony {

   void game::run(std::shared_ptr<game_state> initialState) {

      // manages the current game time
      timer gameTimer;

      this->setFramerate(30);

      this->_stateManager.setState(initialState);
      this->_stateManager.resize(this->_width, this->_height);

      this->_running = true;

      while (this->_running && this->_stateManager.running()) {

         SDL_Event event;

         while (SDL_PollEvent(&event)) {

            switch (event.type) {
               case SDL_QUIT:
                  this->_running = false;
                  break;

               case SDL_WINDOWEVENT:

                  switch (event.window.event) {
                     case SDL_WINDOWEVENT_RESIZED:
                        this->_width = event.window.data1;
                        this->_height = event.window.data2;

                        this->_stateManager.resize(this->_width, this->_height);
                        break;
                  }

                  break;

               case SDL_KEYDOWN:
                  this->_stateManager.keyPressed(event);
                  break;

               case SDL_KEYUP:
                  this->_stateManager.keyReleased(event);
                  break;

               case SDL_MOUSEMOTION:
                  this->_stateManager.mouseMoved(event);
                  break;

               case SDL_MOUSEBUTTONDOWN:
                  this->_stateManager.mousePressed(event);
                  break;

               case SDL_MOUSEBUTTONUP:
                  this->_stateManager.mouseReleased(event);
                  break;

               default:
                  this->_stateManager.raiseEvent(event);
                  break;
            }

         }

         // get the elapsed ms
         unsigned int elapsed = gameTimer.elapsed();

         // check if we have time to wait
         if (elapsed < this->_targetMs) {
            // burn what ever ms remains to stablise the framerate
            unsigned int diff = this->_targetMs - elapsed;
            std::this_thread::sleep_for(std::chrono::milliseconds(diff));
         }

         // update logic for the state
         this->_stateManager.update(
            gameTimer.elapsed(),
            this->_width,
            this->_height
         );

         // render this state to screen
         this->_stateManager.render();

         // flip the back buffer
         SDL_GL_SwapWindow(this->_window);
      }
   }

   const bool game::init(const int width, const int height, const std::string &title) {
      this->_width = width;
      this->_height = height;
      this->_title = title;

      this->_window = nullptr;
      this->_glContext = nullptr;

      if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
         throw std::runtime_error(SDL_GetError());
      }

      this->setupVideo();
      this->setupAudio();

      return true;
   }

   const bool game::teardown(void) {

      // teardown the audio mixer
      Mix_CloseAudio();

      // teardown the window
      if (this->_window != nullptr) {
         SDL_DestroyWindow(this->_window);
         this->_window = nullptr;
      }

      // get out of sdl
      Mix_Quit();
      SDL_Quit();

      return true;
   }

   void game::setupVideo(void) {

      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

      this->_window = SDL_CreateWindow(
         this->_title.c_str(),
         100, 100,
         this->_width, this->_height,
         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
      );

      if (this->_window == nullptr) {
         throw std::runtime_error(SDL_GetError());
      }

      this->_glContext = SDL_GL_CreateContext(this->_window);

      if (this->_glContext == nullptr) {
         throw std::runtime_error(SDL_GetError());
      }

      // use v-sync
      SDL_GL_SetSwapInterval(1);
   }

   void game::setupAudio(void) {
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
         throw std::runtime_error("Unable to open audio mixer");
      }
   }

   void game::setFramerate(const int fps) {
      this->_targetMs = 1000 / fps;
   }
}
