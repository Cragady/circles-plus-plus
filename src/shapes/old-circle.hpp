#ifndef OLD_CIRCLE_H
#define OLD_CIRCLE_H

#include <glm/vec3.hpp>

class OldCircle {

public:
  // llol, no mem management right now
  // multiple of 4
  static const int BUFFER = 50;
  static const int VEC_BUFFER = BUFFER * 4;
  static const int VER_BUFFER = VEC_BUFFER * 3;
  static const int TRI_BUFFER = BUFFER * 6;

private:
  int steps;
  float radius;
  glm::vec3 vec[VEC_BUFFER];


public:
  OldCircle();
  OldCircle(float t_radius);
  ~OldCircle();

  float vertices[VER_BUFFER];
  unsigned int triangle_indices[VEC_BUFFER];

  void createVecVertices();
  void createVers();
  void createTriangleIndices(int index, int correction = 0);
};

#endif
