#include "org/sketch/ui/ProgressSerializer.h"

#include <iostream>

#include "org/sketch/entity/SketchProgress.h"

using org::sketch::ui::ProgressSerializer;
using org::sketch::entity::SketchProgress;

void test_constructor() {
  SketchProgress progress;
  ProgressSerializer serializer(progress);
}

void test_getTopK() {
  SketchProgress progress;
  ProgressSerializer serializer(progress);

  progress.update("key1", 100);

  std::cout << serializer.getTopK(2) << "\n";
}

int main() {
  test_constructor();
  test_getTopK();
  return 0;
}
