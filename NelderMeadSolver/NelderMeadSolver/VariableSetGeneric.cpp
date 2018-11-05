#include "stdafx.h"
#include "VariableSetGeneric.h"

using namespace nmsolver;

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

std::unique_ptr<IVariableSet> nmsolver::VariableSetGeneric::operator-(const IVariableSet * other) const
{
  assert(size() == other->size());

  auto ret = std::make_unique<VariableSetGeneric>();

  for (size_t i = 0; i < size(); ++i)
  {
    double d = get_var(i) - other->get_var(i);
    ret->push_back((TheWrapper)d);
  }

  return ret;
}

void VariableSetGeneric::push_back(ValueWrapperDouble value)
{
  vars_.push_back(value);
}
