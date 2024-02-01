#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ctime>

int main();
double clock_to_ms(clock_t ticks);
void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
void render_new();

