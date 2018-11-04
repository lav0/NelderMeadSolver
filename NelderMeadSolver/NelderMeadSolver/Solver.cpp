
#include "stdafx.h"
#include "Solver.h"


//=============================================================================
Solver::Solver(
  std::function<double(const IVariableSetUPtr&)> objective
) :
  m_objective(objective),
  m_found(false),
  m_found_solution(nullptr),
  m_found_value(DBL_MAX)
//
//
//
{
}   

//=============================================================================
bool Solver::internal_solve_cycle(
  double a_tolerance
)
//
//
//
{ 
  auto simplex = m_simplex_queue.front();
  m_simplex_queue.pop();

  while (simplex->get_deviation() > a_tolerance) {

    IVariableSetUPtr refl_ptr = simplex->reflection();
    
    double refl_val = simplex->value_in_point(refl_ptr);

    if (refl_val < simplex->minimum_value()) {
        
      IVariableSetUPtr expn_ptr = simplex->expansion();
      
      double expn_val = simplex->value_in_point(expn_ptr);

      if (expn_val < refl_val)
      {
        simplex->replace_maximum(expn_ptr);
      }
      else
      {
        simplex->replace_maximum(refl_ptr);
      }
    
    } else if (refl_val < simplex->middle_value()) 
    {
      simplex->replace_maximum(refl_ptr);
    } 
    else 
    { 
      IVariableSetUPtr contr_ptr = simplex->contraction();

      double contr_val = simplex->value_in_point(contr_ptr);

      if (contr_val < simplex->maximum_value()) 
      {
        simplex->replace_maximum(contr_ptr);
      }
      else
      {
        simplex->shrink();
      }
    }
  }
  
  auto centre = simplex->get_gravity_centre();
  double value = simplex->value_in_point(centre);

  if (m_found_value > value)
  {
    std::lock_guard<std::mutex> guard(m_mutex);

    m_found = true;
    m_found_value = value;
    m_found_solution = std::move(centre);
  }

  return true;
}

//=============================================================================
void Solver::addSimplex(ISimplex * simplex)
//
//
//
{
  m_simplex_queue.push(simplex);
}

//=============================================================================
bool Solver::solve(
  bool            a_multithreading,
  double          a_tolerance,
  IVariableSetUPtr& a_output,
  double&         a_value
)
//
//
//
{
  if (a_multithreading) {
    std::thread thread1(&Solver::internal_solve_cycle, this, a_tolerance);
    std::thread thread2(&Solver::internal_solve_cycle, this, a_tolerance);
    std::thread thread3(&Solver::internal_solve_cycle, this, a_tolerance);
    std::thread thread4(&Solver::internal_solve_cycle, this, a_tolerance);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
  } 
  else 
  {
    internal_solve_cycle(a_tolerance);
  }

  if (!m_found)
    return false;

  auto* point = dynamic_cast<Point*>(m_found_solution.get());
  a_output = std::make_unique<Point>(*point);
  a_value = m_found_value;

  return true;
}

//=============================================================================