
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
         void set(unsigned short f = 0);

         void dirty(unsigned short f) {
            this->_dirtyFlags |= f;
         }

         const rgba ambient(void) const { return _ambient; }
         const rgba diffuse(void) const { return _diffuse; }
         const rgba specular(void) const { return _specular; }

         const glm::vec4 position(void) const { return _position; }
         const glm::vec3 spot_direction(void) const { return _spot_direction; }

         const float spot_cutoff(void) const { return _spot_cutoff; }
         const float spot_exponent(void) const { return _spot_exponent; }
         const float constant_attenuation(void) const { return _constant_attenuation; }
         const float linear_attenuation(void) const { return _linear_attenuation; }
         const float quadratic_attenuation(void) const { return _quadratic_attenuation; }

         void ambient(const rgba &a) { this->dirty(L_DIRTY_AMBIENT); this->_ambient = a; }
         void diffuse(const rgba &d) { this->dirty(L_DIRTY_DIFFUSE); this->_diffuse = d; }
         void specular(const rgba &s) { this->dirty(L_DIRTY_SPECULAR); this->_specular = s; }
         void position(const glm::vec4 &p) { this->dirty(L_DIRTY_POSITION); this->_position = p; }
         void spot_direction(const glm::vec3 &d) { this->dirty(L_DIRTY_SPOTDIR); this->_spot_direction = d; }
         void spot_cutoff(const float c) { this->dirty(L_DIRTY_SPOTCUT); this->_spot_cutoff = c; }
         void spot_exponent(const float e) { this->dirty(L_DIRTY_SPOTEXP); this->_spot_exponent = e; }
         void constant_attenuation(const float a) { this->dirty(L_DIRTY_CONSATT); this->_constant_attenuation = a; }
         void linear_attenuation(const float a) { this->dirty(L_DIRTY_LINATT); this->_linear_attenuation = a; }
         void quadratic_attenuation(const float a) { this->dirty(L_DIRTY_QUADATT); this->_quadratic_attenuation = a; }


      private:
         rgba _ambient, _diffuse, _specular;
         glm::vec4 _position;
         glm::vec3 _spot_direction;
         float _spot_cutoff, _spot_exponent;
         float _constant_attenuation,
               _linear_attenuation,
               _quadratic_attenuation;

         GLuint _light_number;

         unsigned short _dirtyFlags;
   };

}
#endif
