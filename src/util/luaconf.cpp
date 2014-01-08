
#include "../stdinc.hpp"

namespace phony {

   lua_config::lua_config(void) : _state(luaL_newstate()) {
      luaL_openlibs(this->_state);
   }

   lua_config::~lua_config(void) {
      lua_close(this->_state);
   }

   std::shared_ptr<lua_config> lua_config::fromFile(const std::string &filename) {
      auto config = std::make_shared<lua_config>();

      if ((luaL_dofile(config->_state, filename.c_str())) != 0) {
         throw std::runtime_error("Unable to open lua file " + filename);
      }

      return config;
   }

   template<typename T>
   T lua_config::getValue(const std::string &name, const std::function<T()> &getter) {
      std::vector<std::string> items = strutil::split(name, '.');
      int length = items.size();

      lua_getglobal(this->_state, items[0].c_str());

      for (int idx = 1; idx < length; idx ++) {
         lua_getfield(this->_state, -1, items[idx].c_str());
      }

      T value = getter();

      for (int idx = 0; idx < length; idx ++) {
         lua_pop(this->_state, 1);
      }

      return value;
   }

   const int lua_config::getInt(const std::string &name) {
      std::function<int()> fn = [&]() {
         return (int)lua_tointeger(this->_state, -1);
      };

      return getValue(name, fn);
   }

   const double lua_config::getDouble(const std::string &name) {
      std::function<double()> fn = [&]() {
         return (double)lua_tonumber(this->_state, -1);
      };

      return getValue(name, fn);
   }

   const bool lua_config::getBool(const std::string &name) {
      std::function<bool()> fn = [&]() {
         return (bool)lua_toboolean(this->_state, -1);
      };

      return getValue(name, fn);
   }

   const std::string lua_config::getString(const std::string &name) {
      std::function<std::string()> fn = [&]() {
         return std::string(lua_tostring(this->_state, -1));
      };

      return getValue(name, fn);
   }

}
