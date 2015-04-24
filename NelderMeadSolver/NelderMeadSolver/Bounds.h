#include "stdafx.h"
#include "Point.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <functional>

enum class eArea
{
  CENTRAL = 0,
  SW      = 1,
  SE      = 2,
  NW      = 3,
  NE      = 4
};

class Bounds
{
public:

  Bounds(double xmin, double xmax, double ymin, double ymax);

  double middle_x() const;
  double middle_y() const;

  bool is_defined() const;
  bool build_triangle_on_area(eArea, Point& a_p1, Point& a_p2, Point& a_p3) const;
  bool check(Point& a_p) const;


private:

  bool m_b_defined;
  
  double m_xmin, m_xmax, m_ymin, m_ymax;

};
