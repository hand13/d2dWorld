#include "GenericNode.h"
GenericNode::GenericNode(const std::string & name,const std::map<std::string,DataType>& inputs,
        const std::map<std::string,DataType>& outputs,RunProcedure runProcedure) :Node(name){
  for(auto & input:inputs) {
    this->addInputPort(input.first,input.second);
  }
  for(auto & output:outputs) {
    this->addInputPort(output.first,output.second);
  }
  this->runProcedure = runProcedure;
}
void GenericNode::run() {
  runProcedure(inputPorts,outputPorts);
}
