#include <iostream>
#include <Eigen/Eigenvalues>

#include "ioEigen.hpp"

using namespace Eigen;


void hints(void){

  MatrixXd M;
  
  // compute the column wize mean of a data matrix
  VectorXd mean =  M.colwise().sum() / (double) M.rows(); 
  
  // some hints to center some data (with the exterior product)
  std::cout << VectorXd::Ones(M.rows())*mean.transpose() << std::endl;

  // compute some eigen vectors
  SelfAdjointEigenSolver<MatrixXd> eigensolver(M);
  std::cout << "\neigenvectors of M \n" << eigensolver.eigenvectors().rowwise().reverse() << std::endl;
  std::cout << "\neigenvalues of M : " << eigensolver.eigenvalues().colwise().reverse().transpose() << std::endl;
  
  // extract some rows or columns from a matrix
  std::cout << M.leftCols(3) << std::endl; 
  std::cout << M.topRows(3) << std::endl; 
	
}



int main(int argc, char **argv)
{
  if(argc != 2){
    std::cerr << "usage : " << argv[0] << " data.mat" << std::endl;
    exit(0);
  }
  
  // load the data
  MatrixXd A;
  loadMatrix(A,argv[1]);
  std::cout << "A\n" << A << std::endl;

  // mean of the data
  //moyenne sur les colones
  VectorXd mean = A.colwise().sum() / (double)A.rows();

  // center the data
  // chaque coef a = a - (moyenne de sa colonne)
  // astuce, on soustrait à A le produit d'une colonne de 1 et 
  // de la transposée du vecteur des moyennes des colones :
  // rend une matrice qui contient des copies du vecteur moyenne en ligne.
  // 
  // 1           a b c 
  // 1 * a b c = a b c 
  // 1           a b c

  MatrixXd Acentered = A - VectorXd::Ones(A.rows()) * mean.transpose();

  // normalize the data
  //calcule de la variance par colonne. on stocke les variances dans la diagonale d'une
  // matrice autrement remplie de zeros. on utilise cette matrice pour scale A
  MatrixXd scale = MatrixXd::Zero(A.cols(), A.cols());
  scale.diagonal() = Acentered.cwiseAbs().colwise().sum() / (double)Acentered.rows();
  scale = scale.inverse();

  MatrixXd Anormalized = Acentered * scale;

  // build the covariance matrix 
  MatrixXd cov = Anormalized.transpose() * Anormalized / (Anormalized.rows() -1);
  //ok

  // compute the eigen vectors
  SelfAdjointEigenSolver<MatrixXd> eigensolver(cov);
  
  std::cout << std::endl;
  std::cout << eigensolver.eigenvectors().rowwise().reverse() << std::endl;
  std::cout << std::endl;
  std::cout << eigensolver.eigenvectors().colwise().reverse().transpose() << std::endl;

  // keep only n dimensions
  int dimension = 3;
  MatrixXd T = eigensolver.eigenvectors().rowwise().reverse().leftCols(dimension);
  // project the data
  MatrixXd Afinal = Anormalized * T;

  // project a new vector (remind to center and scale this vector)
  VectorXd x (A.cols());
  x << 1, 3, 8, 0, 1;
  VectorXd xProj = (T.transpose() * scale * (x - mean)).transpose();
  VectorXd distance = (Afinal - VectorXd::Ones(Afinal.rows()) * xProj.transpose()).rowwise().norm();

  std::cout << distance << std::endl;
 
  return 0;
}
