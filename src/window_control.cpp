#include "window_control.hpp"

WindowControl::WindowControl(std::string t_window_name, int t_width,
                             int t_height) {
  window_name = t_window_name + '\0';
  width = t_width;
  height = t_height;
}

WindowControl::~WindowControl() {}

void WindowControl::initAndCreateWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window =
      glfwCreateWindow(width, height, &window_name[0], NULL, NULL);

  if (window == NULL) {
    glfwTerminate();
    throw "Failed to create GLFW window";
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw "Failed to initialize GLAD";
  }
}

void WindowControl::frameBufferSizeCallback(GLFWwindow *window, int width,
                                            int height) {
  glViewport(0, 0, width, height);
}

void WindowControl::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

bool WindowControl::keepOpen() { return !glfwWindowShouldClose(window); }

void WindowControl::swapAndPoll() {
  // may want to split this eventually
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void WindowControl::terminate() { glfwTerminate(); }

void WindowControl::clearBuffer() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
