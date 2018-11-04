#pragma once

#include <cassert>
#include <vector>
#include <memory>

class IVariableSet
{
public:

  virtual size_t size() const = 0;
  virtual double get_var(size_t index) const = 0;
          
  virtual ~IVariableSet() {}
};

using VariableSetPtr = std::unique_ptr<IVariableSet>;


class VariableSetGeneric : public IVariableSet
{
public:

  VariableSetGeneric();
  ~VariableSetGeneric() {}

  size_t size() const override;
  double get_var(size_t index) const override;

  void push_back(double value);

private:

  std::vector<double> vars_;
};