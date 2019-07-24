#pragma once

#include <Eigen/Sparse>
#include "yaml-cpp/yaml.h"
#include "ParallelBase.h"
#include "Mesh.h"

typedef Eigen::SparseMatrix<double> SpMat;

// Forward Declarations
class FEProblem;

class FEProblem : public ParallelBase
{
public:
  FEProblem(const std::string);

  Mesh * mesh() { return _mesh; }

  void assembleSparse();

protected:
private:
  void sendSparseEigen(const Eigen::Ref<const SpMat, Eigen::StandardCompressedFormat> & mat);
  void receiveSparseEigen(SpMat & out, int rank);

  Mesh * _mesh;

  SpMat _parallel_matrix;
  SpMat _transfer_matrix;
  SpMat _reduced_matrix;
};
