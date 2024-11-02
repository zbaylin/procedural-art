#pragma once

#include "View.hpp"
#include <_types/_uint32_t.h>
#include <array>
#include <iostream>
#include <random>

class RandomLines : View {
public:
  RandomLines(int width, int height)
      : m_width(width), m_height(height),
        m_max_increment_len(sqrt(width * width + height * height)) {
    generate_points(m_start_points);
    m_current_points = m_start_points;
    generate_points(m_next_points);
  }

  void display(SkCanvas &canvas, uint32_t ticks) override;
  void update(uint32_t ticks) override;

private:
  static const int s_num_points = 16;

  void generate_points(std::array<SkPoint, s_num_points> &points) {
    for (auto &point : points) {
      point.set(m_width_distr(m_generator), m_height_distr(m_generator));
    }
  }

  const int m_width;
  const int m_height;
  const int m_max_increment_len;
  uint32_t m_last_minor_tick = 0;
  uint32_t m_last_major_tick = 0;
  std::uniform_int_distribution<> m_width_distr{0, m_width};
  std::uniform_int_distribution<> m_height_distr{0, m_height};
  std::mt19937 m_generator{std::random_device()()};
  static const int s_ticks_to_next = 5000;
  std::array<SkPoint, s_num_points> m_current_points{};
  std::array<SkPoint, s_num_points> m_next_points{};
  std::array<SkPoint, s_num_points> m_start_points{};
};
