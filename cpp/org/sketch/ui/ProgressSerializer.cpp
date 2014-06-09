#include "org/sketch/ui/ProgressSerializer.h"

#include "org/modcpp/string/StringBuilder.h"

namespace org {
namespace sketch {
namespace ui {
  using org::modcpp::string::StringBuilder;

  String ProgressSerializer::getTopK(SizeType k) {
    std::vector<Item> items;
    progress.getSpaceSavingSketch().getTopK(items, k);

    const auto &countSketch = progress.getCountSketch();
    String serialized = "[";
    for (auto &item : items) {
      StringBuilder builder(128);
      serialized = serialized + builder.put("[\"").put(item.coord).put("\",")
          .put(String::valueOf(item.count)).put(",")
          .put(String::valueOf(item.count - item.maxOvershoot)).put(",")
          .put(String::valueOf(countSketch.get(item.coord))).put("],")
          .build();
    }
    return items.empty() ? "[]" : serialized.trimRight(1) + "]";
  }

}}} // namespace
