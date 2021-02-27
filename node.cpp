#include "node.h"
#include <iostream>
Value::Value(DataType dataType):dataType(dataType){}
DataType Value::getDataType() const {
  return dataType;
}
Port::Port(const std::string & name,bool isInput,Node * node,DataType dataType) :
name(name),isInput(isInput),node(node),dataType(dataType){
  wire = nullptr;
}
Value * Port::getValue()const {
  if(node != nullptr) {
    return node->getValue(name);
  }
  return nullptr;
}
void Port::setValue(Value * value) {
  if(node != nullptr) {
    node->setValue(name,value);
  }
}
Wire * Port::getWire() const{
  return wire;
}
void Port::setWire(Wire * wire) {
  this->wire = wire;
}

Node * Port::getNode() {
  return node;
}
Port::~Port(){}

Node::Node(const std::string & name) :name(name){
}
void Node::init() {
  //init
}
void Node::run() {
  std::cout<<"just a test"<<std::endl;
}

void Node::addInputPort(const std::string & portName,DataType dataType) {
  Port * input = new Port(portName,true,this,dataType);
  inputPorts[portName] = input;
}
void Node::addOutputPort(const std::string & portName,DataType dataType) {
  Port * output = new Port(portName,false,this,dataType);
  outputPorts[portName] = output;
}

Port* Node::getInputPort(const std::string & portName) const{
  return inputPorts.at(portName);
}
Port* Node::getOutputPort(const std::string & portName) const{
  return outputPorts.at(portName);
}

void Node::deleteInputPort(const std::string& portName) {
  inputPorts.erase(portName);
}
void Node::deleteOutputPort(const std::string& portName) {
  outputPorts.erase(portName);
}

std::map<std::string,Port*> Node::enumInputPorts() {
  return inputPorts;
}
std::map<std::string,Port*> Node::enumOutputPorts() {
  return outputPorts;
}
Value * Node::getValue(const std::string & name)const {
  return values.at(name);
}
void Node::setValue(const std::string & name,Value * value){
  values[name] = value;

}
Node::~Node(){
}
Wire::Wire() {
  inputPort = nullptr;
  outputPort = nullptr;
}
void Wire::setInputPort(Port * port) {
  inputPort = port;
  port->setWire(this);
}
void Wire::setOutputPort(Port * port) {
  outputPort= port;
  port->setWire(this);
}

Port * Wire::getInputPort()const {
  return inputPort;
}
Port * Wire::getOutputPort()const {
  return outputPort;
}
void Wire::transport() {
  if(inputPort != nullptr && outputPort != nullptr) {
    outputPort->setValue(inputPort->getValue());
  }
}

AddNode::AddNode(const std::string & name) :Node(name){
}
void AddNode::init() {
  addInputPort("a",DataType::INT);
  addInputPort("b",DataType::INT);
  setValue("a",new IntValue(0));
  setValue("b",new IntValue(0));
  addOutputPort("sum",DataType::INT);
  setValue("sum",new IntValue(0));
}
void AddNode::run() {
  IntValue * av = dynamic_cast<IntValue*>(getInputPort("a")->getValue());
  IntValue * bv = dynamic_cast<IntValue*>(getInputPort("b")->getValue());
  if(av == nullptr || bv == nullptr) {
    return;
  }
  int a = *(int*)av->getValue();
  int b = *(int*)bv->getValue();
  int c = a + b;
  getValue("sum")->setValue(&c);
}

void * IntValue::getValue() {
  return &value;
}
void  IntValue::setValue(void * value) {
  this->value = *(int*)value;
}
std::string IntValue::toString() const {
  return std::to_string(value);
}
ConstNode::ConstNode(const std::string & name,int value) :Node(name){
  this->value = value;
}
void ConstNode::init() {
  addOutputPort("value",DataType::INT);
  setValue("value",new IntValue(this->value));
}
void ConstNode::setIntValue(int value) {
  this->value = value;
}
void ConstNode::run(){
  setValue("value",new IntValue(this->value));
}

DisplayNode::DisplayNode(const std::string & name):Node(name){}

void DisplayNode::run() {
  std::cout<<"display value"<<std::endl;
  for(auto & p : values) {
    std::cout<<p.first<<":";
    std::cout<<p.second->toString();
    std::cout<<std::endl;
  }
}
void run(Node * node) {
  for(auto & f : node->enumInputPorts()) {
    Port * port = f.second;
    if(port != nullptr && port->getWire() != nullptr && port->getWire()->getInputPort() != nullptr) {
      Port * in = port->getWire()->getInputPort();
      run(in->getNode());
      port->getWire()->transport();
    }
  }
  node->run();
}
