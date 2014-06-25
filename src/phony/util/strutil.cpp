
#include "../stdinc.hpp"

namespace phony {

   std::vector<std::string> strutil::split(const std::string &source, const char delim) {
      std::stringstream ss(source);
      std::string item;
      std::vector<std::string> items;

      while (std::getline(ss, item, delim)) {
         items.push_back(item);
      }

      return items;
   }

}
