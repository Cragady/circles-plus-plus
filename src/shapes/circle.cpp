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
  DObject::position = t_position;
  DObject::transform(DObject::position);
}

Circle::~Circle(){};

void Circle::createVecVertices() {
  for (int current_step = 0; current_step < steps; current_step++) {
    float degree_partial = (float)current_step / steps;
    glm::vec3 circle_coords =
        CircleMath::pointOnEdge(radius, degree_partial, DObject::position);
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

void Circle::oscillatePosition(float delta_time) {
  float lambda = 1.0f;
  float twoPi = 2 * CircleMath::PI;
  float K = twoPi / lambda;
  float x = 0.15f * cos(K * position.y - twoPi * delta_time);
  float y = 0.15f * sin(K * position.x - twoPi * delta_time);
  std::cout << "\nx: " << position.x
    << "\ny: " << position.y << std::endl;
  glm::vec3 new_position = glm::vec3(x, y, 0);
  // transform(new_position);
  setPosition(new_position);
}

// void Circle::oscillatePosition(float delta_time) {
//   float degrees = CircleMath::degreeFromPositioning(position, glm::vec3());
//   degrees /= 3;
//   radian_delta += 0.01;
//   if ((int)radian_delta % 360 == 0) radian_delta = 0.0f;
//   // 6.28319 | 0.0174533
//   float radians = glm::radians(degrees);
//   float test = cos(radians * radian_delta);
//   float x = cos(radians - radian_delta) * delta_time * test;
//   float y = sin(radians) * delta_time;
//   glm::vec3 new_position = glm::vec3(x, y, 0);
//   transform(new_position);
// }
