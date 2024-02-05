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
#include <glm/glm.hpp>
#include <iostream>

Circle::Circle() : Circle(0.25f, 50) {}

Circle::Circle(float t_radius, float t_steps)
    : Circle(glm::vec3(), t_radius, t_steps) {}

Circle::Circle(glm::vec3 t_position, float t_radius, float t_steps) {
  radius = t_radius;
  steps = t_steps;
  radians = CircleMath::degreeFromPositioning(t_position, glm::vec3());
  DObject::shader_program.setVSandFSLocations(
    "./src/shaders/vs-first-circle.glsl",
    "./src/shaders/fs-first-circle.glsl"
  );
  DObject::shader_program.link();
  DObject::shader_program.use();
  DObject::setPosition(t_position);
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
    glm::vec3 *vec_value = &vec[i];
    vertices.push_back(vec_value->x);
    vertices.push_back(vec_value->y);
    vertices.push_back(vec_value->z);
  }
}

void Circle::createTriangleIndices(int index) {
  if (index >= steps - 2) return;
  indices.push_back(0);
  indices.push_back(index + 1);
  indices.push_back(index + 2);
}

void Circle::initializeMembers() {
  createVecVertices();
  DObject::bindData(vertices, indices);
}

void Circle::oscillatePosition(float delta_time, float life_delta) {
  double twoPi = CircleMath::TWO_PI;
  float radians = twoPi;
  float tmp_angle = 2.0f / 5.0f * twoPi;
  // float x = 0.5f * cos(radians * position.x * life_delta);
  float x = 0.5f * cos(radians * life_delta) * cos(tmp_angle * position.x);
  float y = 0.5f * sin(x);
  // float x = 0.5f * sin(radians * position.y - radians * life_delta);
  // float y = 0.5f * sin(radians * position.x - radians * life_delta);
  glm::vec3 new_position = glm::vec3(x, y, 0);
  setPosition(new_position);
}
