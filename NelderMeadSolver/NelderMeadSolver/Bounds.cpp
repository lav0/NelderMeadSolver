#include "stdafx.h"
#include "Bounds.h"

//=============================================================================
Bounds::Bounds(double xmin, double xmax, double ymin, double ymax)
    : m_xmin(xmin), m_xmax(xmax), m_ymin(ymin), m_ymax(ymax)
//
//
//
{
  m_b_defined = (m_xmin <= m_xmax) && (m_ymin <= m_ymax);
}

//=============================================================================
double Bounds::middle_x() const 
//
//
//
{ 
  return 0.5 * (m_xmin + m_xmax); 
}
//=============================================================================
double Bounds::middle_y() const
//
//
// 
{ 
  return 0.5 * (m_ymin + m_ymax); 
}

//=============================================================================
bool Bounds::check(Point& a_p) const
//
//
//
{
  double& x = a_p.X;
  double& y = a_p.Y;

  if (x < m_xmin)
      x = m_xmin;
        
  if (x > m_xmax)
      x = m_xmax;
    
  if (y < m_ymin)
      y = m_ymin;
        
  if (y > m_ymax)
      y = m_ymax;

  return true;
}

//=============================================================================
bool Bounds::is_defined() const
//
//
//
{
  return m_b_defined;
}

//=============================================================================
bool Bounds::build_triangle_on_area(
  eArea a_area, 
  Point& a_p1, 
  Point& a_p2, 
  Point& a_p3
) const
//
//
//
{
  if (!m_b_defined) 
    return false;

  double w = m_xmax - m_xmin;
  double h = m_ymax - m_ymin;

  Point sw_corner(m_xmin, m_ymin);
  Point centr(w / 4, h / 4);
  
  double a = w / 8;
  double b = h / 8;

  if (a_area == eArea::CENTRAL) {
    
    a = w / 4;
    b = h / 4;
    
    centr.X = w / 2;
    centr.Y = h / 2;

  } else if (a_area == eArea::SE) {
    
    centr.X += w / 2;

  } else if (a_area == eArea::NE) {
    
    centr.X += w / 2;
    centr.Y += h / 2;

  } else if (a_area == eArea::NW) {
    
    centr.Y += h / 2;
  }
  
  auto ellipse = [&a, &b](double angle) 
  {
    return Point(a * cos(angle), b * sin(angle));
  };

  a_p1 = sw_corner + centr + ellipse(0);
  a_p2 = sw_corner + centr + ellipse(2 * M_PI / 3);
  a_p3 = sw_corner + centr + ellipse(4 * M_PI / 3);

  return true;
}

//=============================================================================