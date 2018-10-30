#include <iostream>
#include <Eigen/Dense>
#include <ctime>

//compil : g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex5.cpp -o tp2_ex5 && ./tp2_ex5


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

Eigen::MatrixXf strassenProduct(const Eigen::MatrixXf &A, const Eigen::MatrixXf &B) {
  //matrices are of size 2^n
  //C = A * B , A, B, C are matrixes
  assert (A.cols() % 2 == 0 && 
          A.cols() == A.rows() && 
          A.cols() == B.rows() && 
          B.rows() == B.rows() && "A cols != B rows"); 

  const unsigned int n = A.cols();

  if (n < 128) {
    return matrixProduct(A,B);
  }

  Eigen::MatrixXf C = Eigen::MatrixXf::Zero(A.rows(), B.cols());
  
  Eigen::MatrixXf a = A.topLeftCorner(n/2, n/2);
  Eigen::MatrixXf b = A.topRightCorner(n/2, n/2);
  Eigen::MatrixXf c = A.bottomLeftCorner(n/2, n/2);
  Eigen::MatrixXf d = A.bottomRightCorner(n/2, n/2);
  
  Eigen::MatrixXf e = B.topLeftCorner(n/2, n/2);
  Eigen::MatrixXf f = B.topRightCorner(n/2, n/2);
  Eigen::MatrixXf g = B.bottomLeftCorner(n/2, n/2);
  Eigen::MatrixXf h = B.bottomRightCorner(n/2, n/2);

  Eigen::MatrixXf P1 = strassenProduct(a, f-h);
  Eigen::MatrixXf P2 = strassenProduct(a+b, h);
  Eigen::MatrixXf P3 = strassenProduct(c+d, e);
  Eigen::MatrixXf P4 = strassenProduct(d, g-e);
  Eigen::MatrixXf P5 = strassenProduct(a+d, e+h);
  Eigen::MatrixXf P6 = strassenProduct(b-d, g+h);
  Eigen::MatrixXf P7 = strassenProduct(a-c, e+f);

  C.topLeftCorner(n/2, n/2) = P5 + P4 - P2 + P6;
  C.topRightCorner(n/2, n/2) = P1 + P2;
  C.bottomLeftCorner(n/2, n/2) = P3 + P4;
  C.bottomRightCorner(n/2, n/2) = P1 + P5 - P3 - P7;
  
  return C;
}

int main()
{
  const unsigned int dim1 = 1024;
  const unsigned int dim2 = 1024;
  const unsigned int dim3 = 1024;
  Eigen::setNbThreads(4);
  Eigen::MatrixXf A = Eigen::MatrixXf::Random(dim1,dim2);  
  //std::cout << "A :\n" << A << std::endl << std::endl;

  Eigen::MatrixXf B = Eigen::MatrixXf::Random(dim2,dim3); 
  //std::cout << "B :\n" << B << std::endl << std::endl;

  Eigen::MatrixXf C(dim1, dim3);
  Eigen::MatrixXf D(dim1, dim3);
  Eigen::MatrixXf E(dim1, dim3);

  clock_t begin = clock();

  C = matrixProduct(A,B);

  clock_t end = clock();
  double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "temps calcul du produit matriciel standard: " <<tempsCalc <<"s " << std::endl;  
  //std::cout << "A * B :\n" << C << std::endl << std::endl;

  begin = clock();

  D = strassenProduct(A,B);

  end = clock();
  tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "temps calcul du produit matriciel strassen: " <<tempsCalc <<"s " << std::endl;
  //std::cout << "A * B :\n" << D << std::endl << std::endl;

  begin = clock();

  E = A*B;

  end = clock();
  tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "temps calcul du produit matriciel eigen: " <<tempsCalc <<"s " << std::endl;
  //std::cout << "A * B :\n" << D << std::endl << std::endl;


  std::cout << "standard numerical check: " << (C-E).norm() << std::endl;
  std::cout << "strassen numerical check: " << (D-E).norm() << std::endl;


  return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && ./tp2_ex4
//multithread
// g++ -Wall -O2 -fopenmp -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && OMP_NUM_THREADS=4 ./tp2_ex4

