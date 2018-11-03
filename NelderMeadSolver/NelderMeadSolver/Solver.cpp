
#include "stdafx.h"
#include "Solver.h"


//=============================================================================
Solver::Solver(
  std::function<double(const VariableSetPtr&)> obj_fnc,
  double xmin, double xmax, double ymin, double ymax
) :
  m_bounds(xmin, xmax, ymin, ymax),
  m_objective_function(obj_fnc),
  m_found(false),
  m_found_solution(nullptr)
//
//
//
{
  m_found_solution = std::make_unique<Point>(m_bounds.middle_x(), m_bounds.middle_y());
  m_found_value = m_objective_function(m_found_solution);
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
    
  auto a_simplex = getSimplex(p1, p2, p3);

  while (a_simplex->get_deviation() > a_tolerance) {

    VariableSetPtr refl_ptr = a_simplex->reflection();
    Point* pptr = dynamic_cast<Point*>(refl_ptr.get());
    
    m_bounds.check(*pptr);

    double refl_val = a_simplex->value_in_point(refl_ptr);

    if (refl_val < a_simplex->minimum_value()) {
        
      VariableSetPtr expn_ptr = a_simplex->expansion();
      Point* pptr = dynamic_cast<Point*>(expn_ptr.get());

      m_bounds.check(*pptr);

      double expn_val = a_simplex->value_in_point(expn_ptr);

      if (expn_val < refl_val)
      {
        a_simplex->replace_maximum(expn_ptr);
      }
      else
      {
        a_simplex->replace_maximum(refl_ptr);
      }
    
    } else if (refl_val < a_simplex->middle_value()) 
    {
      a_simplex->replace_maximum(refl_ptr);
    } 
    else 
    { 

      VariableSetPtr contr_ptr = a_simplex->contraction();

      double contr_val = a_simplex->value_in_point(contr_ptr);

      if (contr_val < a_simplex->maximum_value()) 
      {
        a_simplex->replace_maximum(contr_ptr);
      }
      else
      {
        a_simplex->reduce();
      }

    }
  }
  
  auto centre = a_simplex->get_gravity_centre();
  double value = a_simplex->value_in_point(centre);

  m_mutex.lock();

  if (m_found_value > value) {

    m_found = true;
    m_found_value = value;
    m_found_solution = std::move(centre);
  
  }

  m_mutex.unlock();

  return true;
}

//=============================================================================
std::unique_ptr<ISimplex> Solver::getSimplex(const Point & a_p1, const Point & a_p2, const Point & a_p3) const
//
//
//
{
    return std::unique_ptr<SimplexTriple>(
        new SimplexTriple(
            m_objective_function,
            a_p1, a_p2, a_p3
        )
    );
}

//=============================================================================
bool Solver::solve(
  bool            a_multithreading,
  double          a_tolerance,
  Point& a_output,
  double&         a_value
)
//
//
//
{
  /*if (nullptr == a_output)
    return false;
*/
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

  auto* point = dynamic_cast<Point*>(m_found_solution.get());
  a_output = *point;
  a_value = m_found_value;

  return true;
}

//=============================================================================