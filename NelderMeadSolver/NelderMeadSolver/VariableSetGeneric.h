#pragma once
#include "IVariableSet.h"
#include "ValueWrapperDouble.h"

namespace nmsolver
{
  class VariableSetGeneric : public IVariableSet
  {
  public:

    VariableSetGeneric();
    ~VariableSetGeneric() {}

    size_t size() const override;
    double get_var(size_t index) const override;

    std::unique_ptr<IVariableSet> operator-(const IVariableSet*) const override;

    void push_back(ValueWrapperDouble value);

  private:

    std::vector<ValueWrapperDouble> vars_;
  };

  inline double squared_length(const IVariableSet* a)
  {
    double sum = 0;
    auto size = a->size();
    for (decltype(size) i = 0; i < size; ++i)
    {
      auto value = a->get_var(i);
      sum += value * value;
    }
    return sum;
  }
  inline double length(const IVariableSet* a)
  {
    return sqrt(squared_length(a));
  }
}

using VariableSetGenericPtr = std::unique_ptr<nmsolver::VariableSetGeneric>;