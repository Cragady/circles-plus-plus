#include "DObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DObject::DObject() {
  genArraysAndBuffers();
  current_draw_mode = DrawMode::NOOP;
  position = glm::vec3();
}

DObject::~DObject() {
  clearBindings();
}

void DObject::bindData(std::vector<float> &vertices,
                       std::vector<unsigned int> &indices) {
  bindVAO();
  bindVBO(vertices);
  bindEBO(indices);
  finishBindings();
}

void DObject::bindVAO() { glBindVertexArray(VAO); }

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
  // maybe re-think this, probably use enum and only call
  // glPolygonMode once per change instead of every draw
  if (current_draw_mode == DrawMode::NOOP) return;
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
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void DObject::genArraysAndBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

void DObject::transform(glm::vec3 &new_position){

  position += new_position;

  GLuint transformLoc = glGetUniformLocation(shader_program.getID(), "transform");

  if (transformLoc < 0) return;

  glm::mat4 transform = glm::mat4(1.0f);

  transform = glm::translate(transform, position);
  // glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}
