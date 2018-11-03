#pragma once
#include "Point.h"

class ISimplex
{
public:

    virtual double get_deviation() const = 0;
    virtual VariableSetPtr reflection() = 0;
    virtual VariableSetPtr expansion() = 0;
    virtual VariableSetPtr contraction() = 0;
    virtual double value_in_point(const VariableSetPtr& a) const = 0;
    virtual const double minimum_value() const = 0;
    virtual const double middle_value() const = 0;
    virtual const double maximum_value() const = 0;
    virtual void replace_maximum(const VariableSetPtr& a_new_point) = 0;
    virtual void reduce() = 0;
    virtual VariableSetPtr get_gravity_centre() const = 0;

    virtual ~ISimplex() {}
};