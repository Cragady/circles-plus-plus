#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>

double clock_to_ms(clock_t ticks);
void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

// const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

