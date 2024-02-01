#include "clock_track.hpp"
#include <iostream>

ClockTrack::ClockTrack() {
  old_delta = clock();
  seconds_delta = 0.0f;
  enable_fps_log = false;
  poll_fps = false;
}

ClockTrack::~ClockTrack() {};

void ClockTrack::clock_cycle() {
  clock_t new_delta = clock() - old_delta;
  old_delta = clock();
  float delta_time = (float)new_delta / CLOCKS_PER_SEC;

  log_fps(delta_time, new_delta);
}

void ClockTrack::log_fps(float &delta_time, clock_t &new_delta) {
  if (!poll_fps) return;
  seconds_delta += delta_time;
  if (seconds_delta < 1.0f) return;

  seconds_delta -= 1.0f;
  double frame_rate = CLOCKS_PER_SEC / delta_time;
  if (!enable_fps_log) return;
  std::cout << "FPS: " << frame_rate << std::endl;
  std::cout << "clock is at: " << new_delta << " | delta is at: " << delta_time << " | and Clocks/s: " << CLOCKS_PER_SEC << std::endl;
}
