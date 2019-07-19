#pragma once

#include <mpi.h>
#include "ParallelConsole.h"

// Forward Declarations
class ParallelBase;

class ParallelBase
{
public:
  ParallelBase()
  {
    MPI_Comm_rank(MPI_COMM_WORLD, &_tid);
    MPI_Comm_size(MPI_COMM_WORLD, &_mpi_size);
    _console.setThread(_tid);
  }

protected:
  int _tid;
  int _mpi_size;
  ParallelConsole _console;

private:
};
