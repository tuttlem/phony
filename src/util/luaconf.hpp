
#ifndef __phony_luaconf_hpp_

#define __phony_luaconf_hpp_

namespace phony {

   class lua_config {
      public:
         lua_config(void);
         virtual ~lua_config(void);

         static std::shared_ptr<lua_config> fromFile(const std::string &filename);

         const int getInt(const std::string &name);
         const double getDouble(const std::string &name);
         const bool getBool(const std::string &name);
         const std::string getString(const std::string &name);

      private:
         template<typename T>
         T getValue(const std::string &name, const std::function<T()> &getter);

         lua_State   *_state;
   };

}

#endif //__phony_luaconf_hpp_
