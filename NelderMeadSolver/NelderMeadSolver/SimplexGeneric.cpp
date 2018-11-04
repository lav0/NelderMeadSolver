#include "stdafx.h"
#include "SimplexGeneric.h"

SimplexGeneric::SimplexGeneric(size_t simplex_size)
  :expected_size_(simplex_size)
{
  variables_.reserve(simplex_size);
}

double SimplexGeneric::get_deviation() const
{
  return 0.0;
}

IVariableSetUPtr SimplexGeneric::reflection()
{
  return VariableSetGenericPtr();
}

IVariableSetUPtr SimplexGeneric::expansion()
{
  return VariableSetGenericPtr();
}

IVariableSetUPtr SimplexGeneric::contraction()
{
  return VariableSetGenericPtr();
}

void SimplexGeneric::shrink()
{
}

double SimplexGeneric::value_in_point(const IVariableSetUPtr & a) const
{
  return 0.0;
}

const double SimplexGeneric::minimum_value() const
{
  return 0.0;
}

const double SimplexGeneric::middle_value() const
{
  return 0.0;
}

const double SimplexGeneric::maximum_value() const
{
  return 0.0;
}

void SimplexGeneric::replace_maximum(const IVariableSetUPtr & a_new_point)
{
}

IVariableSetUPtr SimplexGeneric::get_gravity_centre() const
{
  auto size = variable_size();
  auto res = std::make_unique<VariableSetGeneric>();
  
  for (size_t i = 0; i < size; ++i)
  {
    auto sum = TheWrapper(0);
    for (auto& varset : variables_)
    {
      auto d = (sum.get() + varset->get_var(i));
      sum.set(d);
    }
    sum.set(sum.get() / simplex_size());
    res->push_back(sum);
  }
  return res;
}

bool SimplexGeneric::addVariableSet(IVariableSetSPtr& varset)
{
  if (variables_.size() < expected_size_)
  {
    variables_.push_back(varset);
    return true;
  }

  return false;
}

size_t SimplexGeneric::simplex_size() const
{
  return variables_.size();
}

size_t SimplexGeneric::variable_size() const
{
  if (!variables_.empty())
    return variables_.front()->size();   

  return size_t(0);
}

IVariableSetSPtr SimplexGeneric::get_variable(size_t index) const
{
  return variables_[index];
}
