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
  progress.update("key2", 200);
  progress.update("key3", 300);

  std::cout << serializer.getTopK(4) << "\n";
}

int main() {
  test_constructor();
  test_getTopK();
  return 0;
}
