
#pragma once

#include "stdafx.h"
#include "Point.h"
#include <memory>
#include <mutex>
#include <functional>
#include <algorithm>
#include <assert.h>

static double alfa() { return 1.0; }
static double gamma() { return 2.0; }
static double rho()  { return -0.5; }
static double sigma() { return 0.5; }



class SimplexTriple
{
public:

  SimplexTriple(
    std::function<double(double, double)> obj_function,
    const Point& a_p1, 
    const Point& a_p2, 
    const Point& a_p3
  );

  const Point& minimum() const;
  const Point& middle() const;
  const Point& maximum() const;

  const double minimum_value() const;
  const double middle_value() const;
  const double maximum_value() const;

  void replace_maximum(const Point& a_new_point);

  Point get_centroid();
  Point get_gravity_centre() const;

  Point reflection();
  Point expansion();
  Point contraction();

  void reduce();
  
  double value_in_point(const Point& a) const;

  double get_deviation() const;

private:

  void did_change();

  void calculate_centroid() const;
  void order() const;
  void calculate_deviation() const;

  Point general_move(double a_coef);

private:
  
  std::function<double(double, double)> m_objective_function;

  Point m_1, m_2, m_3;

  mutable const Point * m_p_min;
  mutable const Point * m_p_mid;
  mutable const Point * m_p_max;

  mutable bool m_b_points_ordered;
  mutable bool m_b_centroid_calculated;
  mutable bool m_b_deviation_calculated;
  
  mutable std::unique_ptr<Point> m_p_centroid;

  mutable double m_deviation;

  mutable std::mutex m_mutex;
};