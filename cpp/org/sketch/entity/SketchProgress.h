#ifndef org_sketch_entity_SketchProgress
#define org_sketch_entity_SketchProgress

#include <cstdint>

#include "org/modcpp/string/String.h"
#include "org/modcpp/sketching/CountSketch.h"

namespace org {
namespace sketch {
namespace entity {
  using org::modcpp::string::String;
  using org::modcpp::sketching::CountSketch;

  class SketchProgress {
   public:
    SketchProgress() : totalFileSize(1), processedSize(1), countSketch(8, 8) {}

    CountSketch<String, uint64_t> getCountSketch() { return countSketch; }

   private:
    std::size_t totalFileSize;
    std::size_t processedSize;

    CountSketch<String, uint64_t> countSketch;
  };

}}} // namespace

#endif
