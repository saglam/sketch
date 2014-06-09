#ifndef org_sketch_FileProcessor
#define org_sketch_FileProcessor

#include "org/modcpp/string/String.h"

namespace org {
namespace sketch {

  // For forward declaration
  namespace entity { class SketchProgress; }
  using org::modcpp::string::String;

  class FileProcessor {
   public:
    FileProcessor(const String fileName, entity::SketchProgress &progress) : progress(progress) {}

   private:
    entity::SketchProgress &progress;
  };
  
}} // namespace

#endif
