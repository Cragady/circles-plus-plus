#ifndef CIRCLE_MATH_H
#define CIRCLE_MATH_H

#include <glm/vec3.hpp>

namespace CircleMath {

  const double PI = 3.14159265358979323846;
  const double TWO_PI = PI * 2;
  glm::vec3 pointOnEdge(float radius, float degree_partial, glm::vec3 center);
  float degreeFromPositioning(glm::vec3 position, glm::vec3 center);
}

#endif
