
#ifndef __phony_strutil_hpp_

#define __phony_strutil_hpp_

namespace phony {

   class strutil {
      public:
         static std::vector<std::string> split(const std::string &source, const char delim);

   };

}

#endif //__phony_strutil_hpp_
