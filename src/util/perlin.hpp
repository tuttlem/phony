
#ifndef __phony_perlin_hpp_

#define __phony_perlin_hpp_

namespace phony {
   /* perlin noise implementation */
   class perlin {
      private:
         static float noise(const int x, const int y);
         static float smooth_noise(const float x, const float y);
         static float lerp(float a, float b, float x);
         static float terp(float a, float b, float x);
         static float interpolate_noise(const float x, const float y);

      public:
         static float perlin_2d(const float x, const float y,
               const int octaves = 6, const float persistence = 0.95f);

   };

   inline float perlin::noise(const int x, const int y) {
      int n = x + y * 57;
      n = (n << 13) ^ n;
      return (1.0f - ( ( n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0f);
   }

   inline float perlin::smooth_noise(const float x, const float y) {
      int ix = (int)x;
      int iy = (int)y;

      float corners = (noise(ix - 1, iy - 1) +
            noise(ix + 1, iy - 1) +
            noise(ix - 1, iy + 1) +
            noise(ix + 1, iy + 1)) / 16;

      float sides = (noise(ix - 1, iy) +
            noise(ix + 1, iy) +
            noise(ix, iy - 1) +
            noise(ix, iy + 1)) / 8;

      float centre = noise(ix, iy);

      return corners + sides + centre;
   }

   inline float perlin::lerp(float a, float b, float x) {
      return a * (1 - x) + b * x;
   }

   inline float perlin::interpolate_noise(const float x, const float y) {
      int   ix = (int)x;
      float fx = x - ix;

      int   iy = (int)y;
      float fy = y - iy;

      float v1 = smooth_noise(ix, iy),
            v2 = smooth_noise(ix + 1, iy),
            v3 = smooth_noise(ix, iy + 1),
            v4 = smooth_noise(ix + 1, iy + 1);

      float i1 = terp(v1, v2, fx),
            i2 = terp(v3, v4, fx);

      return terp(i1, i2, fy);
   }

}

#endif //__phony_perlin_hpp_
