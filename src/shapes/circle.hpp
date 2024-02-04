#ifndef CIRCLE_H
#define CIRCLE_H

#include "../DObject.hpp"
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

  unsigned int steps;
  float radius;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  void createVecVertices();
  void createVers();
  void createTriangleIndices(int index);
  void initializeMembers();
  void oscillatePosition(float delta_time);
};

#endif

