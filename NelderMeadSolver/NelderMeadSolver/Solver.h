
#pragma once

#include <thread>

#include "stdafx.h"
#include "SimplexTriple.h"
#include "Bounds.h"

class Solver
{
public:

  Solver(
    std::function<double(double, double)> objective_function,
    double xmin, 
    double xmax, 
    double ymin, 
    double ymax
  );

  bool solve(
    bool a_multithreading,
    double a_tolerance, 
    double& a_x_out, 
    double& a_y_out, 
    double& a_value
  );

private:

  bool internal_solve_cycle(
    double a_tolerance,
    eArea a_area
  );

private:
    
  Bounds m_bounds;

  std::function<double(double, double)> m_objective_function;

  bool m_found;
  Point m_found_solution;
  double m_found_value;

  std::mutex m_mutex;

};