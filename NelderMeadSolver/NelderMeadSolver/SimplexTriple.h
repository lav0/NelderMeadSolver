
#pragma once

#include "stdafx.h"
#include "Point.h"
#include "Bounds.h"
#include "ISimplex.h"
#include <memory>
#include <mutex>
#include <functional>
#include <algorithm>
#include <assert.h>



class SimplexTriple : public ISimplex
{
public:

  SimplexTriple(
    std::function<double(const VariableSetPtr&)> obj_function,
    const Point& a_p1, 
    const Point& a_p2, 
    const Point& a_p3
  );

  ~SimplexTriple() override {}

  void setBounds(const Bounds& bounds) { m_bounds = bounds; }

  const Point& minimum() const;
  const Point& middle() const;
  const Point& maximum() const;

  const double minimum_value() const override;
  const double middle_value() const override;
  const double maximum_value() const override;

  void replace_maximum(const VariableSetPtr& a_new_point) override;

  Point get_centroid();
  VariableSetPtr get_gravity_centre() const override;
  VariableSetPtr start_position() const override;

  VariableSetPtr reflection() override;
  VariableSetPtr expansion() override;
  VariableSetPtr contraction() override;

  void shrink() override;
  
  double value_in_point(const VariableSetPtr& a) const override;
  double value_in_point(const Point& p) const;

  double get_deviation() const override;

private:

  void did_change();

  void calculate_centroid() const;
  void order() const;
  void calculate_deviation() const;

  Point general_move(double a_coef);

private:
  
  std::function<double(const VariableSetPtr&)> m_objective;

  Point m_1, m_2, m_3;

  Bounds m_bounds;

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