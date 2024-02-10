#include "main.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shapes/circle.hpp"
#include "shapes/circle_math.hpp"
#include "window_control.hpp"
#include <cstdlib>

#include <iostream>

int main() {
  RawMain rawMain;
  return rawMain.main();
}

RawMain::RawMain() : windowControl("Circles", SCR_WIDTH, SCR_HEIGHT) {

  clockTracker.poll_fps = true;
  clockTracker.enable_fps_log = true;
}

RawMain::~RawMain() {};

void RawMain::fillMembers() {
  const int CIRCLES_NUM = 500;
  circles.resize(CIRCLES_NUM);

  for (int i = 0; i < CIRCLES_NUM; i++) {
    float radians_partial = (float)i / CIRCLES_NUM;
    circles[i] = Circle(CircleMath::pointOnEdge(0.225f, radians_partial, glm::vec3()),
      0.05,
      50
    );

    circles[i].index = i;
    circles[i].outer_total = CIRCLES_NUM;
    circles[i].radians_partial = radians_partial;
    circles[i].initializeMembers();
  }


  // for (int i = 0; i < circles.size(); i++) {
  //   circles[i].initializeMembers();
  // }
}

int RawMain::main() {
  try {
    windowControl.initAndCreateWindow();
    fillMembers();

    while (windowControl.keepOpen()) {
      pushClock();

      windowControl.processInput();

      // render
      /*
       *
       */

      windowControl.clearBuffer();
      renderWindow();

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

void RawMain::renderWindow() {
  for (int i = 0; i < circles.size(); i++) {
    circles[i].shader_program.use();
    circles[i].oscillatePosition(clockTracker.delta_time,
                                 clockTracker.life_delta);
    circles[i].draw(clockTracker.delta_time);
  }
}

void RawMain::pushClock() {
  clockTracker.clock_cycle();
}
