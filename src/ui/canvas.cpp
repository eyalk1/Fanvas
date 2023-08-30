#include "ui/canvas.hpp"
#include "common/error.hpp"
#include "ui/code-blocks/CodeBlock.hpp"
#include <string_view>
namespace Canvas {
auto CanvasManager::blockUnderMouse(int x, int y) -> BlockSet {
  return m_block_manager.findBlocks([=](auto const &block_in_question) {
    return block_in_question.contains({x, y});
  });
}
auto CanvasManager::addBlock(std::string_view header, std::string_view source)
    -> Error {
  RETURN_ERROR_OR_NULLOPT(
      m_block_manager.newCodeBlock(std::string(header), std::string(source)));
}
auto CanvasManager::decorateBlocks(DecorationCmd dec_cmd) -> void {
  // TODO: use enumerate
  std::underlying_type_t<decorations> dec_type = 0;
  for (auto windows_to_dec : dec_cmd.decs) {
    m_block_manager.apply<CodeBlocksManager::decorate>(windows_to_dec,
                                                       dec_type);
    dec_type++;
  }
}
} // namespace Canvas
