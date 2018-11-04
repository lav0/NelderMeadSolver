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

class ValueWrapperDouble
{
public:
  explicit ValueWrapperDouble(double a) : d_(a) {}
  ValueWrapperDouble(const ValueWrapperDouble& other) : d_(other.d_) {}
  ValueWrapperDouble& operator=(const ValueWrapperDouble& other)
  {
    d_ = other.d_;
    return *this;
  }

  const double get() const { return d_; }
  void set(const double& a) { d_ = a; }

private:
  double d_ = 0.0;
};
using TheWrapper = ValueWrapperDouble;

//template<typename T>
class VariableSetGeneric : public IVariableSet
{
public:

  VariableSetGeneric();
  ~VariableSetGeneric() {}

  size_t size() const override;
  double get_var(size_t index) const override;

  void push_back(ValueWrapperDouble value);

private:

  std::vector<ValueWrapperDouble> vars_;
};

using IVariableSetUPtr = std::unique_ptr<IVariableSet>;
using IVariableSetSPtr = std::shared_ptr<IVariableSet>;
using VariableSetGenericPtr = std::unique_ptr<VariableSetGeneric>;

