#pragma once

#include "SkCanvas.h"

class View {
public:
  virtual void display(SkCanvas &canvas, uint32_t ticks) { };
  virtual void update(uint32_t ticks) { };
};
