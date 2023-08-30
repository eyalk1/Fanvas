#pragma once
#include "smart_enum/smart_enum.h"
// TODO fix this lol  the path and then clang to version 16
#include "expected/include/tl/expected.hpp"
#include <optional>

namespace Canvas {

// the errors are just a number-description pair
SMART_ENUM(codes, int) {
  SM_ENUM_ELEM(TOO_MANY_CODE_BLOCKS, 1, "too many code blocks",
               "the maximum number of code blocks as been readched cannot "
               "add any more code blocks");
};

template <typename T> using Expect = tl::expected<T, codes>;
using Error = std::optional<codes>;

#define RETURN_ON_ERROR(err)                                                   \
  auto code = err;                                                             \
  if (!code)                                                                   \
    return code.error();

#define RETURN_ERROR_OR_NULLOPT(err)                                           \
  auto code = err;                                                             \
  if (!code)                                                                   \
    return code.error();                                                       \
  else                                                                         \
    return {};

} // namespace Canvas
