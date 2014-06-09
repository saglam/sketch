#ifndef org_sketch_ui_ProgressSerializer
#define org_sketch_ui_ProgressSerializer

#include "org/modcpp/string/String.h"
#include "org/sketch/entity/SketchProgress.h"

namespace org {
namespace sketch {
namespace ui {
  using org::modcpp::string::String;
  using org::sketch::entity::SketchProgress;

  class ProgressSerializer {
   public:
    typedef uint32_t SizeType;
    struct Item {
      SketchProgress::DomainT coord;
      SketchProgress::SpaceSavingRangeT count;
      SketchProgress::SpaceSavingRangeT maxOvershoot;
    };

   public:
    ProgressSerializer(const SketchProgress &progress) : progress(progress) {}

   public:
    String getTopK(SizeType k);

   private:
    const SketchProgress &progress;
  };

}}} // namespace

#endif
