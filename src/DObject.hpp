#ifndef DOBJECT_H
#define DOBJECT_H

#include "shaders/shaderprog.hpp"

#include <glm/vec3.hpp>
#include <vector>

class DObject {

private:
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  unsigned long long indices_size;
  // Vertex Array Objects
  void bindVAO();
  // Vertex Buffer Objects
  void bindVBO(std::vector<float> &vertices);
  // Element Buffer Objects
  void bindEBO(std::vector<unsigned int> &indices);
  void finishBindings();

protected:
  glm::vec3 position;
  void clearBindings();
  void genArraysAndBuffers();

public:
  DObject();
  ~DObject();

  // Disable Copy/Move operations
  // May implement at a later date
  DObject(const DObject&) = delete;
  DObject(DObject&&) = delete;
  DObject& operator=(const DObject&) = delete;
  DObject& operator=(DObject&&) = delete;

  enum DrawMode {
    NOOP = 0,
    NORMAL = 1,
    POLYGON = 2,
    DOTMATRIX = 3,
  };

  DrawMode current_draw_mode;

  ShaderProg shader_program;

  void bindData(std::vector<float> &vertices, std::vector<unsigned int> &indices);
  void draw();
  void setDrawMode();
  void transform(glm::vec3 &new_position);
  void updateShader();

};

#endif
