#include "main.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shapes/circle.hpp"
#include "shapes/circle_math.hpp"
#include "window_control.hpp"
#include <cstdlib>

#include <iostream>

int main() {
  try {
    WindowControl windowControl("Circles", SCR_WIDTH, SCR_WIDTH);
    windowControl.initAndCreateWindow();

    // std::vector<Circle> circles;
    // circles.push_back(Circle(CircleMath::pointOnEdge(0.15f, 0.0f, glm::vec3()), 0.05, 50));
    // circles[0].initializeMembers();

    // Circle testCircle(CircleMath::pointOnEdge(0.15f, 0.0f, glm::vec3()), 0.05, 50);
    // testCircle.initializeMembers();

    // circles.push_back(testCircle);

    Circle firstCircle(CircleMath::pointOnEdge(0.15f, 0.0f, glm::vec3()), 0.05, 50);
    firstCircle.initializeMembers();

    // Circle secondCircle(CircleMath::pointOnEdge(0.15f, 0.5f, glm::vec3()), 0.05, 50);
    // secondCircle.initializeMembers();

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
      // circles[0].shader_program.use();
      // circles[0].shader_program.setFragmentColor(
      //     colorShifting.shiftColor(clockTracker.delta_time));
      // // circles[0].oscillatePosition(clockTracker.delta_time);
      // circles[0].oscillatePosition(clockTracker.delta_time);
      // circles[0].draw();

      firstCircle.shader_program.use();
      firstCircle.shader_program.setFragmentColor(
          colorShifting.shiftColor(clockTracker.delta_time));
      // firstCircle.oscillatePosition(clockTracker.delta_time);
      firstCircle.oscillatePosition(clockTracker.delta_time);
      firstCircle.draw();


      // secondCircle.shader_program.use();
      // secondCircle.shader_program.setFragmentColor(
      //     colorShifting.shiftColor(clockTracker.delta_time));
      // secondCircle.oscillatePosition(clockTracker.delta_time);
      // secondCircle.draw();

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
