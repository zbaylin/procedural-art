add_executable(main
  main.cpp 
  WindowManager.cpp
  ParallelSinusoids.cpp
  RandomLines.cpp
)

if(NOT IS_DIRECTORY ${SKIA_ROOT})
  message(FATAL_ERROR "SKIA_ROOT ${SKIA_ROOT} does not exist.")
endif()

target_link_libraries(main 
  "${SKIA_ROOT}/out/Static/libskia.a"
  "${SKIA_ROOT}/out/Static/libwuffs.a"
  "${SKIA_ROOT}/out/Static/libskcms.a"
  "${SKIA_ROOT}/out/Static/libpng.a"
  "${SKIA_ROOT}/out/Static/libwebp.a"
  "${SKIA_ROOT}/out/Static/libjpeg.a"
  PkgConfig::SDL2
  Boost::range
  spdlog
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(main
    "-framework CoreFoundation"
    "-framework CoreText"
    "-framework CoreServices"
    "-framework CoreGraphics"
    "-framework OpenGL"
  )
endif()

target_include_directories(main PRIVATE 
  "include"
  "${SKIA_ROOT}"
  "${SKIA_ROOT}/include"
  "${SKIA_ROOT}/include/config"
  "${SKIA_ROOT}/include/core"
  "${SDL2_INCLUDE_DIRS}"
)
