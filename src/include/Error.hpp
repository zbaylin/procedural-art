#pragma once

#include <optional>
#include <spdlog/fmt/bundled/format.h>
#include <spdlog/fmt/bundled/std.h>
#include <string>

struct Error {
  const std::optional<std::string> msg;

  Error() {}
  Error(std::string msg) : msg(msg) {}
};

template <typename T>
concept IsError = std::is_base_of_v<Error, T>;

template <IsError E> struct fmt::formatter<E> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }

  template <typename FormatContext>
  auto format(const E &input, FormatContext &ctx) -> decltype(ctx.out()) {
    if (input.msg.has_value()) {
      return format_to(ctx.out(), "{}({})", typeid(E).name(), input.msg.value());
    } else {
      return format_to(ctx.out(), "{}", typeid(E).name());
    }
  }
};
