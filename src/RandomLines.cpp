#include "RandomLines.hpp"
#include <SkPath.h>
#include <cstdlib>
#include <random>
#include <ranges>
#include <boost/range/combine.hpp>

void RandomLines::display(SkCanvas &canvas, uint32_t ticks) {
  SkPath path{};

  canvas.drawColor(SK_ColorBLACK);

  path.moveTo(m_current_points[0]);

  SkPaint paint{};

  paint.setColor(SK_ColorRED);
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setAntiAlias(true);

  for (auto &point : m_next_points) {
    canvas.drawCircle(point, 2, paint);
  }

  paint.setColor(SK_ColorWHITE);
  
  for (int i = 1; i < s_num_points; i++) {
    path.lineTo(m_current_points[i]);
  }


  canvas.drawPath(path, paint);
}

void RandomLines::update(uint32_t ticks) {
  if (ticks >= m_last_major_tick + s_ticks_to_next) {
    m_current_points = m_next_points;
    m_start_points = m_next_points;
    m_last_major_tick = ticks;
    m_last_minor_tick = ticks;
    generate_points(m_next_points);
  } else {
    auto interpolate_by = (ticks - m_last_major_tick) / (float)s_ticks_to_next;
    m_last_minor_tick = ticks;

    for (auto [start, current, next] : boost::combine(m_start_points, m_current_points, m_next_points)) {
      auto x_dist = next.x() - start.x();
      auto y_dist = next.y() - start.y();

      current.set(
        start.x() + x_dist * interpolate_by,
        start.y() + y_dist * interpolate_by
      );
    }
  }
}
