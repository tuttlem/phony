
#include "../stdinc.hpp"

namespace phony {

   float perlin::terp(float a, float b, float x) {
      float ft = x * 3.1415927f;
      float f = (1 - cosf(ft)) * 0.5f;

      return a * (1 - f) + b * f;
   }


   float perlin::perlin_2d(const float x, const float y,
         const int octaves, const float persistence) {
      float total = 0.0f;

      for (int i = 0; i <= (octaves - 1); i ++) {
         float frequency = powf(2, i);
         float amplitude = powf(persistence, i);

         total = total + interpolate_noise(x * frequency, y * frequency) * amplitude;
      }

      return total;
   }

}
