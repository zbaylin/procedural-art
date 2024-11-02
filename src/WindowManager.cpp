#include "WindowManager.hpp"
#include "Result.hpp"
#include "SkImageInfo.h"
#include <memory>
#include <spdlog/spdlog.h>

const int DEFAULT_WIDTH = 1280;
const int DEFAULT_HEIGHT = 720;

WindowManager::WindowManager() {}

Result<void, err::InitializationFailure>
WindowManager::initialize_skia_canvas() {
  auto info = SkImageInfo::MakeN32Premul(m_width, m_height);
  auto row_bytes = info.minRowBytes();
  auto size = info.computeByteSize(row_bytes);
  m_pixels = new char[size];
  m_canvas = SkCanvas::MakeRasterDirect(info, m_pixels, row_bytes);
  if (m_canvas == nullptr) {
    return std::unexpected{err::InitializationFailure()};
  }

  return {};
}

Result<void, err::InitializationFailure> WindowManager::initialize_window() {
  auto window = SDL_CreateWindow("procedural art", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                 SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    return std::unexpected{err::InitializationFailure()};
  }
  m_window = std::unique_ptr<SDL_Window, SDLWindowDeleter>{window};

  auto renderer =
      SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    return std::unexpected{err::InitializationFailure()};
  }
  m_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>{renderer};

  auto texture =
      SDL_CreateTexture(m_renderer.get(), SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
  if (texture == nullptr) {
    return std::unexpected{err::InitializationFailure()};
  }
  m_texture = std::unique_ptr<SDL_Texture, SDLTextureDeleter>{texture};

  return {};
}

ResultRef<WindowManager, err::InitializationFailure>
WindowManager::initialize() {
  if (s_instance == nullptr) {
    s_instance = new WindowManager();

    s_instance->m_width = DEFAULT_WIDTH;
    s_instance->m_height = DEFAULT_HEIGHT;

    RET_ON_ERR_VOID(s_instance->initialize_skia_canvas());
    RET_ON_ERR_VOID(s_instance->initialize_window());
  } else {
    spdlog::warn("Attempted to double-initialize WindowManager.");
  }

  return *s_instance;
}

Result<void, err::NotInitialized> WindowManager::draw() {
  RET_ON_ERR_REF(this->renderer(), renderer);
  RET_ON_ERR_REF(this->texture(), texture);

  SDL_UpdateTexture(&texture, nullptr, m_pixels, m_width * sizeof(uint32_t));
  SDL_RenderCopy(&renderer, &texture, nullptr, nullptr);
  SDL_RenderPresent(&renderer);

  return {};
}
