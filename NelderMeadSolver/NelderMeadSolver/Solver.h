
#pragma once

#include <thread>

#include "stdafx.h"
#include "SimplexTriple.h"
#include "Bounds.h"

class Solver
{
public:

  Solver(
    std::function<double(const VariableSetPtr&)> objective_function,
    double xmin, 
    double xmax, 
    double ymin, 
    double ymax
  );

  bool solve(
    bool a_multithreading,
    double a_tolerance, 
    Point& a_output,
    double& a_value
  );

private:

  bool internal_solve_cycle(
    double a_tolerance,
    eArea a_area
  );

  std::unique_ptr<ISimplex> getSimplex(const Point& a_p1,
                                       const Point& a_p2,
                                       const Point& a_p3) const;

private:
    
  Bounds m_bounds;

  std::function<double(const VariableSetPtr&)> m_objective_function;

  bool           m_found;
  VariableSetPtr m_found_solution;
  double         m_found_value;

  std::mutex m_mutex;

};