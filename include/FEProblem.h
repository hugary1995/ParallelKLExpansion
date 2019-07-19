#pragma once

#include <Eigen/Sparse>
#include "ParallelBase.h"
#include "Mesh.h"

typedef Eigen::SparseMatrix<double> SpMat;

// Forward Declarations
class FEProblem;

class FEProblem : public ParallelBase
{
public:
  FEProblem() : ParallelBase()
  {
    _parallel_matrix.resize(3, 3);
    _transfer_matrix.resize(3, 3);
    _reduced_matrix.resize(3, 3);
  }

  void assembleSparse();

protected:
private:
  void sendSparseEigen(const Eigen::Ref<const SpMat, Eigen::StandardCompressedFormat> & mat);
  void receiveSparseEigen(SpMat & out, int rank);
  SpMat _parallel_matrix;
  SpMat _transfer_matrix;
  SpMat _reduced_matrix;
};
