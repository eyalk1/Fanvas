#ifndef CONSTS__HPP
#define CONSTS__HPP
#include <array>
#include <concepts> // constructible_from, input_iterator, range, unsigned_integral
#include <cstddef> // size_t
#include <optional>

#define PASS {}

namespace xstd {
template <std::size_t N, std::unsigned_integral> class bit_set;
};
namespace Canvas {

static constexpr size_t MAX_NUMBER_OF_WINDOWS{64};
static constexpr size_t MAX_NUMBER_OF_APP_ACTIONS_PER_UI_EVENT{64};
static constexpr auto MAX_NUMBER_OF_UI_ACTIONS_PER_APP_EVENT = 1;
static constexpr auto MAX_NUMBER_OF_EVENTS = 10;

using WindowSet = xstd::bit_set<MAX_NUMBER_OF_WINDOWS, std::size_t>;

enum Entities { NO_ONE = 0, UI = 1, LSP = 1 << 1, APP = 1 << 2 };
} // namespace Canvas
// WindowSet is the 'fd' of the windows the window manager provides
#endif // CONSTS__HPP
