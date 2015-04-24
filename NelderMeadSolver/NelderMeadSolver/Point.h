#pragma once

#include "stdafx.h"



struct Point
{
  Point(double a_x, double a_y);

  double X;
  double Y;
};

//=============================================================================
Point operator+(const Point& a, const Point& b);


//=============================================================================
Point operator-(const Point& a, const Point& b);

//=============================================================================
Point operator*(const Point& a, double c);

//=============================================================================
Point operator*(double c, const Point& a);

double point_norm(const Point& a);
