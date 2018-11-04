#pragma once

#include "ISimplex.h"
#include "VariableSet.h"

class SimplexGeneric : public ISimplex
{
public:

  SimplexGeneric(size_t simplex_size);
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
  IVariableSetUPtr get_gravity_centre() const;

  bool addVariableSet(IVariableSetSPtr& varset);
  size_t simplex_size() const;
  size_t variable_size() const;
  IVariableSetSPtr get_variable(size_t index) const;

private:

  size_t expected_size_;

  std::vector<IVariableSetSPtr> variables_;
};
