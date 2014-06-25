
#ifndef __phony_lscape_hpp_

#define __phony_lscape_hpp_

namespace phony {

   /*
    * Heightmap-based landscape
    */
   class landscape {
      public:
         landscape(const int w, const int h);
         ~landscape(void);

         void render_lines(void);
         void render_quads(void);

         const float get_height(const int x, const int y);
      private:
         void set_colour(const int x, const int y);
         void render(GLenum mode);

      private:
         int            _width, _height; /* width and height of the map */
         int            _step;          /* step to process the map at */
         float          *_map;          /* the map data */
   };

   inline void landscape::render_lines(void) {
      this->render(GL_LINES);
   }

   inline void landscape::render_quads(void) {
      this->render(GL_QUADS);
   }

   inline const float landscape::get_height(const int x, const int y) {
      int xx = x % this->_width;
      int yy = y % this->_height;

      return _map[xx + (yy * _width)] * 5.0f;
   }

}

#endif //__phony_lspace_hpp_
