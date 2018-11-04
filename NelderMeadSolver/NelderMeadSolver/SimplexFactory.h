#pragma once

#include "SimplexTriple.h"

class SimplexFactory
{
public:

  static std::unique_ptr<SimplexTriple> simplexTriple(
    std::function<double(const IVariableSetUPtr&)> obj_function, 
    const Bounds& bounds,
    eArea a_area);
};
