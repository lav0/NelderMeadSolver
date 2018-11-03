#pragma once

#include <array>
#include <vector>
#include <memory>

class IVariableSet
{
public:
        
    virtual ~IVariableSet() {}
};
using VariableSetPtr = std::unique_ptr<IVariableSet>;

template<size_t Dimension>
struct VariableSet
{
    using Var = VariableSet<Dimension>;

    Var() {}
    Var(double a_x, double a_y) { values_[0] = a_x; values_[1] = a_y; }

    inline Var operator+(const Var& a) const
    {
        Var res; 

        for (size_t i = 0; i < Dimension; ++i)
            res.values_[i] = this->values_[i] + a.values_[i];

        return res;
    }
    inline Var operator-(const Var& a) const
    {
        Var res;

        for (size_t i = 0; i < Dimension; ++i)
            res.values_[i] = this->values_[i] - a.values_[i];

        return res;
    }
    inline Var operator*(double c) const
    {
        Var res;

        for (size_t i = 0; i < Dimension; ++i)
            res.values_[i] = this->values_[i] * c;

        return res;
    }

    std::array<double, Dimension> values_;
};


