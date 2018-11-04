#pragma once

#include "stdafx.h"
#include "VariableSet.h"
#include <functional>

//struct Point
//{
//  Point(double a_x, double a_y);
//
//  double X;
//  double Y;
//};

struct Point : public IVariableSet
{
    ~Point() override {};
    Point(double a_x, double a_y);
    Point(const Point& a) : Point(a.X, a.Y) {}
    Point(const VariableSet<2>& a) : Point(a.values_[0], a.values_[1]) {}
    Point& operator=(const Point& p) {
        X = p.X;
        Y = p.Y;
        return *this; 
    }

    size_t size() const override { return 2; }
    virtual double getVar(size_t index) const override {
      return index == 0 ? X : Y;
    }

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
