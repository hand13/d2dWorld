#pragma once
#include "node.h"
class Context {
  private:
    std::map<std::string,Node*> nodes;
    std::map<std::string,Wire*> wires;
    Node* outputNode;
  public:
    Context();
    Node * createNode(const std::string& nodeType,const std::string & nodeName);
    void buildFromFile(const std::string& path);
    void run();
    void clear();
    ~Context();
};
