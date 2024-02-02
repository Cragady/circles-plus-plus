#include "circle_math.hpp"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

namespace CircleMath {


  glm::vec3 pointOnEdge(float radius, float degree_partial, glm::vec3 center) {
    float degree = degree_partial * 360.f;
    float radians = glm::radians(degree);

    float x = cos(radians) * radius;
    float y = sin(radians) * radius;

    glm::vec3 position = glm::vec3(x, y, 0.0f) + center;

    return position;
  }

  float degreeFromPositioning(glm::vec3 position, glm::vec3 center) {
    glm::vec3 delta_from = position - center;
    float x_decomp = atan2(delta_from.y, delta_from.x);
    x_decomp *= 180 / PI;

    if (x_decomp < 0) {
      x_decomp += 360;
    }
    return x_decomp;
  }
}
