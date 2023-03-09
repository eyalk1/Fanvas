#ifndef CANVAS_UTILITY__HPP
#define CANVAS_UTILITY__HPP

#include <functional>
#include <utility>

template <typename CONTAINER, typename Func, typename... Args>
auto for_each_optional(CONTAINER const &thing, Func const &f, Args&&... args) -> void {
  for (auto const &t : thing)
    if (t)
      std::invoke(f, t, std::forward<Args>(args)...);
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
#endif // CANVAS_UTILITY__HPP
