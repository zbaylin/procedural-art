#pragma once

#include "View.hpp"

class ParallelSinusoids : View {
public:
  ParallelSinusoids(int width, int height) : m_width(width), m_height(height) {}
  void display(SkCanvas &canvas, uint32_t ticks) override;

private:
  const int m_width;
  const int m_height;
  static const inline int s_num_sinusoids = 40;
};
