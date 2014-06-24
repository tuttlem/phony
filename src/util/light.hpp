
#ifndef __phony_light_hpp_

#define __phony_light_hpp_

#include "../stdinc.hpp"

#define  L_DIRTY_AMBIENT      0x0001
#define  L_DIRTY_DIFFUSE      0x0002
#define  L_DIRTY_SPECULAR     0x0004
#define  L_DIRTY_POSITION     0x0008
#define  L_DIRTY_SPOTDIR      0x0010
#define  L_DIRTY_SPOTEXP      0x0020
#define  L_DIRTY_CONSATT      0x0040
#define  L_DIRTY_LINATT       0x0080
#define  L_DIRTY_QUADATT      0x0100
#define  L_DIRTY_SPOTCUT      0x0200

namespace phony {

   class light {
      public:
         light(GLuint n);
         ~light(void);

         void enable();
         void disable();
         void set();

         void dirty(unsigned short f) {
            this->_dirtyFlags |= f;
         }

         const rgba ambient(void) const { return _ambient; }
         const rgba diffuse(void) const { return _diffuse; }
         const rgba specular(void) const { return _specular; }

         const glm::vec4 position(void) const { return _position; }
         const glm::vec3 spotDirection(void) const { return _spotDirection; }

         const float spotCutoff(void) const { return _spotCutoff; }
         const float spotExponent(void) const { return _spotExponent; }
         const float constantAttenuation(void) const { return _constantAttenuation; }
         const float linearAttenuation(void) const { return _linearAttenuation; }
         const float quadraticAttenuation(void) const { return _quadraticAttenuation; }

         void ambient(const rgba &a) { this->dirty(L_DIRTY_AMBIENT); this->_ambient = a; }
         void diffuse(const rgba &d) { this->dirty(L_DIRTY_DIFFUSE); this->_diffuse = d; }
         void specular(const rgba &s) { this->dirty(L_DIRTY_SPECULAR); this->_specular = s; }
         void position(const glm::vec4 &p) { this->dirty(L_DIRTY_POSITION); this->_position = p; }
         void spotDirection(const glm::vec3 &d) { this->dirty(L_DIRTY_SPOTDIR); this->_spotDirection = d; }
         void spotCutoff(const float c) { this->dirty(L_DIRTY_SPOTCUT); this->_spotCutoff = c; }
         void spotExponent(const float e) { this->dirty(L_DIRTY_SPOTEXP); this->_spotExponent = e; }
         void constantAttenuation(const float a) { this->dirty(L_DIRTY_CONSATT); this->_constantAttenuation = a; }
         void linearAttenuation(const float a) { this->dirty(L_DIRTY_LINATT); this->_linearAttenuation = a; }
         void quadraticAttenuation(const float a) { this->dirty(L_DIRTY_QUADATT); this->_quadraticAttenuation = a; }


      private:
         rgba _ambient, _diffuse, _specular;
         glm::vec4 _position;
         glm::vec3 _spotDirection;
         float _spotCutoff, _spotExponent;
         float _constantAttenuation,
               _linearAttenuation,
               _quadraticAttenuation;

         GLuint _lightNumber;

         unsigned short _dirtyFlags;
   };

}
#endif
