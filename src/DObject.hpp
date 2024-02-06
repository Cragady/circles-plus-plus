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
  void delta_transform(glm::vec3 &position_delta);

protected:
  glm::vec3 position;
  void clearBindings();

public:
  DObject();
  ~DObject();

  // Disable Copy/Move operations
  // May implement at a later date
  DObject(const DObject&) = delete;
  DObject& operator=(const DObject&) = delete;
  // DObject(DObject&&) = delete;
  // DObject& operator=(DObject&&) = delete;

  // copy
  // DObject(DObject const &other);
  // DObject& operator=(DObject const &other);
  // DObject& operator=(DObject other);
  // move
  DObject(DObject &&other);
  DObject& operator=(DObject &&other) noexcept;

  enum DrawMode {
    NOOP = 0,
    NORMAL = 1,
    POLYGON = 2,
    DOTMATRIX = 3,
  };

  DrawMode current_draw_mode;

  ShaderProg shader_program;

  void genArraysAndBuffers();
  void bindData(std::vector<float> &vertices, std::vector<unsigned int> &indices);
  void draw();
  void setDrawMode();
  void updateShader();
  void transform(glm::vec3 &position_delta);
  void setPosition(glm::vec3 &new_position);
  friend void swap(DObject &first, DObject &second);

};

void swap(DObject &first, DObject &second);

#endif
