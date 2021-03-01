#include "node.h"
#include <iostream>
int main() {
  std::cout<<"start"<<std::endl;
  ConstNode a("a",100);
  ConstNode b("b",350);
  AddNode add("add");
  SinNode sinNode("sin");
  DisplayNode displayNode("display");
  a.init();
  b.init();
  add.init();
  sinNode.init();
  displayNode.init();
  Wire wirea;
  Wire wireb;
  wirea.setInputPort(a.getOutputPort("value"));
  wirea.setOutputPort(add.getInputPort("a"));
  wireb.setInputPort(b.getOutputPort("value"));
  wireb.setOutputPort(add.getInputPort("b"));

  Wire wiresin;
  wiresin.setInputPort(add.getOutputPort("sum"));
  wiresin.setOutputPort(sinNode.getInputPort("input"));

  Wire wiredis;
  wiredis.setInputPort(sinNode.getOutputPort("output"));
  displayNode.addInputPort("resulta",DataType::INT);
  wiredis.setOutputPort(displayNode.getInputPort("resulta"));
  run(&displayNode);
  return 0;
}
