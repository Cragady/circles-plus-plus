#include "main.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shaders/shaderprog.hpp"
#include "shapes/circle.hpp"
#include "window_control.hpp"
#include <cstdlib>

#include <iostream>

int main() {
  try {
    WindowControl windowControl("Circles", SCR_WIDTH, SCR_WIDTH);
    windowControl.initAndCreateWindow();

    Circle firstCircle;
    firstCircle.initializeMembers();

    ClockTrack clockTracker;
    clockTracker.poll_fps = true;
    clockTracker.enable_fps_log = true;

    ColorShifting colorShifting(156.0, 0.0, 25.0f);

    while (windowControl.keepOpen()) {
      clockTracker.clock_cycle();

      windowControl.processInput();

      // render
      /*
       *
       */

      glm::vec3 movement = glm::vec3(-1, 0, 0) * clockTracker.delta_time;

      windowControl.clearBuffer();
      firstCircle.shader_program.use();
      firstCircle.shader_program.setFragmentColor(
          colorShifting.shiftColor(clockTracker.delta_time));
      firstCircle.transform(movement);
      firstCircle.draw();

      /*
       *
       */
      // end render

      windowControl.swapAndPoll();
    }

    windowControl.terminate();

  } catch (const char *e) {
    std::cout << "Program terminated with error: \n" << e << std::endl;
    std::cout << EXIT_FAILURE << std::endl;
    return EXIT_FAILURE;
  } catch (const std::exception &e) {
    std::cout << "Program terminated with error: \n" << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
