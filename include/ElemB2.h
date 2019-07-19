#pragma once

#include "Elem.h"

// Forward Declarations
class ElemB2;

class ElemB2 : public Elem
{
public:
  ElemB2(unsigned int domain, unsigned int id, std::vector<Node *> nodes)
    : Elem(domain, id, ElemType::B2, nodes)
  {
  }
};
