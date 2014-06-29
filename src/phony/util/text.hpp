
#ifndef __phony_text_hpp_

#define __phony_text_hpp_

namespace phony {

   class text {
      public:
         static bool init(const std::string &ttf_file, unsigned int size);
         static bool teardown(void);

         static void print(const float x, const float y, const rgba &col, const std::string &s);

      private:
         static TTF_Font *_font;
   };

}

#endif // __phony_text_hpp_
