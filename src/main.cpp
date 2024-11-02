#include "ParallelSinusoids.hpp"
#include "RandomLines.hpp"
#include "SkSurfaceProps.h"
#include "WindowManager.hpp"
#include "spdlog/spdlog.h"
#include <SDL2/SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <SkCanvas.h>
#include <SkColorSpace.h>
#include <SkData.h>
#include <SkImageInfo.h>
#include <SkPath.h>
#include <SkRefCnt.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <tuple>

int main(int argc, char **argv) {
  auto wm_res = WindowManager::initialize();

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    spdlog::error("Error initializing SDL.");
    exit(1);
  }

  if (!wm_res.has_value()) {
    spdlog::error("Error initializing WindowManager: {}", wm_res.error());
    exit(1);
  }

  auto &wm = wm_res->get();

  RandomLines ps{wm.width(), wm.height()};

  bool is_running = true;
  SDL_Event event;
  while (is_running) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        is_running = false;
      }
    }

    auto canvas_res = wm.canvas();
    if (!canvas_res.has_value()) {
      spdlog::error("Unable to get canvas: {}", canvas_res.error());
      exit(1);
    }
    auto &canvas = canvas_res->get();

    canvas.clear(SK_ColorWHITE);

    ps.display(canvas, SDL_GetTicks());

    auto draw_res = wm.draw();
    if (!draw_res.has_value()) {
      spdlog::error("Error drawing window: {}", draw_res.error());
      exit(1);
    };

    ps.update(SDL_GetTicks());

    SDL_Delay(16);
  }

  return 0;
}
