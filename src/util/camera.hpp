
#ifndef __phony_camera_hpp_

#define __phony_camera_hpp_

namespace phony {

   class camera {
      private:
         glm::vec3 _view_dir,
            _right_vector,
            _up_vector,
            _position;

         float _rotated_x,
               _rotated_y,
               _rotated_z;

      public:
         camera(void);

         // _positions the camera by transforming the scene
         void place(void);

         void move(const glm::vec3 &dir);
         void move_to(const glm::vec3 &pos);

         // x rotation
         void pitch(const float angle);
         void pitch_to(const float angle);

         // y rotation
         void yaw(const float angle);
         void yaw_to(const float angle);

         // z rotation
         void roll(const float angle);
         void roll_to(const float angle);

         // z movement
         void advance(const float distance);
         // y movement
         void ascend(const float distance);
         // x movement
         void strafe(const float distance);

         const glm::vec3& pos(void) const { return _position; }

         void print(void);

      private:
         void pitch_internal(void);
         void yaw_internal(void);
         void roll_internal(void);

         static const glm::vec3 _view_initial;
         static const glm::vec3 _up_initial;
         static const glm::vec3 _right_initial;
   };

}

#endif //__phony_camera_hpp_
