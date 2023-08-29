#ifndef USER_ACTIONS__HPP
#define USER_ACTIONS__HPP
#include "bit_set/bit_set.hpp"
#include "common/consts.hpp"
#include "ui/code-blocks/CodeBlock.hpp"
#include <SFML/System/Vector2.hpp>
#include <string_view>
#include <variant>
namespace Canvas {

// ~~~~~~~~~~~~~~~~~~window commands~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct DecorationCmd {
  std::array<BlockSet, decorations::number_of_decorations> decs{};
  BlockSet &select() { return decs[decorations::select]; };
  BlockSet &deselect() { return decs[decorations::deselect]; };
  BlockSet &highlight() { return decs[decorations::highlight]; };
  BlockSet &dehighlight() { return decs[decorations::dehighlight]; };
  BlockSet &hover() { return decs[decorations::hover]; };
  BlockSet &dehover() { return decs[decorations::dehover]; };
  DecorationCmd &select(BlockSet val) {
    decs[decorations::select] = val;
    return *this;
  };
  DecorationCmd &deselect(BlockSet val) {
    decs[decorations::deselect] = val;
    return *this;
  };
  DecorationCmd &highlight(BlockSet val) {
    decs[decorations::highlight] = val;
    return *this;
  };
  DecorationCmd &dehighlight(BlockSet val) {
    decs[decorations::dehighlight] = val;
    return *this;
  };
  DecorationCmd &hover(BlockSet val) {
    decs[decorations::hover] = val;
    return *this;
  };
  DecorationCmd &dehover(BlockSet val) {
    decs[decorations::dehover] = val;
    return *this;
  };
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
