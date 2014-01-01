
#include "../stdinc.hpp"

namespace phony {

   const double PION180 = 3.1415926535897 / 180.0;

   camera::camera(void) {
      position    = glm::vec3(0.0f, 0.0f, 0.0f);
      viewDir     = glm::vec3(0.0f, 0.0f, -1.0f);
      rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
      upVector    = glm::vec3(0.0f, 1.0f, 0.0f);

      rotatedX = rotatedY = rotatedZ = 0.0f;
   }

   // positions the camera by transforming the scene
   void camera::place(void) {
      glm::vec3 viewPoint = this->position + this->viewDir;

      // setup opengl with gluLookAt
      gluLookAt(
            position[0], position[1], position[2],
            viewPoint[0], viewPoint[1], viewPoint[2],
            upVector[0], upVector[1], upVector[2]
            );
   }

   void camera::move(const glm::vec3 &dir) {
      this->position += dir;
   }

   // x rotation
   void camera::pitch(const float angle) {
      this->rotatedX += angle;

      this->viewDir = glm::normalize(
            this->viewDir * cosf(angle * PION180) +
            this->upVector * sinf(angle * PION180)
            );

      this->upVector  = glm::cross(this->viewDir, this->rightVector);
      this->upVector *= -1;
   }

   // y rotation
   void camera::yaw(const float angle) {
      this->rotatedY += angle;

      this->viewDir = glm::normalize(
            this->viewDir * cosf(angle * PION180) -
            this->rightVector * sinf(angle * PION180)
            );

      this->rightVector = glm::cross(this->viewDir, this->upVector);
   }

   // z rotation
   void camera::roll(const float angle) {
      this->rotatedZ += angle;

      this->rightVector = glm::normalize(
            this->rightVector * cosf(angle * PION180) +
            this->upVector * sinf(angle * PION180)
            );

      this->upVector  = glm::cross(this->viewDir, this->rightVector);
      this->upVector *= -1;
   }

   // z movement
   void camera::advance(const float distance) {
      this->position += (this->viewDir * -distance);
   }

   // y movement
   void camera::ascend(const float distance) {
      this->position += (this->upVector * distance);
   }

   // x movement
   void camera::strafe(const float distance) {
      this->position += (this->rightVector * distance);
   }

   void camera::print(void) {
      std::cout << "x: " << this->rotatedX << ", y: " << this->rotatedY << ", z: " << this->rotatedZ << std::endl;

      std::cout << "View: [ " << this->viewDir[0] << ", " << this->viewDir[1] << ", " << this->viewDir[2] << std::endl;
      std::cout << "Up: [ " << this->upVector[0] << ", " << this->upVector[1] << ", " << this->upVector[2] << std::endl;
      std::cout << "Right: [ " << this->rightVector[0] << ", " << this->rightVector[1] << ", " << this->rightVector[2] << std::endl;
   }

}
