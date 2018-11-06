#include "stdafx.h"
#include "SimplexGeneric.h"

using namespace nmsolver;

SimplexGenericDouble::SimplexGeneric(
  std::function<double(const IVariableSet*)> obj_function,
  size_t simplex_size
)
  : objective_(obj_function)
  , expected_size_(simplex_size)
{
  variables_.reserve(simplex_size);
}

double SimplexGenericDouble::get_deviation() const
{
  using VariableSetDouble = VariableSetGeneric<T>;

  auto grav_centre = get_gravity_centre();

  auto max_len = 0.0;
  for (auto& var : variables_)
  {
    auto len = length(var->subtract(grav_centre.get()).get());
    if (max_len < len)
      max_len = len;
  }

  return max_len;
}

IVariableSetUPtr SimplexGenericDouble::reflection()
{
  auto size = variable_size();
  auto res = std::make_unique<VariableSetGeneric<T>>(size);
  auto last = variables_.back().get();
  auto centroid = get_centroid();

  auto coef = alfa();
  auto div = centroid->subtract(last);
  auto reflection = centroid->add(div.get());

  for (size_t i = 0; i < size; ++i)
  {
    auto value = VariableSetGeneric<T>::_type(0);
    res->set_var(i, value.get());
  }
  return reflection;
}

IVariableSetUPtr SimplexGenericDouble::expansion()
{
  return VariableSetDoublePtr();
}

IVariableSetUPtr SimplexGenericDouble::contraction()
{
  return VariableSetDoublePtr();
}

void SimplexGenericDouble::shrink()
{
}

double SimplexGenericDouble::value_in_point(const IVariableSetUPtr & a) const
{
  return objective_(a.get());
}

const double SimplexGenericDouble::minimum_value() const
{
  return 0.0;
}

const double SimplexGenericDouble::middle_value() const
{
  return 0.0;
}

const double SimplexGenericDouble::maximum_value() const
{
  return 0.0;
}

void SimplexGenericDouble::replace_maximum(const IVariableSetUPtr & a_new_point)
{
}

template<>
IVariableSetUPtr SimplexGenericDouble::get_gravity_centre() const
{
  using VariableSetDouble = VariableSetGeneric<T>;
  using Wrapper = VariableSetDouble::_type;

  auto size = variable_size();
  auto res = std::make_unique<VariableSetDouble>(size);
  
  for (size_t i = 0; i < size; ++i)
  {
    auto sum = Wrapper(0);
    for (auto& varset : variables_)
    {
      auto d = (sum.get() + varset->get_var(i));
      sum.set(d);
    }
    sum.set(sum.get() / simplex_size());
    res->set_var(i, sum.get());
  }
  return res;
}

template<>
IVariableSetUPtr SimplexGenericDouble::get_centroid()
{
  auto cmp = [this](const IVariableSetSPtr& a, const IVariableSetSPtr& b)
  {
    return objective_(a.get()) < objective_(b.get());
  };

  std::sort(variables_.begin(), variables_.end(), cmp);

  auto var_size = variable_size();
  auto res = std::make_unique<VariableSetGeneric<T>>(var_size);

  // looping through components of a simplex' variable
  for (size_t i = 0; i < var_size; ++i)
  {
    auto sum = VariableSetGeneric<T>::_type(0);
    auto smx_size = simplex_size();

    // looping through the vars themselves
    for (size_t j = 0; j < smx_size - 1; ++j)
    {
      auto& varset = variables_[j];
      auto d = (sum.get() + varset->get_var(i));
      sum.set(d);
    }
    sum.set(sum.get() / (smx_size - 1));
    res->set_var(i, sum.get());
  }
  return res;
}

bool SimplexGenericDouble::addVariableSet(IVariableSetSPtr& varset)
{
  if (variables_.size() < expected_size_)
  {
    variables_.push_back(varset);
    return true;
  }

  return false;
}

template<>
size_t SimplexGenericDouble::simplex_size() const
{
  return variables_.size();
}

template<>
size_t SimplexGenericDouble::variable_size() const
{
  if (!variables_.empty())
    return variables_.front()->size();   

  return size_t(0);
}

IVariableSetSPtr SimplexGenericDouble::get_variable(size_t index) const
{
  return variables_[index];
}

//void MakeTheTemplatesLink()
//{
//  SimplexGeneric<ValueWrapperDouble> o(0);
//  o.get_gravity_centre();
//}