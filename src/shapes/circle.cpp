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

#include "circle.hpp"
#include "circle_math.hpp"
#include <iostream>

Circle::Circle() {
  radius = 0.25f;
  steps = 50;
}

Circle::Circle(float t_radius, float t_steps) {
  radius = t_radius;
  steps = t_steps;
}

Circle::~Circle(){};

void Circle::createVecVertices() {
  for (int current_step = 0; current_step < steps; current_step++) {
    float degree_partial = (float)current_step / steps;
    glm::vec3 circle_coords =
        CircleMath::pointOnEdge(radius, degree_partial, glm::vec3());
    vec.push_back(circle_coords);
    createTriangleIndices(current_step);
  }
  createVers();
}

void Circle::createVers() {
  for (int i = 0; i < steps; i++) {
    glm::vec3 vec_value = vec[i];
    vertices.push_back(vec_value.x);
    vertices.push_back(vec_value.y);
    vertices.push_back(vec_value.z);
  }
}

void Circle::createTriangleIndices(int index, int correction) {
  indices.push_back(0);
  indices.push_back(index + 1 - correction);
  indices.push_back(index + 3 - correction);
}
