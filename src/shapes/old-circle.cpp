//THIS IS AN OLD FILE AND WILL BE BROKEN
//
//keeping for legacy's sake on my sanity
//
// while generating vertices, be sure to organize them in counter-clockwise
// ordering
/*
 *
 *     A
 *     | \        y
 *     |  \       a
 *     |   \      x
 *     B----C     x-axis
 *     A -> B -> C
 */

#include "old-circle.hpp"
#include "circle_math.hpp"
#include <iostream>
#include <glm/vec3.hpp>

OldCircle::OldCircle() { radius = 0.025f; }

OldCircle::OldCircle(float t_radius) { radius = t_radius; }

OldCircle::~OldCircle() {};

void OldCircle::createVecVertices() {
  glm::vec3 line_start = CircleMath::pointOnEdge(radius * 2, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
  glm::vec3 base_subtractor = glm::vec3(0.0f, radius, 0.0f);
  int i_four = 0;
  int steps = BUFFER;
  for (int current_step = 0; current_step < steps; current_step++) {
    float degree = (float)current_step / steps * 360;
    glm::vec3 circle_coords =
        CircleMath::pointOnEdge(radius * 2, degree, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 line_end = circle_coords;
    glm::vec3 base_start = line_start - base_subtractor;
    glm::vec3 base_end = line_end - base_subtractor;
    if (i_four >= VEC_BUFFER)
      i_four = VEC_BUFFER - 1;
    vec[i_four] = base_start;
    vec[i_four + 1] = line_start;
    vec[i_four + 2] = line_end;
    vec[i_four + 3] = base_end;
    i_four += 4;
    line_start = line_end;
    createTriangleIndices(current_step);
  }
  createVers();
}

void OldCircle::createVers() {
  std::cout << "start createVers" << std::endl;
  int i_three = 0;
  for (int i = 0; i < VEC_BUFFER; i++) {
    if (i_three >= VER_BUFFER) i_three = VER_BUFFER - 1;
    glm::vec3 vec_value = vec[i];
    vertices[i_three] = vec_value.x;
    vertices[i_three + 1] = vec_value.y;
    vertices[i_three + 2] = vec_value.z;
    i_three += 2;
  }
  std::cout << "end createVers" << std::endl;
}

void OldCircle::createTriangleIndices(int index, int correction) {
  unsigned int i = index * 6;

  // triangle_indices[i] = index - correction;
  triangle_indices[i] = 0;
  triangle_indices[i + 1] = index + 1 - correction;
  triangle_indices[i + 2] = index + 3 - correction;

  // triangle_indices[i + 3] = index + 1 - correction;
  triangle_indices[i + 3] = 0;
  triangle_indices[i + 4] = index + 2 - correction;
  triangle_indices[i + 5] = index + 3 - correction;

}
