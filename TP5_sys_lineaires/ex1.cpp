#include <iostream>
#include <Eigen/Dense>
#include <ctime>



Eigen::VectorXd GS(Eigen::MatrixXd A, Eigen::VectorXd b, const int iterations) {
  VectorXd x = b;
  for (int iter=0; iter<iterations; ++iter) {
    for (int i=0; i<A.rows(); ++i) {
      x[i] = b[i];
      for (int j=0; j<A.cols(); ++iter) {
        if (i != j) x[i] = A[i][j] * x[i];
      }
      x[i] /= A[i][i];
    }
  }
  return x;
}


int main()
{
  int matrixSize = 50;
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(matrixSize, matrixSize);	
  std::cout << "A :\n" << A << std::endl << std::endl;

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(matrixSize, matrixSize);	
  std::cout << "B :\n" << B << std::endl << std::endl;

  Eigen::MatrixXd C(matrixSize, matrixSize);
  
  clock_t begin = clock();
  C=A*B;
  clock_t end = clock();
  double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  

  std::cout << "temps calcul du produit matriciel: " <<tempsCalc <<"s " << std::endl;
  std::cout << "A + 2*A :\n" << A + 2*A << std::endl << std::endl;
  std::cout << "A * B :\n" << A * B << std::endl << std::endl;

  return 0;
}



// g++ -Wall -I ~/eigen/  eigenSample.cpp 
