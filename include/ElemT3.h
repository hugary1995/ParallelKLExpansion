#pragma once

#include "Elem.h"

// Forward Declarations
class ElemT3;

class ElemT3 : public Elem
{
public:
  ElemT3(unsigned int domain, unsigned int id, std::vector<Node *> nodes)
    : Elem(domain, id, ElemType::T3, nodes)
  {
  }
};
