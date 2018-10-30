#include <iostream>
#include <Eigen/Dense>
#include <ctime>

float dotProduct(const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) {
 
  assert (v1.size() == v2.size() && "v1 size != v2 rows"); 
  double result = 0; //pour plus de précision on passe par un double qu'on cast en float une fois que la somme est faite
 
  for(unsigned int i=0; i<v1.size(); i++) {
    result += v1[i] * v2[i];
  }
 
  return result;
}

Eigen::MatrixXf matrixProduct(const Eigen::MatrixXf &A, const Eigen::MatrixXf &B) {
  //C = A * B , A, B, C are matrixes
  assert (A.cols() == B.rows() && "A cols != B rows"); 

  Eigen::MatrixXf C = Eigen::MatrixXf::Zero(A.rows(), B.cols());
  //double tmp = 0; //pour plus de précision on passe par un double qu'on cast en float une fois que la somme est faite 
  for(unsigned int i=0; i<C.rows(); i++) {
    for(unsigned int j=0; j<C.cols(); j++) {
      C(i,j) = dotProduct(A.row(i), B.col(j));
      /*
      tmp = 0;
      
      for(unsigned int k=0; k< A.cols(); k++) {
        tmp += A(i,k) * B(k,j);
      }

      C(i,j) = (float)tmp;
      */
    }
  }
 
  return C;
}

int main()
{
  const unsigned int dim1 = 10;
  const unsigned int dim2 = 50000;
  const unsigned int dim3 = 10;
  Eigen::setNbThreads(4);
  Eigen::MatrixXf A = Eigen::MatrixXf::Random(dim1,dim2);  
  //std::cout << "A :\n" << A << std::endl << std::endl;

  Eigen::MatrixXf B = Eigen::MatrixXf::Random(dim2,dim3); 
  //std::cout << "B :\n" << B << std::endl << std::endl;

  Eigen::MatrixXf C(dim1, dim3);
  Eigen::MatrixXf D(dim1, dim3);

  clock_t begin = clock();

  C = matrixProduct(A,B);

  clock_t end = clock();
  double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "temps calcul du produit matriciel: " <<tempsCalc <<"s " << std::endl;  
  //std::cout << "A * B :\n" << C << std::endl << std::endl;

  begin = clock();

  D=A*B;

  end = clock();
  tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "temps calcul du produit matriciel Eigen: " <<tempsCalc <<"s " << std::endl;
  //std::cout << "A * B :\n" << D << std::endl << std::endl;

  std::cout << "numerical check: " << (C-D).norm() << std::endl;


  return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && ./tp2_ex4
//multithread
// g++ -Wall -O2 -fopenmp -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && OMP_NUM_THREADS=4 ./tp2_ex4

