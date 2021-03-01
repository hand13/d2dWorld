#include "node.h"
#include <iostream>
int main() {
  std::cout<<"start"<<std::endl;
  ConstNode a("a",100);
  ConstNode b("b",350);
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
  displayNode.setValue("resulta", new IntValue(0));
  wiredis.setOutputPort(displayNode.getInputPort("resulta"));
  run(&displayNode);
  return 0;
}
