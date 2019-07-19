#pragma once

#include <iostream>

// Forward Declarations
class Point;

class Point
{
public:
  Point() {}
  Point(double x, double y) : _x(x), _y(y) {}
  Point(const Point & other) : _x(other._x), _y(other._y) {}

  Point & operator=(const Point & other)
  {
    // check for self-assignment
    if (&other == this)
      return *this;
    _x = other._x;
    _y = other._y;
    return *this;
  }

  double x() { return _x; }
  double y() { return _y; }

  double x() const { return _x; }
  double y() const { return _y; }

  friend std::ostream & operator<<(std::ostream & console, const Point & p);

protected:
  double _x;
  double _y;
};

inline std::ostream &
operator<<(std::ostream & os, const Point & p)
{
  os << '(' << p.x() << ", " << p.y() << ')';
  return os;
}
