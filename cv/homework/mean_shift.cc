#include "mean_shift.h"

#include <cmath>
#include <iostream>

namespace Homework
{

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define POSITION(y, x, w, c) (((y) * (w) + (x)) * (c))

void MeanShift(unsigned char* value, unsigned char* output, size_t height,
               size_t width, int sw, double th, size_t channel,
               size_t max_iter) {
  th = th * th;
  int c, x0, x1, y0, y1;

  int* cvals = new int[channel];
  long* csums = new long[channel];

  size_t step = width * channel;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      x0 = x;
      y0 = y;

      size_t n_iter = 0;
      size_t count, x_sum, y_sum, distance;
      size_t miny = MAX(y0 - sw, 0), maxy = MIN(y0 + sw, height);
      size_t minx = MAX(x0 - sw, 0), maxx = MIN(x0 + sw, width);

      for (c = 0; c < channel; c++) {
        cvals[c] = value[POSITION(y, x, width, channel) + c];
      }

      while (n_iter < max_iter) {
        count = 0;
        x_sum = 0;
        y_sum = 0;

        for (c = 0; c < channel; c++) {
          csums[c] = 0;
        }

        for (size_t yi = miny; yi < maxy; ++yi) {
          for (size_t xi = minx; xi < maxx; ++xi) {
            distance = 0;
            for (c = 0; c < channel; c++) {
              int d = (int)cvals[c] -
                      (int)value[POSITION(yi, xi, width, channel) + c];
              distance += d * d;
            }

            if (distance <= th) {
              count++;
              x_sum += xi;
              y_sum += yi;
              for (c = 0; c < channel; c++) {
                csums[c] += value[POSITION(yi, xi, width, channel) + c];
              }
            }
          }
        }  // calculate the window done.

        if (count == 0) break;

        double count_inv = 1.0 / count;
        x1 = (int)(x_sum * count_inv);
        y1 = (int)(y_sum * count_inv);
        distance = 0;
        for (c = 0; c < channel; c++) {
          csums[c] = (long)(csums[c] * count_inv);
          distance += (csums[c] - cvals[c]) * (csums[c] - cvals[c]);
          cvals[c] = csums[c];
        }

        bool same_position = (x1 == x0 && y0 == y1);
        x0 = x1, y0 = y1;

        // stop when distance equal 0
        if (same_position || distance == 0) {
          break;
        }

        ++n_iter;
      }

      for (c = 0; c < channel; c++) {
        output[POSITION(y, x, width, channel) + c] = cvals[c];
      }
    }
  }

  delete[] cvals;
  delete[] csums;
}

}  // namespace Homework
