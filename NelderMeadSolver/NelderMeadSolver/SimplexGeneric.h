#pragma once

#include "ISimplex.h"
#include "VariableSetGeneric.h"

template<typename INNER_TYPE>
class SimplexGeneric : public ISimplex
{
public:

  using Simplex = SimplexGeneric<INNER_TYPE>;
  using T = INNER_TYPE;

  SimplexGeneric(
    std::function<double(const IVariableSet*)> obj_function,
    size_t simplex_size
    );
  ~SimplexGeneric() override {}

  double get_deviation() const override;
  IVariableSetUPtr reflection() override;
  IVariableSetUPtr expansion() override;
  IVariableSetUPtr contraction() override;
  void shrink() override;
  double value_in_point(const IVariableSetUPtr& a) const override;
  const double minimum_value() const override;
  const double middle_value() const override;
  const double maximum_value() const override;
  void replace_maximum(const IVariableSetUPtr& a_new_point) override;
  IVariableSetUPtr get_gravity_centre() const override;
  IVariableSetUPtr get_centroid();

  bool addVariableSet(IVariableSetSPtr& varset);
  size_t simplex_size() const;
  size_t variable_size() const;
  IVariableSetSPtr get_variable(size_t index) const;

private:

  std::function<double(const IVariableSet*)> objective_;
  size_t expected_size_;

  std::vector<IVariableSetSPtr> variables_;

  IVariableSetUPtr centroid_;
};

using SimplexGenericDouble = SimplexGeneric<ValueWrapperDouble>;
