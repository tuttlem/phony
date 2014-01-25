
#include "../stdinc.hpp"

namespace phony {

   const double PION180 = 3.1415926535897 / 180.0;


   const glm::vec3 camera::_view_initial(0.0f, 0.0f, -1.0f);
   const glm::vec3 camera::_up_initial(0.0f, 1.0f, 0.0f);
   const glm::vec3 camera::_right_initial(1.0f, 0.0f, 0.0);

   camera::camera(void) {
      _position    = glm::vec3(0.0f, 0.0f, 0.0f);
      _view_dir     = _view_initial;
      _right_vector = _right_initial;
      _up_vector    = _up_initial;

      _rotated_x = _rotated_y = _rotated_z = 0.0f;
   }

   // _positions the camera by transforming the scene
   void camera::place(void) {
      glm::vec3 viewPoint = this->_position + this->_view_dir;

      // setup opengl with gluLookAt
      gluLookAt(
         _position[0], _position[1], _position[2],
         viewPoint[0], viewPoint[1], viewPoint[2],
         _up_vector[0], _up_vector[1], _up_vector[2]
      );
   }

   void camera::move(const glm::vec3 &dir) {
      this->_position += dir;
   }

   void camera::move_to(const glm::vec3 &pos) {
      this->_position = pos;
   }

   // x rotation
   void camera::pitch(const float angle) {
      this->_rotated_x += angle;

      this->_view_dir = glm::normalize(
         this->_view_dir * cosf(angle * PION180) +
         this->_up_vector * sinf(angle * PION180)
      );

      this->_up_vector  = glm::cross(this->_view_dir, this->_right_vector);
      this->_up_vector *= -1;
   }

   void camera::pitch_to(const float angle) {
      this->_rotated_x = angle;

      this->_view_dir = glm::normalize(
         _view_initial * cosf(angle * PION180) +
         _up_initial * sinf(angle * PION180)
      );

      this->_up_vector  = glm::cross(this->_view_dir, _right_initial);
      this->_up_vector *= -1;
   }

   // y rotation
   void camera::yaw(const float angle) {
      this->_rotated_y += angle;

      this->_view_dir = glm::normalize(
         this->_view_dir * cosf(angle * PION180) -
         this->_right_vector * sinf(angle * PION180)
      );

      this->_right_vector = glm::cross(this->_view_dir, this->_up_vector);
   }

   void camera::yaw_to(const float angle) {
      this->_rotated_y = angle;

      this->_view_dir = glm::normalize(
         _view_initial * cosf(angle * PION180) -
         _right_initial * sinf(angle * PION180)
      );

      this->_right_vector = glm::cross(this->_view_dir, _up_initial);
   }

   // z rotation
   void camera::roll(const float angle) {
      this->_rotated_z += angle;

      this->_right_vector = glm::normalize(
         this->_right_vector * cosf(angle * PION180) +
         this->_up_vector * sinf(angle * PION180)
      );

      this->_up_vector  = glm::cross(this->_view_dir, this->_right_vector);
      this->_up_vector *= -1;
   }

   void camera::roll_to(const float angle) {
      this->_rotated_z += angle;

      this->_right_vector = glm::normalize(
         _right_initial * cosf(angle * PION180) +
         _up_initial * sinf(angle * PION180)
      );

      this->_up_vector = glm::cross(_view_initial, this->_right_vector);
      this->_up_vector *= -1;
   }

   // z movement
   void camera::advance(const float distance) {
      this->_position += (this->_view_dir * -distance);
   }

   // y movement
   void camera::ascend(const float distance) {
      this->_position += (this->_up_vector * distance);
   }

   // x movement
   void camera::strafe(const float distance) {
      this->_position += (this->_right_vector * distance);
   }

   void camera::print(void) {
      std::cout << "x: " << this->_rotated_x << ", y: " << this->_rotated_y << ", z: " << this->_rotated_z << std::endl;

      std::cout << "View: [ " << this->_view_dir[0] << ", " << this->_view_dir[1] << ", " << this->_view_dir[2] << std::endl;
      std::cout << "Up: [ " << this->_up_vector[0] << ", " << this->_up_vector[1] << ", " << this->_up_vector[2] << std::endl;
      std::cout << "Right: [ " << this->_right_vector[0] << ", " << this->_right_vector[1] << ", " << this->_right_vector[2] << std::endl;
   }

}

