#ifndef CLOCKTRACK_H
#define CLOCKTRACK_H

#include <ctime>

class ClockTrack {
private:
  clock_t old_delta;
  float seconds_delta;

public:
  ClockTrack();
  ~ClockTrack();

  bool enable_fps_log;
  bool poll_fps;
  void clock_cycle();
  void log_fps(float &delta_time, clock_t &new_delta);

};

#endif
