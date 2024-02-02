#include "color_shifting.hpp"

ColorShifting::ColorShifting() {
  shift_speed = 10.0f;
  color_high = COLOR_MAX;
  color_low = COLOR_LOWEST;
  colors = glm::vec3(color_high, color_low, color_low);
  current_index = 0;
  next_index = colors.length() - 1;
}

ColorShifting::ColorShifting(float t_color_high, float t_color_low, float t_speed) {
  shift_speed = t_speed;
  color_high = t_color_high <= COLOR_MAX ? t_color_high : COLOR_MAX;
  color_low = t_color_low >= COLOR_LOWEST ? t_color_low : COLOR_LOWEST;

  if (color_low >= color_high)
    color_low = COLOR_LOWEST;
  if (color_high <= color_low)
    color_high = COLOR_MAX;

  colors = glm::vec3(color_high, color_low, color_low);
  current_index = 0;
  next_index = colors.length() - 1;
}

ColorShifting::~ColorShifting() {};

glm::vec3 ColorShifting::shiftColor(float delta_time) {
  float delta_color = shift_speed * delta_time;

  float *current_color = &colors[current_index];
  float *next_color = &colors[next_index];

  if (*current_color <= *next_color) {
    *current_color -= delta_color;
  }

  if (*current_color <= color_low) {
    *current_color = color_low;
  }

  if (*current_color < color_high && *next_color < color_high) {
    *current_color += delta_color;
  }

  if (*current_color >= color_high) {
    *current_color = color_high;
  }

  if (*current_color == color_high) {
    *next_color += delta_color;
  }

  if (*next_color >= color_high) {
    *next_color = color_high;
  }

  if (*next_color == color_high && *current_color == color_low) {
    current_index--;
    if (current_index < 0) current_index = colors.length() - 1;
    next_index--;
    if (next_index < 0) next_index = colors.length() - 1;
  }

  return colors / COLOR_DIVISOR;
}
