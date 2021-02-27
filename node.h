#pragma once
#include <map>
#include <vector>
#include <string>
class Node;
class Wire;

enum DataType {
  STRING,
  INT,
  FLOAT,
  INT_VECTOR3,
  FLOAT_VECTOR3
};

class Value {
  private:
    DataType dataType;
  public:
    Value(DataType dataType);
    DataType getDataType()const;
    virtual void * getValue()= 0;
    virtual std::string toString()const = 0;
    virtual void setValue(void * value) = 0;
};

class Port {
  private:
    std::string name;
    bool isInput;
    Wire * wire;
    Node * node;
    DataType dataType;
  public:
    Port(const std::string & name,bool isInput,Node * node,DataType dataType);
    virtual Value * getValue() const;
    virtual void setValue(Value * value);
    Wire * getWire()const;
    virtual ~Port();
};

class Node {
  protected:
    std::string name;
    std::map<std::string,Port*> inputPorts;
    std::map<std::string,Port*> outputPorts;
    std::map<std::string,Value *> values;
  public:
    Node(const std::string & name);
    virtual void init();
    virtual void run();
    void addInputPort(const std::string& portName,DataType dataType);
    void addOutputPort(const std::string& portName,DataType dataType);
    Port* getInputPort(const std::string& portName)const;
    Port* getOutputPort(const std::string& portName)const;
    void deleteInputPort(const std::string& portName);
    void deleteOutputPort(const std::string& portName);
    std::map<std::string,Port*> enumInputPorts();
    std::map<std::string,Port*> enumOutputPorts();
    Value * getValue(const std::string & name) const;
    void setValue(const std::string &name,Value * value);
    virtual ~Node();
};
class Wire {
  private:
    Port * inputPort;
    Port * outputPort;
  public:
    Wire();
    void setInputPort(Port * port);
    void setOutputPort(Port * port);
    Port * getInputPort() const;
    Port * getOutputPort()const;
    void transport();
};

class IntValue:public Value {
  private:
    int value;
  public:
    IntValue(int value):Value(DataType::INT),value(value){}
    virtual void * getValue();
    virtual void setValue(void * value);
    virtual std::string toString()const;
};

class ConstNode:public Node {
  private:
    int value;
  public:
    ConstNode(const std::string & name,int value);
    virtual void init();
    void setIntValue(int value);
    virtual void run();
};

class AddNode :public Node {
  public:
    AddNode(const std::string & name);
    virtual void init();
    virtual void run();
};
class DisplayNode:public Node {
  public:
    DisplayNode(const std::string & name);
    virtual void run();
};
