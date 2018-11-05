#include "stdafx.h"
#include "SimplexGeneric.h"

using namespace nmsolver;

SimplexGeneric::SimplexGeneric(size_t simplex_size)
  :expected_size_(simplex_size)
{
  variables_.reserve(simplex_size);
}

double SimplexGeneric::get_deviation() const
{
  auto p = get_gravity_centre();
  auto grav_centre = dynamic_cast<VariableSetGeneric*>(p.get());

  auto var0 = dynamic_cast<VariableSetGeneric*>(variables_[0].get());
  auto var1 = dynamic_cast<VariableSetGeneric*>(variables_[1].get());
  auto var2 = dynamic_cast<VariableSetGeneric*>(variables_[2].get());

  VariableSetGeneric v0;

  v0.push_back((TheWrapper)(var0->get_var(0) - p->get_var(0)));
  v0.push_back((TheWrapper)(var0->get_var(1) - p->get_var(1)));

  auto len0 = length(&v0);

  VariableSetGeneric v1;

  v1.push_back((TheWrapper)(var1->get_var(0) - p->get_var(0)));
  v1.push_back((TheWrapper)(var1->get_var(1) - p->get_var(1)));

  auto len1 = length(&v1);

  VariableSetGeneric v2;

  v2.push_back((TheWrapper)(var2->get_var(0) - p->get_var(0)));
  v2.push_back((TheWrapper)(var2->get_var(1) - p->get_var(1)));

  auto len2 = length(&v2);

  return std::max(len0, std::max(len1, len2));
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
