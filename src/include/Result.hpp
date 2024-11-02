#pragma once

#include "Error.hpp"
#include <expected>
#include <functional>
#include <type_traits>
#include <variant>

template <typename T, IsError... Es>
using Result = std::expected<T, std::variant<Es...>>;

template <typename T, IsError... Es>
using ResultRef = std::expected<std::reference_wrapper<T>, std::variant<Es...>>;

template <typename T, typename... Es>
ResultRef<T, Es...> ok_ref(T &v) {
  return {std::cref(v)};
}

#define RET_ON_ERR_REF(result, name) \
if (!result.has_value()) { \
  return std::unexpected{result.error()}; \
}\
auto &name = result->get()

#define RET_ON_ERR(result, name) \
if (!result.has_value()) { \
  return std::unexpected{result.error()}; \
}\
auto name = result.value()

#define RET_ON_ERR_VOID(result) \
if (!result.has_value()) { \
  return std::unexpected{result.error()}; \
}\
