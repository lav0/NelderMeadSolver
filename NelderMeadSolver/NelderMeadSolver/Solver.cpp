
#include "stdafx.h"
#include "Solver.h"


//=============================================================================
Solver::Solver(
  std::function<double(double, double)> obj_fnc,
  double xmin, double xmax, double ymin, double ymax
) :
  m_bounds(xmin, xmax, ymin, ymax),
  m_objective_function(obj_fnc),
  m_found(false),
  m_found_solution(0,0)
//
//
//
{
  m_found_solution = Point(m_bounds.middle_x(), m_bounds.middle_y());
  m_found_value = m_objective_function(m_found_solution.X, m_found_solution.Y);
}
   

//=============================================================================
bool Solver::internal_solve_cycle(
  double a_tolerance,  
  eArea a_area
)
//
//
//
{    
  Point p1(0,0), p2(0,0), p3(0,0);

  bool bounds_are_good = m_bounds.build_triangle_on_area(a_area, p1, p2, p3);

  if (!bounds_are_good) {
    return false;
  }
    
  std::unique_ptr<SimplexTriple> a_simplex(
    new SimplexTriple(
      m_objective_function, 
      p1, p2, p3
    )
  );

  while (a_simplex->get_deviation() > a_tolerance) {

    Point refl(a_simplex->reflection());
    
    m_bounds.check(refl);

    double refl_val = a_simplex->value_in_point(refl);

    if (refl_val < a_simplex->minimum_value()) {

      Point expn(a_simplex->expansion());

      m_bounds.check(expn);

      double expn_val = a_simplex->value_in_point(expn);

      if (expn_val < refl_val)
      {
        a_simplex->replace_maximum(expn);
      }
      else
      {
        a_simplex->replace_maximum(refl);
      }
    
    } else if (refl_val < a_simplex->middle_value()) 
    {
      a_simplex->replace_maximum(refl);
    } 
    else 
    { 

      Point contr(a_simplex->contraction());

      double contr_val = a_simplex->value_in_point(contr);

      if (contr_val < a_simplex->maximum_value()) 
      {
        a_simplex->replace_maximum(contr);
      }
      else
      {
        a_simplex->reduce();
      }

    }
  }
  
  Point centre(a_simplex->get_gravity_centre());
  double value = a_simplex->value_in_point(centre);

  m_mutex.lock();

  if (m_found_value > value) {

    m_found = true;
    m_found_value = value;
    m_found_solution = centre;
  
  }

  m_mutex.unlock();

  return true;
}

//=============================================================================
bool Solver::solve(
  bool a_multithreading,
  double a_tolerance, 
  double& a_result_x, 
  double& a_result_y,
  double& a_value
)
//
//
//
{
   if (!m_bounds.is_defined())
     return false;
    
  if (a_multithreading) {
    std::thread thread1(&Solver::internal_solve_cycle, this, a_tolerance, eArea::SW);
    std::thread thread2(&Solver::internal_solve_cycle, this, a_tolerance, eArea::SE);
    std::thread thread3(&Solver::internal_solve_cycle, this, a_tolerance, eArea::NW);
    std::thread thread4(&Solver::internal_solve_cycle, this, a_tolerance, eArea::NE);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
  } 
  else 
  {
    internal_solve_cycle(a_tolerance, eArea::CENTRAL);
  }

  if (!m_found)
    return false;

  a_result_x = m_found_solution.X;
  a_result_y = m_found_solution.Y;

  a_value = m_found_value;

  return true;
}

//=============================================================================