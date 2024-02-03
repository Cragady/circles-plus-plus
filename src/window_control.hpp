#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <string>

class WindowControl {

public:
  WindowControl(std::string t_window_name, int t_width, int t_height);
  ~WindowControl();

  std::string window_name;
  int width;
  int height;

  GLFWwindow *window;

  void initAndCreateWindow();
  static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
  void processInput();
  bool keepOpen();
  void swapAndPoll();
  void terminate();
  void clearBuffer();

};

#endif
