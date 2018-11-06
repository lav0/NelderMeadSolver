#pragma once
#include "IVariableSet.h"
#include "ValueWrapperDouble.h"

namespace nmsolver
{
  template<typename TYPE>
  class VariableSetGeneric : public IVariableSet
  {
  public:

    typedef typename TYPE _type;

    VariableSetGeneric(size_t size) : vars_(size, TYPE(0)) {}
    ~VariableSetGeneric() {}

    size_t size() const override
    {
      return vars_.size();
    }

    double get_var(size_t index) const override
    {
      assert(index < size());

      return vars_[index].get();
    }

    std::unique_ptr<IVariableSet> subtract(const IVariableSet* other) const override
    {
      assert(size() == other->size());

      auto ret = std::make_unique<VariableSetGeneric<TYPE>>(size());

      for (size_t i = 0; i < size(); ++i)
      {
        double d = get_var(i) - other->get_var(i);
        ret->set_var(i, d);
      }

      return ret;
    }

    std::unique_ptr<IVariableSet> add(const IVariableSet* other) const override
    {
      assert(size() == other->size());

      auto ret = std::make_unique<VariableSetGeneric<TYPE>>(size());

      for (size_t i = 0; i < size(); ++i)
      {
        double d = get_var(i) + other->get_var(i);
        ret->set_var(i, d);
      }

      return ret;
    }

    void set_var(size_t index, double value)
    {
      vars_[index].set(value);
    }

    void set_gut(size_t index, const TYPE& gut)
    {
      vars_[index] = gut;
    }

    TYPE& get_gut(size_t index)
    {
      return vars_[index];
    }
    
  private:

    std::vector<TYPE> vars_;
  };

}

using VariableSetDoublePtr = std::unique_ptr<
  nmsolver::VariableSetGeneric<
    nmsolver::ValueWrapperDouble
  >
>;