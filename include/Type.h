#pragma once

#include <iostream>

typedef enum elemType
{
  B2,
  T3
} ElemType;

inline std::ostream &
operator<<(std::ostream & os, const ElemType & e)
{
  if (e == ElemType::B2)
    std::cout << "B2";
  if (e == ElemType::T3)
    std::cout << "T3";
  return os;
}
