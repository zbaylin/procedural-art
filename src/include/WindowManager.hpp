#pragma once

#include "Error.hpp"
#include "Result.hpp"
#include "SDLUtils.hpp"
#include "SkCanvas.h"
#include "spdlog/spdlog.h"
#include <SDL2/SDL.h>
#include <expected>
#include <memory>

namespace err {
struct NotInitialized : Error {
  NotInitialized(std::string str) : Error(str) {};
  NotInitialized() = default;
};
struct InitializationFailure : Error {};
} // namespace err

class WindowManager {
public:
  static ResultRef<WindowManager, err::NotInitialized> get() {
    if (s_instance == nullptr) {
      throw err::NotInitialized("s_instance");
    }

    return *s_instance;
  }

  static ResultRef<WindowManager, err::InitializationFailure> initialize();

  ResultRef<SkCanvas, err::NotInitialized> canvas() {
    if (m_canvas == nullptr) {
      return std::unexpected{err::NotInitialized()};
    }

    return *m_canvas;
  }

  Result<void, err::NotInitialized> draw();

  int height() { return m_height; }
  int width() { return m_width; }

  WindowManager(WindowManager &) = delete;
  WindowManager(WindowManager &&) = delete;

private:
  WindowManager();

  Result<void, err::InitializationFailure> initialize_skia_canvas();
  Result<void, err::InitializationFailure> initialize_window();

  ResultRef<SDL_Window, err::NotInitialized> window() {
    if (m_window == nullptr) {
      return std::unexpected{err::NotInitialized("m_window")};
    }

    return *m_window;
  }

  ResultRef<SDL_Texture, err::NotInitialized> texture() {
    if (m_texture == nullptr) {
      return std::unexpected{err::NotInitialized("m_texture")};
    }

    return *m_texture;
  }

  ResultRef<SDL_Renderer, err::NotInitialized> renderer() {
    if (m_renderer == nullptr) {
      return std::unexpected{err::NotInitialized("m_renderer")};
    }

    return *m_renderer;
  }

  static inline WindowManager *s_instance = nullptr;
  int m_width;
  int m_height;
  char *m_pixels;
  std::unique_ptr<SkCanvas> m_canvas = nullptr;
  std::unique_ptr<SDL_Window, SDLWindowDeleter> m_window = nullptr;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> m_renderer = nullptr;
  std::unique_ptr<SDL_Texture, SDLTextureDeleter> m_texture = nullptr;
};
