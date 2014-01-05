
#ifndef __phony_tween_hpp_

#define __phony_tween_hpp_

namespace phony {

   /** Provides a base interface for value interpolation */
   template<class T>
   class tweener {
      public:
         /** Construction */
         tweener(T start, T end, const bool repeat, const unsigned int ticks);

         /** Destruction */
         virtual ~tweener(void);

         /** Resets the state of this tweener */
         void reset(void);

         /** Gets the value of this tweener */
         T value(void);

         /** Determines if the tweener has finished */
         const bool finished(void) { return _finished; }

      protected:
         /** User supplied value getter */
         virtual T value_internal(const float prog) = 0;

      protected:
         bool           _repeat, _finished;

         T              _start, _end;
         timer          _clock;
         unsigned int   _prog, _ticks;
   };

   /** Linear tweener */
   template<class T>
   class lin_tweener : public tweener<T> {
      public:
         /** Construction */
         lin_tweener(T start, T end,
               const bool repeat, const unsigned int ticks);

      protected:
         /** User supplied value getter */
         T value_internal(const float prog);

      private:
         T       _length;
   };

   /** Trig tweener */
   template<class T>
   class trig_tweener : public tweener<T> {
      public:
         /** Construction */
         trig_tweener(T start, T end,
               const bool repeat, const unsigned int ticks);

      protected:
         /** User supplied value getter */
         T value_internal(const float prog);

      private:
         T       _length;
   };

   /** Logarithmic tweener */
   template<class T>
   class log_tweener : public tweener<T> {
      public:
         /** Construction */
         log_tweener(T start, T end,
               const bool repeat, const unsigned int ticks);

      protected:
         /** User supplied value getter */
         T value_internal(const float prog);

      private:
         T       _length;
   };

   /** Parabolic tweener */
   template<class T>
   class parb_tweener : public tweener<T> {
      public:
         /** Construction */
         parb_tweener(T start, T end,
               const bool repeat, const unsigned int ticks);

      protected:
         /** User supplied value getter */
         T value_internal(const float prog);

      private:
         T       _length;
   };

   /** Construction */
   template<class T>
   tweener<T>::tweener(T start, T end,
         const bool repeat, const unsigned int ticks) {
      _start = start; _end = end;
      _repeat = repeat; _ticks = ticks;

      _prog = 0;
   }

   /** Destruction */
   template<class T>
   tweener<T>::~tweener(void) { }

   /** Resets the state of this tweener */
   template<class T>
   void tweener<T>::reset(void) {
      _prog = 0;
      _finished = false;
   }

   /** Gets the value of this tweener */
   template<class T>
   T tweener<T>::value(void) {

      // if we've already finished,
      // no more processing
      if (_finished) {
         return _end;
      }

      // accumulate split timing
      _prog += _clock.elapsed();

      // need to handle boundaries if we're repeating
      if (_repeat) {
         // have we overflowed?
         if (_prog > _ticks) {
            _prog %= _ticks;
         }
      } else {
         // have we finished?
         if (_prog > _ticks) {
            _finished = true;
         }
      }

      // return the calculated value
      return this->value_internal((float)_prog/(float)_ticks);
   }

   /** Construction */
   template<class T>
   lin_tweener<T>::lin_tweener(T start, T end,
         const bool repeat, const unsigned int ticks) :
      tweener<T>(start, end, repeat, ticks) {
      // calculate the linear delta
      _length = (end - start);
   }

   /** User supplied value getter */
   template<class T>
   T lin_tweener<T>::value_internal(const float prog) {
      return this->_start + (prog * _length);
   }

   /** Construction */
   template<class T>
   trig_tweener<T>::trig_tweener(T start, T end,
         const bool repeat, const unsigned int ticks) :
      tweener<T>(start, end, repeat, ticks) {
      // calculate the linear delta
      _length = (end - start);
   }

   /** User supplied value getter */
   template<class T>
   T trig_tweener<T>::value_internal(const float prog) {
      return this->_start + (sinf(prog * M_PI_2) * _length);
   }

   /** Construction */
   template<class T>
   log_tweener<T>::log_tweener(T start, T end,
         const bool repeat, const unsigned int ticks) :
      tweener<T>(start, end, repeat, ticks) {
      // calculate the linear delta
      _length = (end - start);
   }

   /** User supplied value getter */
   template<class T>
   T log_tweener<T>::value_internal(const float prog) {
      return this->_start + (log10(1.0f + (prog * 9.0f)) * _length);
   }

   /** Construction */
   template<class T>
   parb_tweener<T>::parb_tweener(T start, T end,
         const bool repeat, const unsigned int ticks) :
      tweener<T>(start, end, repeat, ticks) {
      // calculate the linear delta
      _length = (end - start);
   }

   /** User supplied value getter */
   template<class T>
   T parb_tweener<T>::value_internal(const float prog) {
      return this->_start + ((prog * prog) * _length);
   }


}

#endif // __phony_tween_hpp_
