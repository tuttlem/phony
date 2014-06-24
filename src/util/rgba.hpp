
#ifndef __phony_rgba_hpp_

#define __phony_rgba_hpp_

#include "../stdinc.hpp"

namespace phony {
   class rgba {
      public:
         rgba(void)
            : rgba(0.0f, 0.0f, 0.0f, 1.0f) { }
         rgba(float rr, float gg, float bb)
            : rgba(rr, gg, bb, 1.0f) { }
         rgba(float rr, float gg, float bb, float aa) {
            _c[0] = rr; _c[1] = gg; _c[2] = bb; _c[3] = aa;
         }

         const float r(void) const { return _c[0]; }
         const float g(void) const { return _c[1]; }
         const float b(void) const { return _c[2]; }
         const float a(void) const { return _c[3]; }
         const float* c(void) const { return _c; }

         void setGL(void);

      private:
         float _c[4];
   };
}

#endif
