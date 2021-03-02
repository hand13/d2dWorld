#pragma once
#include "node.h"
typedef bool (*RunProcedure)(std::map<std::string,Port*> inputs,std::map<std::string,Port*> outputs);
class GenericNode:public Node{
  private:
    RunProcedure  runProcedure;
  public: 
    GenericNode(const std::string & name,const std::map<std::string,DataType>& inputs,
        const std::map<std::string,DataType>& outputs,RunProcedure runProcedure);
    virtual void run();
};
