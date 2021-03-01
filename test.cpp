#include "node.h"
#include <iostream>
int main() {
  std::cout<<"start"<<std::endl;
  ConstNode a("a",2);
  ConstNode b("b",4);
  AddNode add("add");
  SinNode sinNode("sin");
  Int2FloatNode i2fNode("i2f");
  DisplayNode displayNode("display");
  a.init();
  b.init();
  add.init();
  sinNode.init();
  i2fNode.init();
  displayNode.init();
  Wire wirea;
  Wire wireb;
  wirea.setInputPort(a.getOutputPort("value"));
  wirea.setOutputPort(add.getInputPort("a"));
  wireb.setInputPort(b.getOutputPort("value"));
  wireb.setOutputPort(add.getInputPort("b"));

  Wire wirei2f;
  wirei2f.setInputPort(add.getOutputPort("sum"));
  wirei2f.setOutputPort(i2fNode.getInputPort("input"));

  Wire wiresin;
  wiresin.setInputPort(i2fNode.getOutputPort("output"));
  wiresin.setOutputPort(sinNode.getInputPort("input"));

  Wire wiredis;
  wiredis.setInputPort(sinNode.getOutputPort("output"));
  displayNode.addInputPort("resulta",DataType::FLOAT);
  wiredis.setOutputPort(displayNode.getInputPort("resulta"));
  run(&displayNode);
  return 0;
}
