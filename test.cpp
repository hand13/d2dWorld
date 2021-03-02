#include "node.h"
#include <iostream>
#include "context.h"
int main() {
  std::cout<<"start"<<std::endl;
  Context context;
  context.buildFromFile("d:\\inside\\d2dworld\\testing.node");
  context.run();
  return 0;
}
