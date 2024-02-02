#include "main.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shaders/shaderprog.hpp"
#include "shapes/circle.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>
// #include <cmath>

#include <iostream>

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Circles", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  ShaderProg shaderProgram;
  //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  shaderProgram.attach("./src/shaders/vs-first-circle.glsl", GL_VERTEX_SHADER);
  shaderProgram.attach("./src/shaders/fs-first-circle.glsl", GL_FRAGMENT_SHADER);
  shaderProgram.link();

  Circle firstCircle;
  firstCircle.createVecVertices();


  unsigned int VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * firstCircle.vertices.size(), &firstCircle.vertices[0], GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * firstCircle.indices.size(), &firstCircle.indices[0], GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  ClockTrack clockTracker;
  clockTracker.poll_fps = true;
  clockTracker.enable_fps_log = true;

  ColorShifting colorShifting(156.0, 0.0, 25.0f);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while(!glfwWindowShouldClose(window)) {
    clockTracker.clock_cycle();

    process_input(window);


    // render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.use();
    shaderProgram.setFragmentColor(colorShifting.shiftColor(clockTracker.delta_time));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, firstCircle.indices.size(), GL_UNSIGNED_INT, 0);

    // end render

    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();

  return 0;
}

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
