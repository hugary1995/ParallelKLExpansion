#include <Eigen/Sparse>
#include "FEProblem.h"

FEProblem::FEProblem(const std::string input) : ParallelBase()
{
  YAML::Node config = YAML::LoadFile(input);
  if (config["mesh"])
    std::cout << "Mesh file name: \033[1;34m" << config["mesh"].as<std::string>() << "\033[0m"
              << std::endl;
  else
    std::cout << "\033[1;31mMissing mesh.\033[0m" << std::endl;
  _mesh = new Mesh(config["mesh"].as<std::string>());

  _parallel_matrix.resize(3, 3);
  _transfer_matrix.resize(3, 3);
  _reduced_matrix.resize(3, 3);
}

void
FEProblem::assembleSparse()
{
  _parallel_matrix.setZero();
  _parallel_matrix.data().squeeze();
  _parallel_matrix.insert(0, 0) = _tid + 1.0;
  _parallel_matrix.insert(0, 2) = _tid - 5.3;
  _parallel_matrix.insert(2, 0) = _tid - 5.3;
  _parallel_matrix.insert(1, 2) = _tid + 2.1;
  _parallel_matrix.insert(2, 1) = _tid + 2.1;

  printf("Processr %d: \n[%.3f, %.3f, %.3f\n %.3f, %.3f, %.3f\n %.3f, %.3f, %.3f]\n",
         _tid,
         _parallel_matrix.coeff(0, 0),
         _parallel_matrix.coeff(0, 1),
         _parallel_matrix.coeff(0, 2),
         _parallel_matrix.coeff(1, 0),
         _parallel_matrix.coeff(1, 1),
         _parallel_matrix.coeff(1, 2),
         _parallel_matrix.coeff(2, 0),
         _parallel_matrix.coeff(2, 1),
         _parallel_matrix.coeff(2, 2));

  if (_tid == 0)
  {
    _reduced_matrix += _parallel_matrix;
    for (int rank = 1; rank < _mpi_size; rank++)
    {
      receiveSparseEigen(_transfer_matrix, rank);
      _reduced_matrix += _transfer_matrix;
    }
  }
  else
    sendSparseEigen(_parallel_matrix);

  if (_tid == 0)
    printf("Reduced Matrix: \n[%.3f, %.3f, %.3f\n %.3f, %.3f, %.3f\n %.3f, %.3f, %.3f]\n",
           _reduced_matrix.coeff(0, 0),
           _reduced_matrix.coeff(0, 1),
           _reduced_matrix.coeff(0, 2),
           _reduced_matrix.coeff(1, 0),
           _reduced_matrix.coeff(1, 1),
           _reduced_matrix.coeff(1, 2),
           _reduced_matrix.coeff(2, 0),
           _reduced_matrix.coeff(2, 1),
           _reduced_matrix.coeff(2, 2));
}

void
FEProblem::sendSparseEigen(const Eigen::Ref<const SpMat, Eigen::StandardCompressedFormat> & mat)
{
  Eigen::Index cols = mat.cols(), nnz = mat.nonZeros();
  Eigen::Index shape[2] = {cols, nnz};
  MPI_Send(shape, 2, MPI_LONG, 0, 0, MPI_COMM_WORLD);
  MPI_Send(mat.valuePtr(), nnz, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  MPI_Send(mat.innerIndexPtr(), nnz, MPI_LONG, 0, 2, MPI_COMM_WORLD);
  MPI_Send(mat.outerIndexPtr(), cols, MPI_LONG, 0, 3, MPI_COMM_WORLD);
}

void
FEProblem::receiveSparseEigen(SpMat & out, int rank)
{
  Eigen::Index shape[2];
  MPI_Recv(shape, 2, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  Eigen::Index cols = shape[0], nnz = shape[1];
  out.setZero();
  out.data().squeeze();
  out.reserve(9);
  MPI_Recv(out.valuePtr(), nnz, MPI_DOUBLE, rank, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(out.innerIndexPtr(), nnz, MPI_LONG, rank, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(out.outerIndexPtr(), cols, MPI_LONG, rank, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  out.outerIndexPtr()[cols] = nnz;
}
