#pragma once

namespace nmsolver
{
  class ValueWrapperDouble
  {
  public:
    explicit ValueWrapperDouble(double a) : d_(a) {}
    ValueWrapperDouble(const ValueWrapperDouble& other) : d_(other.d_) {}
    ValueWrapperDouble& operator=(const ValueWrapperDouble& other)
    {
      d_ = other.d_;
      return *this;
    }

    const double get() const { return d_; }
    void set(const double& a) { d_ = a; }

  private:
    double d_ = 0.0;
  };

}