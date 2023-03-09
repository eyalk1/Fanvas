#ifndef CONSTS__HPP
#define CONSTS__HPP
#include <array>
#include <concepts> // constructible_from, input_iterator, range, unsigned_integral
#include <cstddef> // size_t
#include <optional>

namespace xstd {
template <std::size_t N, std::unsigned_integral> class bit_set;
};
namespace Canvas {

static constexpr size_t MAX_NUMBER_OF_WINDOWS{64};
static constexpr size_t MAX_NUMBER_OF_ACTIONS_PER_EVENT{64};

using WindowSet = xstd::bit_set<MAX_NUMBER_OF_WINDOWS, std::size_t>;
} // namespace Canvas
// WindowSet is the 'fd' of the windows the window manager provides
#endif // CONSTS__HPP
