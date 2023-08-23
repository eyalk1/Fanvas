#ifndef USER_ACTIONS__HPP
#define USER_ACTIONS__HPP
#include "bit_set/bit_set.hpp"
#include "common/consts.hpp"
#include <SFML/System/Vector2.hpp>
#include <string_view>
#include <variant>
namespace Canvas {

// ~~~~~~~~~~~~~~~~~~window commands~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct DecorationCmd {
  BlockSet hover;
  BlockSet dehover;
  BlockSet select;
  BlockSet deselect;
  BlockSet highlight;
  BlockSet dehighlight;
};

//~~~~~~~~~~~~~~~~~App commands~~~~~~~~~~~~~~~~~~~~~

struct close_app {};

struct open_repo {
  open_repo(std::string_view path_to_repo) : path(path_to_repo) {}
  std::string_view path;
};

using AppAction = std::variant<close_app, open_repo>;

//~~~~~~~~~~~~~~~User Commands~~~~~~~~~~~~~~~~~~~
using Event = std::variant<DecorationCmd, AppAction>;
using AppCmd = std::array<std::optional<Canvas::Event>,
                          MAX_NUMBER_OF_APP_ACTIONS_PER_UI_EVENT>;

} // namespace Canvas
#endif //
