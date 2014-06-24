
#include "../stdinc.hpp"

namespace phony {

   light::light(GLuint n) {
      this->_lightNumber = n;

      _position.x = 0.0f; _position.y = 0.0f; _position.z = 0.0f; _position.w = 0.0f;
      _spotDirection.x = 0.0f; _spotDirection.y = -1.0f; _spotDirection.z = 0.0f;

      _ambient = rgba(0.5f, 0.5f, 0.5f, 1.0f);
      _specular = rgba(1.0f, 1.0f, 1.0f, 1.0f);
      _diffuse = rgba(1.0f, 1.0f, 1.0f, 1.0f);

      _spotCutoff = 180.0f;
      _spotExponent = 128;

      this->dirty(L_DIRTY_POSITION | L_DIRTY_AMBIENT | L_DIRTY_SPECULAR | L_DIRTY_DIFFUSE);
   }

   light::~light(void) {
      this->disable();
   }

   void light::enable() {
      glEnable(this->_lightNumber);
   }

   void light::disable() {
      glDisable(this->_lightNumber);
   }

   void light::set() {

      if (this->_dirtyFlags & L_DIRTY_AMBIENT) {
         glLightfv(this->_lightNumber, GL_AMBIENT, _ambient.c());
      }

      if (this->_dirtyFlags & L_DIRTY_DIFFUSE) {
         glLightfv(this->_lightNumber, GL_DIFFUSE, _diffuse.c());
      }

      if (this->_dirtyFlags & L_DIRTY_SPECULAR) {
         glLightfv(this->_lightNumber, GL_SPECULAR, _specular.c());
      }

      if (this->_dirtyFlags & L_DIRTY_POSITION) {
         float pos[] = { _position.x, _position.y, _position.z, _position.w };
         glLightfv(this->_lightNumber, GL_POSITION, pos);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTDIR) {
         float dir[] = { _spotDirection.x, _spotDirection.y, _spotDirection.z };
         glLightfv(this->_lightNumber, GL_SPOT_DIRECTION, dir);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTCUT) {
         glLightf(this->_lightNumber, GL_SPOT_CUTOFF, _spotCutoff);
      }

      if (this->_dirtyFlags & L_DIRTY_SPOTEXP) {
         glLightf(this->_lightNumber, GL_SPOT_EXPONENT, _spotExponent);
      }

      if (this->_dirtyFlags & L_DIRTY_CONSATT) {
         glLightf(this->_lightNumber, GL_CONSTANT_ATTENUATION, this->_constantAttenuation);
      }

      if (this->_dirtyFlags & L_DIRTY_LINATT) {
         glLightf(this->_lightNumber, GL_LINEAR_ATTENUATION, this->_linearAttenuation);
      }

      if (this->_dirtyFlags & L_DIRTY_QUADATT) {
         glLightf(this->_lightNumber, GL_QUADRATIC_ATTENUATION, this->_quadraticAttenuation);
      }

      this->_dirtyFlags = 0;
   }

}
