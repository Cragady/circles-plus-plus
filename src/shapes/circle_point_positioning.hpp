#ifndef CIRCLE_POINT_POSITIONING_H
#define CIRCLE_POINT_POSITIONING_H

#include "../math/vector3.hpp"

struct CirclePointPositioning {
  Vector3 Position;
  float Degree;
  float Radians;

  inline CirclePointPositioning(const Vector3 pos, const float deg, const float rad) {
    Position = pos;
    Degree = deg;
    Radians = rad;
  }
};

#endif
