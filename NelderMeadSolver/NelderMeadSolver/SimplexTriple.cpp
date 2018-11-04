#include "stdafx.h"
#include "SimplexTriple.h"



//=============================================================================
//
//=============================================================================


//=============================================================================
SimplexTriple::SimplexTriple(  
  std::function<double(const VariableSetPtr&)> obj_function,
  const Point& a_p1, 
  const Point& a_p2, 
  const Point& a_p3
):  
  m_objective(obj_function),
  m_1(a_p1), m_2(a_p2), m_3(a_p3), 
  m_bounds(0,0,0,0),
  m_b_points_ordered(false), 
  m_b_centroid_calculated(false), 
  m_b_deviation_calculated(false),
  m_p_min(nullptr), m_p_mid(nullptr), m_p_max(nullptr)
//
//
//
{
  order();
}
  
//=============================================================================
void SimplexTriple::did_change()
//
//
//
{
  m_b_points_ordered       = false;
  m_b_centroid_calculated  = false;
  m_b_deviation_calculated = false;
}
  
//=============================================================================
double SimplexTriple::value_in_point(const VariableSetPtr& vars) const
//
//
//
{
  return m_objective(vars);
}

//=============================================================================
double SimplexTriple::value_in_point(const Point& p) const
{
  auto vars = (VariableSetPtr) std::make_unique<Point>(p);
  return m_objective(vars);
}

//=============================================================================
const Point& SimplexTriple::minimum() const
//
//
//
{  
  order();

  return *m_p_min;
}
//=============================================================================
const Point& SimplexTriple::middle() const
//
//
//
{
  order();

  return *m_p_mid;
}
//=============================================================================
const Point& SimplexTriple::maximum() const
//
//
//
{
  order();

  return *m_p_max;
}


//=============================================================================
const double SimplexTriple::minimum_value() const
//
//
//
{
  return value_in_point(minimum());
}

//=============================================================================
const double SimplexTriple::middle_value()  const
//
//
//
{
  return value_in_point(middle());
}

//=============================================================================
const double SimplexTriple::maximum_value() const
//
//
//
{
  return value_in_point(maximum());
}

//=============================================================================
void SimplexTriple::replace_maximum(const VariableSetPtr& a_new_point)
//
//
//
{
  auto p = dynamic_cast<Point*>(a_new_point.get());
  auto t = const_cast<Point*>(m_p_max);
  *t = *p;

  did_change();
}


//=============================================================================
Point SimplexTriple::get_centroid()
//
//
//
{
  calculate_centroid();

  return *m_p_centroid;
}

//=============================================================================
void SimplexTriple::order() const
//
//
//
{
  if (m_b_points_ordered)
    return;

  double value1 = value_in_point(m_1);
  double value2 = value_in_point(m_2);
  double value3 = value_in_point(m_3);

  m_mutex.lock();

  if (value1 < value2) {

    if (value1 < value3) {
      m_p_min = &m_1;

      if (value2 < value3) {
        m_p_mid = &m_2;
        m_p_max = &m_3;
      } else {
        m_p_mid = &m_3;
        m_p_max = &m_2;
      }

    } else {
      m_p_min = &m_3;
      m_p_mid = &m_1;
      m_p_max = &m_2;
    }
  } else {

    if (value2 < value3) {
      m_p_min = &m_2;

      if (value1 < value3) {
        m_p_mid = &m_1;
        m_p_max = &m_3;
      } else {
        m_p_mid = &m_3;
        m_p_max = &m_1;
      }
    } else {
      m_p_min = &m_3;
      m_p_mid = &m_2;
      m_p_max = &m_1;
    }
  }

  m_b_points_ordered = true;

  m_mutex.unlock();

  return;
}

//=============================================================================
void SimplexTriple::calculate_centroid() const
//
//
//
{
  order();
  
  if (m_b_centroid_calculated) 
    return;

  double d_coef = 0.5;

  m_p_centroid.reset(new Point(d_coef * (*m_p_min + *m_p_mid)));

  m_b_centroid_calculated = true;
}

//=============================================================================
VariableSetPtr SimplexTriple::reflection()
//
//
//
{
  auto point = general_move(alfa());
  m_bounds.check(point);
  return std::make_unique<Point>(point);
}

//=============================================================================
VariableSetPtr SimplexTriple::expansion()
//
//
//
{
  auto point = general_move(gamma());
  m_bounds.check(point);
  return std::make_unique<Point>(point);
}

//=============================================================================
VariableSetPtr SimplexTriple::contraction()
//
//
//
{
  return std::make_unique<Point>(general_move(rho()));
}

//=============================================================================
void SimplexTriple::shrink()
//
// first - best point
// second - second after best...etc
//
{
  order();

  Point first  = *m_p_min;
  Point second = first + sigma() * (*m_p_mid - first);
  Point third  = first + sigma() * (*m_p_max - first);

  m_1 = first;
  m_2 = second;
  m_3 = third;

  did_change();
}

//=============================================================================
Point SimplexTriple::general_move(double a_coef)
//
//
//
{
  calculate_centroid();

  return *m_p_centroid + a_coef * (*m_p_centroid - *m_p_max); 
}

//=============================================================================
void SimplexTriple::calculate_deviation() const
//
//
//
{
  auto var = get_gravity_centre();
  Point centre(dynamic_cast<Point&>(*var));

  double dev1 = point_norm(centre - m_1);
  double dev2 = point_norm(centre - m_2);
  double dev3 = point_norm(centre - m_3);

  m_mutex.lock();

  m_deviation = std::max(dev1, std::max(dev2, dev3));
  m_b_deviation_calculated = true;
  
  m_mutex.unlock();
}

//=============================================================================
double SimplexTriple::get_deviation() const
//
//
//
{
  if (!m_b_deviation_calculated) 
  {
    calculate_deviation();
  }

  return m_deviation;
}

//=============================================================================
VariableSetPtr SimplexTriple::get_gravity_centre() const
//
//
//
{
  double coef = 1.0 / 3.0;
  return std::make_unique<Point>(coef * (m_1 + m_2 + m_3));
}

VariableSetPtr SimplexTriple::start_position() const
{
  return std::make_unique<Point>(m_bounds.middle_x(), m_bounds.middle_y());
}
