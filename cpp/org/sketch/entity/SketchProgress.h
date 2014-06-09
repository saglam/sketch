#ifndef org_sketch_entity_SketchProgress
#define org_sketch_entity_SketchProgress

#include <cstdint>
#include <type_traits>
#include <iostream>

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
    typedef String DomainT;
    typedef uint32_t RangeT;
    typedef RangeT SpaceSavingRangeT;
    typedef std::make_signed<RangeT>::type CountSketchRangeT;

    static const uint CountSketchLogRows = 10;
    static const uint CountSketchLogCols = 10;
    static const uint SpaceSavingLogCounters = 10; 

   public:
    SketchProgress() : totalFileSize(1), processedSize(1),
        countSketch(CountSketchLogRows, CountSketchLogCols),
        spaceSavingSketch(SpaceSavingLogCounters) {}

    CountSketch<DomainT, CountSketchRangeT> &getCountSketch() { return countSketch; }
    const CountSketch<DomainT, CountSketchRangeT> &getCountSketch() const { return countSketch; }

    SpaceSavingSketch<DomainT, SpaceSavingRangeT> &getSpaceSavingSketch() {
      return spaceSavingSketch;
    }

    const SpaceSavingSketch<DomainT, SpaceSavingRangeT> &getSpaceSavingSketch() const {
      return spaceSavingSketch;
    }

    void update(DomainT coord, RangeT update) {
      std::cout << "Updating " << coord << "\n";
      countSketch.update(coord, (CountSketchRangeT) update);
      spaceSavingSketch.update(coord, update);
    }

    bool isDone() const { return false; }

   private:
    SizeType totalFileSize;
    SizeType processedSize;

    CountSketch<DomainT, CountSketchRangeT> countSketch;
    SpaceSavingSketch<DomainT, SpaceSavingRangeT> spaceSavingSketch;
  };

}}} // namespace

#endif
