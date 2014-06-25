
#ifndef __phony_luaconf_hpp_

#define __phony_luaconf_hpp_

namespace phony {

   class lua_config {
      public:
         lua_config(void);
         virtual ~lua_config(void);

         static std::shared_ptr<lua_config> from_file(const std::string &filename);

         const int get_int(const std::string &name);
         const double get_double(const std::string &name);
         const bool get_bool(const std::string &name);
         const std::string get_string(const std::string &name);

      private:
         template<typename T>
         T get_value(const std::string &name, const std::function<T()> &getter);

         lua_State   *_state;
   };

}

#endif //__phony_luaconf_hpp_
