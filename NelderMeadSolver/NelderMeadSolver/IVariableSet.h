#pragma once

#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>

namespace nmsolver
{
  class IVariableSet
  {
  public:

    virtual size_t size() const = 0;
    virtual double get_var(size_t index) const = 0;

    virtual std::unique_ptr<IVariableSet> subtract(const IVariableSet*) const = 0;
    virtual std::unique_ptr<IVariableSet> add(const IVariableSet*) const = 0;

    virtual ~IVariableSet() {}
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

using IVariableSetUPtr = std::unique_ptr<nmsolver::IVariableSet>;
using IVariableSetSPtr = std::shared_ptr<nmsolver::IVariableSet>;

