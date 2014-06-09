#ifndef org_sketch_entity_SketchProgress
#define org_sketch_entity_SketchProgress

#include <cstdint>

#include "org/modcpp/string/String.h"
#include "org/modcpp/sketching/CountSketch.h"
#include "org/modcpp/sketching/SpaceSavingSketch.h"

namespace org {
namespace sketch {
namespace entity {
  using org::modcpp::sketching::CountSketch;
  using org::modcpp::sketching::SpaceSavingSketch;
  using org::modcpp::string::String;

  class SketchProgress {
   public:
    typedef uint64_t SizeType;

   public:
    SketchProgress() : totalFileSize(1), processedSize(1),
        countSketch(8, 8), spaceSavingSketch(10) {}

    CountSketch<String, int32_t> &getCountSketch() { return countSketch; }
    SpaceSavingSketch<String, uint32_t> &getSpaceSavingSketch() { return spaceSavingSketch; }

   private:
    SizeType totalFileSize;
    SizeType processedSize;

    CountSketch<String, int32_t> countSketch;
    SpaceSavingSketch<String, uint32_t> spaceSavingSketch;
  };

}}} // namespace

#endif
