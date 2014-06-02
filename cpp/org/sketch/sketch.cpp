#include "org/modcpp/base/base.h"

#include "org/modcpp/string/String.h"
#include "org/sketch/entity/SketchProgress.h"
#include "org/sketch/FileProcessor.h"
#include "org/sketch/ui/UiServer.h"

using org::modcpp::string::String;
using org::sketch::entity::SketchProgress;
using org::sketch::FileProcessor;
using org::sketch::ui::UiServer;

int main(int argc, const char *argv[]) {
  String fileName = (argc >= 2) ? argv[1] : "input.txt";
  SketchProgress progress;
  FileProcessor fileProcessor(fileName, progress);
  UiServer uiServer(progress);
  system("open http://localhost:8080");

  sleep(1000);
  return 0;
}
