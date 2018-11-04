#include "stdafx.h"
#include "SimplexFactory.h"

std::unique_ptr<SimplexTriple> SimplexFactory::simplexTriple(
  std::function<double(const IVariableSetUPtr&)> obj_function, 
  const Bounds& bounds,
  eArea a_area)
{
  Point p1(0, 0), p2(0, 0), p3(0, 0);
  bounds.build_triangle_on_area(a_area, p1, p2, p3);
  auto simplex = std::make_unique<SimplexTriple>(
    obj_function,
    p1, p2, p3
  );
  simplex->setBounds(bounds);
  return simplex;
}
