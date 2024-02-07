#include "main.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shapes/circle.hpp"
#include "shapes/circle_math.hpp"
#include "window_control.hpp"
#include <cstdlib>

#include <iostream>

namespace RawMain {

const int CIRCLES_NUM = 12;

int main() {
  try {
    WindowControl windowControl("Circles", SCR_WIDTH, SCR_WIDTH);
    windowControl.initAndCreateWindow();

    std::vector<Circle> circles(CIRCLES_NUM);
    for (int i = 0; i < CIRCLES_NUM; i++) {
      float radians_partial = (float)i / CIRCLES_NUM;
      Circle tmp(CircleMath::pointOnEdge(0.225f, radians_partial, glm::vec3()), 0.05, 50);
      tmp.index = i;
      tmp.outer_total = CIRCLES_NUM;
      tmp.radians_partial = radians_partial;
      circles[i] = std::move(tmp);
    }

    for (int i = 0; i < circles.size(); i++) {
      circles[i].initializeMembers();
    }
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

      windowControl.clearBuffer();
      for (int i = 0; i < CIRCLES_NUM; i++) {
        circles[i].shader_program.use();
        circles[i].oscillatePosition(clockTracker.delta_time, clockTracker.life_delta);
        circles[i].draw(clockTracker.delta_time);
      }

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

}

int main() {
  return RawMain::main();
}
