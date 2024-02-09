#include "DObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

DObject::DObject() {
  // genArraysAndBuffers();
  current_draw_mode = DrawMode::NOOP;
  position = glm::vec3();
}

DObject::~DObject() {
  clearBindings();
}

DObject::DObject(const DObject &other)
    : VBO(other.VBO ? other.VBO : (unsigned)int()),
      VAO(other.VAO ? other.VAO : (unsigned)int()),
      EBO(other.EBO ? other.EBO : (unsigned)int()) {
}

DObject::DObject(DObject &&other) noexcept : DObject() {
  swap(*this, other);
}

DObject &DObject::operator=(DObject &other) {
  swap(*this, other);
  return *this;
}

DObject &DObject::operator=(DObject &&other) {
  swap(*this, other);
  return *this;
}

void swap(DObject &first, DObject &second) {
  using std::swap;
  swap(first.VBO, second.VBO);
  swap(first.VAO, second.VAO);
  swap(first.EBO, second.EBO);
  swap(first.shader_program, second.shader_program);
  swap(first.current_draw_mode, second.current_draw_mode);
  swap(first.position, second.position);
  swap(first.indices_size, second.indices_size);
}

void DObject::bindData(std::vector<float> &vertices,
                       std::vector<unsigned int> &indices) {
  bindVAO();
  bindVBO(vertices);
  bindEBO(indices);
  finishBindings();
}

void DObject::bindVAO() {
  glBindVertexArray(VAO);
}

void DObject::bindVBO(std::vector<float> &vertices) {
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0],
               GL_STREAM_DRAW);
}

void DObject::bindEBO(std::vector<unsigned int> &indices) {
  indices_size = indices.size();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_size,
               &indices[0], GL_STREAM_DRAW);
}

void DObject::finishBindings() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DObject::draw() {
  bindVAO();
  setDrawMode();
  glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
}

void DObject::setDrawMode() {
  // This may draw every object like this lol
  // consider moving this to the window class
  // if that is the behavior
  if (current_draw_mode == DrawMode::NOOP)
    return;
  if (current_draw_mode == DrawMode::NORMAL) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  if (current_draw_mode == DrawMode::POLYGON) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (current_draw_mode == DrawMode::DOTMATRIX) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }
  current_draw_mode = DrawMode::NOOP;
}

void DObject::clearBindings() {
  // if (VAO && VAO != GL_INVALID_VALUE) // ??
  if (VAO)
    glDeleteVertexArrays(1, &VAO);
  if (VBO)
    glDeleteBuffers(1, &VBO);
  if (EBO)
    glDeleteBuffers(1, &EBO);
}

void DObject::genArraysAndBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  GL_INVALID_VALUE;
}

void DObject::transform(glm::vec3 &position_delta) {

  position += position_delta;

  delta_transform(position_delta);
}

void DObject::delta_transform(glm::vec3 &position_delta) {

  GLuint transformLoc =
      glGetUniformLocation(shader_program.getID(), "transform");

  if (transformLoc < 0)
    return;

  glm::mat4 transform = glm::mat4(1.0f);

  transform = glm::translate(transform, position);
  // glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void DObject::setPosition(glm::vec3 &new_position) {
  glm::vec3 zero_delta = glm::vec3();
  position = new_position;

  delta_transform(zero_delta);
}
