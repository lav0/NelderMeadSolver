#include "stdafx.h"
#include "VariableSet.h"

VariableSetGeneric::VariableSetGeneric()
{
}

size_t VariableSetGeneric::size() const
{
  return vars_.size();
}

double VariableSetGeneric::get_var(size_t index) const
{
  assert(index < size());

  return vars_[index].get();
}

void VariableSetGeneric::push_back(ValueWrapperDouble value)
{
  vars_.push_back(value);
}
