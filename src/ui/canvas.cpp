#include "ui/canvas.hpp"
#include <string_view>
namespace Canvas {
auto CanvasManager::block_under_mouse(int x, int y) -> BlockSet {
  return m_block_manager.findBlocks([=](auto const &block_in_question) {
    return block_in_question.contains({x, y});
  });
}
void CanvasManager::add_block(std::string_view header,
                              std::string_view source) {
  m_block_manager.newCodeBlock(std::string(header), std::string(source));
}
} // namespace Canvas
