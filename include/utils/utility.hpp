#ifndef CANVAS_UTILITY__HPP
#define CANVAS_UTILITY__HPP

#include <array>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

#define PASS()

#define TODO(...)                                                              \
  { /*__va_args__*/                                                            \
  }

#define UNUSED(var) "(void)var"

template <typename T, std::size_t N>
using optarray = std::array<std::optional<T>, N>;

template <typename CONTAINER, typename Func, typename... Args>
auto for_each_optional(CONTAINER const &container, Func const &function, Args &&...args)
    -> void {
  for (auto const &element : container)
    if (element)
      std::invoke(function, *element, std::forward<Args>(args)...);
}

template <typename SETINDEX, typename SET, typename FUNC, typename... Args>
auto for_indexes(SETINDEX const &set_index, SET &set, FUNC const &f,
                 Args &&...args) {
  for (auto const &index : set_index) {
    if (set[index]) {
      std::invoke(f, set[index], std::forward<Args>(args)...);
    }
  }
}

template <typename var, typename T, std::size_t index = 0>
consteval std::size_t type2index() {
  static_assert(std::variant_size_v<var> > index, "type not in variant");
  if constexpr (std::is_same_v<std::variant_alternative_t<index, var>, T>) {
    return index;
  } else {
    return type2index<var, T, index + 1>();
  }
}

#endif // CANVAS_UTILITY__HPP
