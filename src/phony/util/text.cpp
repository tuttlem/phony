
#include "../stdinc.hpp"

namespace phony {

   TTF_Font *text::_font = nullptr;

   bool text::init(const std::string &ttf_file, unsigned int size) {
      _font = TTF_OpenFont(ttf_file.c_str(), size);
      return _font != nullptr;
   }

   bool text::teardown(void) {
      TTF_CloseFont(_font);
      return true;
   }

   void text::print(const float x, const float y, const rgba &col, const std::string &s) {
      SDL_Color c = {
         (unsigned char)(col.r() * 255.0f),
         (unsigned char)(col.g() * 255.0f),
         (unsigned char)(col.b() * 255.0f)
      };

      SDL_Surface *message = TTF_RenderText_Blended(_font, s.c_str(), c);
      unsigned int texture = 0;

      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, message->w, message->h,
                                0, GL_BGRA, GL_UNSIGNED_BYTE, message->pixels);

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();

      bool reenableLighting = false;
      if (glIsEnabled(GL_LIGHTING)) {
         glDisable(GL_LIGHTING);
         reenableLighting = true;
      }

      scene::resize_2d(window_width(), window_height());

      glBegin(GL_QUADS);
         glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, 0.0f);
         glTexCoord2f(1.0f, 0.0f); glVertex3f(x + message->w, y, 0.0f);
         glTexCoord2f(1.0f, 1.0f); glVertex3f(x + message->w, y + message->h, 0.0f);
         glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + message->h, 0.0f);
      glEnd();

      glDeleteTextures(1, &texture);
      SDL_FreeSurface(message);

      if (reenableLighting) {
         glEnable(GL_LIGHTING);
      }

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

      glMatrixMode(GL_MODELVIEW);
   }
}
