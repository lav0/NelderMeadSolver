#include "stdafx.h"
#include "Point.h"

#include <math.h>

//=============================================================================
Point::Point(double a_x, double a_y) : X(a_x), Y(a_y) {}

std::unique_ptr<IVariableSet> Point::subtract(const IVariableSet * a) const
{
  auto p = dynamic_cast<const Point*>(a);
  return std::make_unique<Point>(*this - *p);
}
std::unique_ptr<IVariableSet> Point::add(const IVariableSet * a) const
{
  auto p = dynamic_cast<const Point*>(a);
  return std::make_unique<Point>(*this + *p);
}

//=============================================================================
Point operator+(const Point& a, const Point& b)
{
  return Point(a.X + b.X, a.Y + b.Y);
}

//=============================================================================
Point operator-(const Point& a, const Point& b)
{
  return Point(a.X - b.X, a.Y - b.Y);
}

//=============================================================================
Point operator*(const Point& a, double c)
{
  return Point(a.X * c, a.Y * c);
}

//=============================================================================
Point operator*(double c, const Point& a)
{
  return a * c;
}

double point_norm(const Point& a)
{
  return sqrt(a.X * a.X + a.Y * a.Y);
}

