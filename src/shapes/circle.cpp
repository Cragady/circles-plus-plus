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

Circle::Circle() : Circle(0.25f, 50) {
}

Circle::Circle(float t_radius, float t_steps)
    : Circle(glm::vec3(), t_radius, t_steps) {
}

Circle::Circle(glm::vec3 t_position, float t_radius, float t_steps) {
  radius = t_radius;
  steps = t_steps;
  radians = CircleMath::degreeFromPositioning(t_position, glm::vec3());
  index = 0;
  outer_total = -1;
  radians_partial = 0;
  ColorShifting tmp(156.0, 0.0f, 100.0f);
  color_shifting = tmp;
  DObject::shader_program.setVSandFSLocations(
    "./src/shaders/vs-first-circle.glsl",
    "./src/shaders/fs-first-circle.glsl"
  );
  DObject::shader_program.link();
  DObject::shader_program.use();
  DObject::position = t_position;
}

Circle::~Circle(){};

Circle::Circle(const Circle &other) {
};

Circle::Circle(Circle &&other) noexcept
    : Circle() {
  swap(*this, other);
}

Circle &Circle::operator=(Circle &other) {
  swap(*this, other);
  this->setPosition(this->position);
  return *this;
}

Circle &Circle::operator=(Circle &&other) {
  swap(*this, other);
  this->setPosition(this->position);
  return *this;
}

void swap(Circle &first, Circle &second) {
  using std::swap;
  swap(first.vec, second.vec);
  swap(first.vertices, second.vertices);
  swap(first.indices, second.indices);
  swap(first.radius, second.radius);
  swap(first.steps, second.steps);
  swap(first.index, second.index);
  swap(first.position, second.position);
  swap(first.radians_partial, second.radians_partial);
  swap(first.color_shifting, second.color_shifting);
  swap(first.outer_total, second.outer_total);
}

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
  DObject::genArraysAndBuffers();
  createVecVertices();
  DObject::bindData(vertices, indices);
  DObject::shader_program.use();
  DObject::setPosition(position);
  color_shifting.shiftColor((float)index / outer_total);
}

void Circle::oscillatePosition(float delta_time, float life_delta) {
  float radians = radians_partial * CircleMath::TWO_PI / 2;

  float x = 0.9 * cos(radians) * cos(radians * 3 + life_delta);
  float y = 0.9 * sin(radians) * cos(radians * 3 + life_delta);

  glm::vec3 new_position = glm::vec3(x, y, 0);
  setPosition(new_position);
}

void Circle::draw(float delta_time) {
  DObject::shader_program.setFragmentColor(
      color_shifting.shiftColor(delta_time)
  );
  DObject::draw();
}
