
#ifndef __phony_prim_hpp_

#define __phony_prim_hpp_

namespace phony {

   template<class T> inline T operator~ (T a) { return (T)~(int)a; }
   template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
   template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
   template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
   template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
   template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
   template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }
   enum class side {
      NONE = 0,
      TOP  = 1,
      BOTTOM = 2,
      LEFT = 4,
      RIGHT = 8,
      FRONT = 16,
      BACK = 32,
      ALL = (side::TOP | side::BOTTOM |
             side::LEFT | side::RIGHT |
             side::FRONT | side::BACK)
   };

   /** Helper functions for primitive drawing */
   class primitive {
      public:
         static void cuboid(const glm::vec3 &v1, const glm::vec3 &v2, const side s = side::ALL);
         static void cuboid(const glm::vec3 &v, const side s = side::ALL);
         static void cube(const glm::vec3 &v1, const float f, const side s = side::ALL);
         static void cube(const float f, const side s = side::ALL);


         static void poly(
            const float x1, const float y1, const float z1,
            const float x2, const float y2, const float z2,
            const float x3, const float y3, const float z3,
            const float x4, const float y4, const float z4,
            const float nx, const float ny, const float nz
         );
   };

}

#endif //__phony_prim_hpp_
