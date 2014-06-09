#include "org/sketch/FileProcessor.h"

#include "org/sketch/entity/SketchProgress.h"
#include "Poco/Thread.h"

namespace org {
namespace sketch {

  FileProcessor::FileProcessor(const String fileName, entity::SketchProgress &progress)
      : progress(progress) {
    const String terminatedName = "" + fileName + String("\0", 1);
    file = fopen(terminatedName.begin(), "r");
    printf("File opened %s\n", terminatedName.begin());
  }

  FileProcessor::~FileProcessor() {
  	fclose(file);
  }

  void FileProcessor::start() {
  	Poco::Thread thread;
  	thread.start(*this);
  	thread.join();
  }

  void FileProcessor::run() {
  	char buffer[512];
  	if (file == nullptr) {
  	  return;
  	}
  	while (fscanf(file, "%s", buffer) > 0) {
  	  progress.update(String::copyOf(buffer), 1);
  	}
  	Poco::Thread::sleep(1000);
  }

}} // namespace
