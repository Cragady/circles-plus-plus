#include "window_control.hpp"
#include "shapes/circle.hpp"
#include "clock_tracking/clock_track.hpp"

#include <vector>

// const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

class RawMain {
private:
  std::vector<Circle> circles;
  ClockTrack clockTracker;

public:
  RawMain();
  ~RawMain();

  WindowControl windowControl;

  void fillMembers();
  int main();
  void renderWindow();
  void pushClock();
};
