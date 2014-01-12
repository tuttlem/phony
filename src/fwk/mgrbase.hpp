
#ifndef __phony_mgrbase_hpp_

#define __phony_mgrbase_hpp_

namespace phony {

   template<class T>
   class singleton_manager {
      public:
         singleton_manager(void) {
         }

         virtual ~singleton_manager(void) {
            this->clear();
         }

         virtual void clear() {
         }

         static std::shared_ptr<T> instance(void) {
            if (singleton_manager<T>::_instance == nullptr) {
               singleton_manager<T>::_instance = std::make_shared<T>();
            }

            return _instance;
         }

      private:
         static std::shared_ptr<T> _instance;
   };

   template<class T>
   std::shared_ptr<T> singleton_manager<T>::_instance = nullptr;
}

#endif //__phony_mgrbase_hpp_
