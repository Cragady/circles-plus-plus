#ifndef COLORSHIFTING_H
#define COLORSHIFTING_H

#include <glm/vec3.hpp>

class ColorShifting {

private:
  const float COLOR_MAX = 255.0f;
  const float COLOR_LOWEST = 0.0f;
  const glm::vec3 COLOR_DIVISOR = glm::vec3(COLOR_MAX, COLOR_MAX, COLOR_MAX);
  glm::vec3 colors;
  int current_index;
  int next_index;

public:
  ColorShifting();
  ColorShifting(float t_color_high, float t_color_low, float t_speed);
  ~ColorShifting();
  // ColorShifting(ColorShifting const &other);
  ColorShifting(ColorShifting &other);
  // ColorShifting& operator=(ColorShifting &other);
  ColorShifting &operator=(ColorShifting other);

  ColorShifting(ColorShifting &&other);

  glm::vec3 shiftColor(float delta_time);

  float color_high;
  float color_low;
  float shift_speed;
  friend void swap(ColorShifting &first, ColorShifting &other);
};

void swap(ColorShifting &first, ColorShifting &other);

#endif
