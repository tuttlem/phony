
#include "../stdinc.hpp"

namespace phony {
   void rgba::set_gl(void) {
      glColor4f(this->_c[0], this->_c[1], this->_c[2], this->_c[3]);
   }
}
