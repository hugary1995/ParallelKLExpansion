#pragma once

#include <vector>
#include "Type.h"
#include "Node.h"

// Forward Declarations
class Elem;

class Elem
{
public:
  Elem(unsigned int domain, unsigned int id, ElemType type, std::vector<Node *> nodes)
    : _domain(domain), _id(id), _type(type), _nodes(nodes)
  {
  }

  unsigned int domain() { return _domain; }
  unsigned int id() { return _id; }
  std::vector<Node *> nodes() { return _nodes; }

  unsigned int domain() const { return _domain; }
  unsigned int id() const { return _id; }
  std::vector<Node *> nodes() const { return _nodes; }

  friend std::ostream & operator<<(std::ostream & console, const Elem & e);

protected:
  unsigned int _domain;
  unsigned int _id;
  ElemType _type;
  std::vector<Node *> _nodes;
};

inline std::ostream &
operator<<(std::ostream & os, const Elem & e)
{
  os << "Element #" << e.id() << " on Domain #" << e.domain() << ": {";
  std::vector<Node *> nodes = e.nodes();
  for (unsigned int i = 0; i < nodes.size() - 1; i++)
    os << *nodes[i] << ", ";
  os << *nodes[nodes.size() - 1] << "}";
  return os;
}
