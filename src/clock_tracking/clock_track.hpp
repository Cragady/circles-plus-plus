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
  float delta_time;
  void clock_cycle();
  void log_fps(clock_t &new_delta);

};

#endif
