#include "main.hpp"
#include "DObject.hpp"
#include "clock_tracking/clock_track.hpp"
#include "color/color_shifting.hpp"
#include "shaders/shaderprog.hpp"
#include "shapes/circle.hpp"
#include "window_control.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include <iostream>

int main() {
  try {
    WindowControl windowControl("Circles", SCR_WIDTH, SCR_WIDTH);
    windowControl.initAndCreateWindow();

    ShaderProg shaderProgram;
    shaderProgram.attach("./src/shaders/vs-first-circle.glsl",
                         GL_VERTEX_SHADER);
    shaderProgram.attach("./src/shaders/fs-first-circle.glsl",
                         GL_FRAGMENT_SHADER);
    shaderProgram.link();

    Circle firstCircle;
    firstCircle.createVecVertices();

    DObject firstCanvasItem;

    firstCanvasItem.bindData(firstCircle.vertices, firstCircle.indices);

    ClockTrack clockTracker;
    clockTracker.poll_fps = true;
    clockTracker.enable_fps_log = true;

    ColorShifting colorShifting(156.0, 0.0, 25.0f);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (windowControl.keepOpen()) {
      clockTracker.clock_cycle();

      windowControl.processInput();

      // render
      // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      shaderProgram.use();
      shaderProgram.setFragmentColor(
          colorShifting.shiftColor(clockTracker.delta_time));
      firstCanvasItem.draw();
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
