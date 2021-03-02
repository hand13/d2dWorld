#include "context.h"
#include <fstream>
Context::Context() {
  outputNode = nullptr;
}
  Node * Context::createNode(const std::string& nodeType,const std::string & nodeName) {
    Node * result = nullptr;
    if(nodeType == "sin") {
      result =  new SinNode(nodeName);
    }
    if(nodeType == "display") {
      result = new DisplayNode(nodeName);
    }
    if(nodeType == "const") {
      ConstNode* cn = new ConstNode(nodeName,0);
      cn->setIntValue(12);//todo
      result = cn;
    }
    if(nodeType == "add") {
      result = new AddNode(nodeName);
    }
    if(nodeType == "i2f") {
      result = new Int2FloatNode(nodeName);
    }
    if(result != nullptr) {
      nodes[nodeName] = result;
    }
    return result;
  }
void Context::run() {
  if(outputNode != nullptr) {
    ::run(outputNode);
  }
}
void Context::clear() {
  for(auto & node:nodes) {
    if(node.second != nullptr) {
      delete node.second;
    }
  }
  for(auto & wire:wires) {
    if(wire.second != nullptr) {
      delete wire.second;
    }
  }
  nodes.clear();
  wires.clear();
  outputNode = nullptr;
}
Context::~Context() {
  clear();
}
void Context::buildFromFile(const std::string & path) {
  clear();
  std::ifstream m;
  m.open(path);
  if(!m.is_open()) {
    return;
  }
  int nodeLength = 0;
  m >> nodeLength;
  if(nodeLength == 0) {
    m.close();
    return;
  }
  for(int i =0;i<nodeLength;i++) {
    std::string type,name;
    m >> type>>name;
    Node * node = createNode(type,name);
    if (node != nullptr) {
        node->init();
    }
  }
  int wireLength = 0;
  m >> wireLength;
  for(int i = 0;i<wireLength;i++) {
    std::string name;
    m >>name;
    wires[name] = new Wire();
  }
  int binds = 0;
  m >> binds;
  for(int i =0;i<binds;i++) {
    std::string inputNodeName,inputPortName,wireName,outputNodeName,outputPortName;
    m >> inputNodeName>>inputPortName>>wireName>>outputNodeName>>outputPortName;
    if(nodes.count(inputNodeName) <= 0 || nodes.count(outputNodeName) <=0) {
      continue;
    }
    if(wires.count(wireName) <=0) {
      continue;
    }
    Port* inputPort = nodes[inputNodeName]->getOutputPort(inputPortName);
    Port* outputPort= nodes[outputNodeName]->getInputPort(outputPortName);
    if(inputPort != nullptr && outputPort != nullptr) {
      Wire * wire = wires[wireName];
      wire->setInputPort(inputPort);
      wire->setOutputPort(outputPort);
    }
  }
  std::string outputNodeName;
  m >> outputNodeName;
  if(nodes.count(outputNodeName) > 0) {
    outputNode = nodes[outputNodeName];
  }
  m.close();
}
