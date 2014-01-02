
#ifndef __phony_prim_hpp_

#define __phony_prim_hpp_

namespace phony {

   /** Helper functions for primitive drawing */
   class primitive {
      public:
         static void vertex(const float x,  const float y,  const float z,
                            const float tx, const float ty);

         static void poly(const float x1, const float y1, const float z1,
                        const float x2, const float y2, const float z2,
                        const float x3, const float y3, const float z3,
                        const float x4, const float y4, const float z4,
                        const float nx, const float ny, const float nz);

         static void cube(const float s,
                          const float r, const float g, const float b, const float a);
         static void cube(const float s);

         static void cuboid(const float sx, const float sy, const float sz,
                            const float r,  const float g,  const float b, const float a);
         static void cuboid(const float sx, const float sy, const float sz);
   };

}

#endif //__phony_prim_hpp_
