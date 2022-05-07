#pragma once

#include <cstdlib>

#include "definitions.h"

template<typename... Args>
std::string FormatString(const char *fmt, Args... args)
{
  const size_t n = snprintf(nullptr, 0, fmt, args...);
  std::vector<char> buf(n+1);
  snprintf(buf.data(), n+1, fmt, args...);
  return std::string(buf.data());
}

// To find next point
vector<Point> BresenhamLine(int x1, int y1, int x2, int y2)
{
  vector<Point> Result;

  int delta_x(x2 - x1);
  // if x1 == x2, then it does not matter what we set here
  signed char const ix((delta_x > 0) - (delta_x < 0));
  delta_x = std::abs(delta_x) << 1;

  int delta_y(y2 - y1);
  // if y1 == y2, then it does not matter what we set here
  signed char const iy((delta_y > 0) - (delta_y < 0));
  delta_y = std::abs(delta_y) << 1;

  if (delta_x >= delta_y)
    {
      // error may go below zero
      int error(delta_y - (delta_x >> 1));

      while (x1 != x2)
        {
          // reduce error, while taking into account the corner case of error == 0
          if ((error > 0) || (!error && (ix > 0)))
            {
              error -= delta_x;
              y1 += iy;
            }
          // else do nothing

          error += delta_y;
          x1 += ix;

          Result.push_back(Point { x1, y1 });
        }
    }
  else
    {
      // error may go below zero
      int error(delta_x - (delta_y >> 1));

      while (y1 != y2)
        {
          // reduce error, while taking into account the corner case of error == 0
          if ((error > 0) || (!error && (iy > 0)))
            {
              error -= delta_y;
              x1 += ix;
            }
          // else do nothing

          error += delta_x;
          y1 += iy;

          Result.push_back(Point { x1, y1 });
        }
    }

  return Result;
}
