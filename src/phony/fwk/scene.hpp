
#ifndef __phony_scene_hpp_

#define __phony_scene_hpp_

namespace phony {

   /** Holds some scene helper functions */
   class scene {
      public:
         static void resize_2d(const int width, const int height);
         static void resize_3d(
            const int width, const int height,
            const float fovy = 45.0f, const float zNear = 0.1f, const float zFar = 1000.0f
         );
   };

}

#endif //__phony_scene_hpp_
