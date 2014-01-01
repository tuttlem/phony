
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

         void renderLines(void);
         void renderPolys(void);

         const float getHeight(const int x, const int y);
      private:
         void setColour(const int x, const int y);
         void render(GLenum mode);

      private:
         int            width, height; /* width and height of the map */
         int            step;          /* step to process the map at */
         float          *map;          /* the map data */
   };

   inline void landscape::renderLines(void) {
      this->render(GL_LINES);
   }

   inline void landscape::renderPolys(void) {
      this->render(GL_QUADS);
   }

   inline const float landscape::getHeight(const int x, const int y) {
      int xx = x % this->width;
      int yy = y % this->height;

      return map[xx + (yy * width)] * 5.0f;
   }

}

#endif //__phony_lspace_hpp_
