#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
#include "FEProblem.h"
#include "Mesh.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage ./KLExpansion input.yml" << std::endl;
    return -1;
  }

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // // create FEProblem on each processor
  // FEProblem KL;
  //
  // KL.assembleSparse();
  //
  // Node * n1 = new Node(1, 1.5, 2.5);
  // std::cout << *n1 << std::endl;
  //
  // Node * n2 = new Node(2, 3.3, 4.2);
  // std::cout << *n2 << std::endl;
  //
  // Node * n3 = new Node(3, 3.5, -5.9);
  // std::cout << *n3 << std::endl;
  //
  // ElemB2 * e1 = new ElemB2(0, 1, {n1, n2});
  // std::cout << *e1 << std::endl;
  //
  // ElemT3 * e2 = new ElemT3(0, 1, {n1, n2, n3});
  // std::cout << *e2 << std::endl;
  //
  // Eigen::GeneralizedEigenSolver<Eigen::Matrix3d> ges;
  // Eigen::Matrix3d A;
  // A(0, 0) = 1.2204;
  // A(1, 0) = 1.1123;
  // A(2, 0) = -3.8935;
  // A(0, 1) = 1.1123;
  // A(1, 1) = 3.5821;
  // A(2, 1) = -3.3333;
  // A(0, 2) = -3.8935;
  // A(1, 2) = -3.3333;
  // A(2, 2) = 19.6174;
  // Eigen::Matrix3d B;
  // B(0, 0) = 8.2380;
  // B(1, 0) = -3.7587;
  // B(2, 0) = 8.6182;
  // B(0, 1) = -3.7587;
  // B(1, 1) = 1.8416;
  // B(2, 1) = -4.3268;
  // B(0, 2) = 8.6182;
  // B(1, 2) = -4.3268;
  // B(2, 2) = 11.9408;
  // ges.compute(A, B);
  // std::cout << "The (complex) generalzied eigenvalues are: " << ges.eigenvalues().transpose()
  //           << std::endl;

  // Mesh * mesh = new Mesh("mesh.msh");
  //
  // for (Elem * e : mesh->active_elems())
  // printf("Elem %d on processor %d\n", e->id(), mesh->tid());
  // mesh->printDomainMapping();
  // mesh->printNodes();
  // mesh->printElements();

  FEProblem test(argv[1]);

  // Finalize the MPI environment.
  MPI_Finalize();

  return 0;
}
