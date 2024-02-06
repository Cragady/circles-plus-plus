#ifndef CIRCLE_H
#define CIRCLE_H

#include "../DObject.hpp"
#include "../color/color_shifting.hpp"
#include <glm/vec3.hpp>
#include <vector>

class Circle : public DObject {

private:
  std::vector<glm::vec3> vec;
  float radians;


public:
  Circle();
  Circle(float t_radius, float t_steps = 50);
  Circle(glm::vec3 t_position, float t_radius, float t_steps = 50);
  ~Circle();

  Circle(const Circle&) = delete;
  Circle& operator=(const Circle&) = delete;
  Circle(Circle &&other);
  Circle& operator=(Circle &&other) noexcept;

  unsigned int steps;
  float radius;
  int index;
  float radians_partial;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  ColorShifting color_shifting;
  int outer_total;

  void createVecVertices();
  void createVers();
  void createTriangleIndices(int index);
  void initializeMembers();
  void oscillatePosition(float delta_time, float life_delta);
  void draw(float delta_time);
  friend void swap(Circle &first, Circle &second);
};
void swap(Circle &first, Circle &second);

#endif

