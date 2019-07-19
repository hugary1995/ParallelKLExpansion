#pragma once

#include "Point.h"

// Forward Declarations
class Node;

class Node : public Point
{
public:
  Node() {}
  Node(unsigned int id, double x, double y) : Point(x, y), _id(id) {}
  Node(const Node & other) : Point(other), _id(other._id) {}

  Node & operator=(const Node & other)
  {
    // check for self-assignment
    if (&other == this)
      return *this;
    _id = other._id;
    _x = other._x;
    _y = other._y;
    return *this;
  }

  double id() { return _id; }
  double id() const { return _id; }

  friend std::ostream & operator<<(std::ostream & console, const Node & p);

private:
  unsigned int _id;
};

inline std::ostream &
operator<<(std::ostream & os, const Node & n)
{
  os << "Node #" << n.id() << ": ";
  os << '(' << n.x() << ", " << n.y() << ')';
  return os;
}
