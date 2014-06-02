#include "org/modcpp/base/base.h"

#include "org/sketch/ui/UiServer.h"
#include "org/sketch/entity/SketchProgress.h"

using org::sketch::ui::UiServer;
using org::sketch::entity::SketchProgress;

int main(int argc, const char *argv[]) {
  SketchProgress progress;
  UiServer uiServer(progress);
  system("open http://localhost:8080");
  sleep(1000);
  return 0;
}
