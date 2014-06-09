#ifndef org_sketch_FileProcessor
#define org_sketch_FileProcessor

#include <cstdio>

#include "org/modcpp/string/String.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

// TODO(saglam): to this multithreaded and using BSD or OS open / close
namespace org {
namespace sketch {

  // For forward declaration
  namespace entity { class SketchProgress; }
  using org::modcpp::string::String;

  class FileProcessor : public Poco::Runnable {
   public:
    FileProcessor(const String fileName, entity::SketchProgress &progress);
    ~FileProcessor();

   public:
   	void start();

   private:
   	virtual void run();

   private:
   	FILE *file;
    entity::SketchProgress &progress;
  };
  
}} // namespace

#endif
