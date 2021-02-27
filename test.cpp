#include "node.h"
#include <iostream>
int main() {
  std::cout<<"start"<<std::endl;
  ConstNode a("a",100);
  ConstNode b("b",300);
  AddNode add("add");
  DisplayNode displayNode("display");
  a.init();
  b.init();
  add.init();
  displayNode.init();
  Wire wirea;
  Wire wireb;
  wirea.setInputPort(a.getOutputPort("value"));
  wirea.setOutputPort(add.getInputPort("a"));
  wireb.setInputPort(b.getOutputPort("value"));
  wireb.setOutputPort(add.getInputPort("b"));
  Wire wiredis;
  wiredis.setInputPort(add.getOutputPort("sum"));
  displayNode.addInputPort("resulta",DataType::INT);
  wiredis.setOutputPort(displayNode.getInputPort("resulta"));
  a.run();
  b.run();
  wirea.transport();
  wireb.transport();
  add.run();
  wiredis.transport();
  displayNode.run();
  return 0;
}
