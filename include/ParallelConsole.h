#pragma once

#include <iostream>
#include <sstream>

// Forward Declarations
class ParallelConsole;

class ParallelConsole
{
public:
  ParallelConsole() : _tid(0) {}

  void setThread(int tid) { _tid = tid; }

  template <typename T>
  ParallelConsole & operator<<(const T & t)
  {
    if (_tid == 0)
      std::cout << t;
    return *this;
  }

  // this is the type of std::cout
  typedef std::basic_ostream<char, std::char_traits<char>> CoutType;

  // this is the function signature of std::endl
  typedef CoutType & (*StandardEndLine)(CoutType &);

  // define an operator<< to take in std::endl
  ParallelConsole & operator<<(StandardEndLine manip)
  {
    if (_tid == 0)
      manip(std::cout);
    return *this;
  }

protected:
private:
  int _tid;
};
