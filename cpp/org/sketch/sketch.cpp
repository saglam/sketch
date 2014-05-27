#include "org/modcpp/base/base.h"

#include "org/sketch/ui/UiServer.h"

using org::sketch::ui::UiServer;

int main(int argc, const char *argv[]) {
  UiServer uiServer;
  system("open http://localhost:8080");
  sleep(1000);
  return 0;
}
