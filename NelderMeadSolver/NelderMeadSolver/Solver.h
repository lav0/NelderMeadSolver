
#pragma once

#include <thread>
#include <queue>

#include "stdafx.h"
#include "SimplexFactory.h"

class Solver
{
public:

  Solver(std::function<double(const VariableSetPtr&)> objective);

  void addSimplex(ISimplex* simplex);

  bool solve(
    bool            a_multithreading,
    double          a_tolerance, 
    VariableSetPtr& a_output,
    double&         a_value
  );

private:

  bool internal_solve_cycle(double a_tolerance);

private:
    
  std::function<double(const VariableSetPtr&)> m_objective;

  std::queue<ISimplex*>     m_simplex_queue;
  bool                      m_found;
  VariableSetPtr            m_found_solution;
  double                    m_found_value;

  std::mutex m_mutex;

};