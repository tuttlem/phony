
#include "../stdinc.hpp"

namespace phony {

   light::light(GLuint n) {
      this->_light_number = n;

      _position.x = 0.0f; _position.y = 0.0f; _position.z = 0.0f; _position.w = 0.0f;
      _spot_direction.x = 0.0f; _spot_direction.y = -1.0f; _spot_direction.z = 0.0f;

      _ambient = rgba(0.5f, 0.5f, 0.5f, 1.0f);
      _specular = rgba(1.0f, 1.0f, 1.0f, 1.0f);
      _diffuse = rgba(1.0f, 1.0f, 1.0f, 1.0f);

      _spot_cutoff = 180.0f;
      _spot_exponent = 128;

      this->_dirtyFlags = L_DIRTY_POSITION | L_DIRTY_AMBIENT | L_DIRTY_SPECULAR | L_DIRTY_DIFFUSE;
   }

   light::~light(void) {
      this->disable();
   }

   void light::enable() {
      this->set();
      glEnable(this->_light_number);
   }

   void light::disable() {
      glDisable(this->_light_number);
   }

   void light::set(unsigned short n) {
      this->_dirtyFlags |= n;

      if (this->_dirtyFlags & L_DIRTY_AMBIENT) {
         glLightfv(this->_light_number, GL_AMBIENT, _ambient.c());
      }

      if (this->_dirtyFlags & L_DIRTY_DIFFUSE) {
         glLightfv(this->_light_number, GL_DIFFUSE, _diffuse.c());
      }

      if (this->_dirtyFlags & L_DIRTY_SPECULAR) {
         glLightfv(this->_light_number, GL_SPECULAR, _specular.c());
      }

      if (this->_dirtyFlags & L_DIRTY_POSITION) {
         float pos[] = { _position.x, _position.y, _position.z, _position.w };
         glLightfv(this->_light_number, GL_POSITION, pos);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTDIR) {
         float dir[] = { _spot_direction.x, _spot_direction.y, _spot_direction.z };
         glLightfv(this->_light_number, GL_SPOT_DIRECTION, dir);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTCUT) {
         glLightf(this->_light_number, GL_SPOT_CUTOFF, _spot_cutoff);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTEXP) {
         glLightf(this->_light_number, GL_SPOT_EXPONENT, _spot_exponent);
      }

      if (this->_dirtyFlags & L_DIRTY_CONSATT) {
         glLightf(this->_light_number, GL_CONSTANT_ATTENUATION, this->_constant_attenuation);
      }

      if (this->_dirtyFlags & L_DIRTY_LINATT) {
         glLightf(this->_light_number, GL_LINEAR_ATTENUATION, this->_linear_attenuation);
      }

      if (this->_dirtyFlags & L_DIRTY_QUADATT) {
         glLightf(this->_light_number, GL_QUADRATIC_ATTENUATION, this->_quadratic_attenuation);
      }

      this->_dirtyFlags = 0;
   }

}
