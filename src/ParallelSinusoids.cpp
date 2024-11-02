#include "ParallelSinusoids.hpp"
#include "SkColor.h"
#include "SkMatrix.h"
#include "SkPath.h"
#include "private/base/SkPoint_impl.h"

void ParallelSinusoids::display(SkCanvas &canvas, uint32_t ticks) {
  canvas.drawColor(SK_ColorBLACK);

  SkPath path{};

  path.moveTo(-m_width, 0);

  for (auto x = -m_width; x < m_width * 2; x += 1) {
    auto y = std::cos(.00005 * (x * x) + (ticks / 1000.)) * 32;

    path.lineTo(x, y);
  }

  SkPaint paint{};

  paint.setColor(SK_ColorWHITE);
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setAntiAlias(true);

  auto spacing = m_height / s_num_sinusoids;

  for (auto i = 0; i < m_height; i += spacing) {
    canvas.drawPath(path, paint);
    path.offset(0, spacing);
  }
}
