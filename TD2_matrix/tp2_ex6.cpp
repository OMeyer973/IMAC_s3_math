#include <iostream>
#include <Eigen/Dense>
#include <ctime>

//compil : g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex5.cpp -o tp2_ex5 && ./tp2_ex5


int main()
{
  const unsigned int dim1 = 4;
  const unsigned int dim2 = 4;
  const unsigned int dim3 = 4;

  Eigen::MatrixXf P = Eigen::MatrixXf::identity(dim1,dim2);  
  //std::cout << "A :\n" << A << std::endl << std::endl;

  P.rows(1).swap(P.rows(3));

  return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && ./tp2_ex4
//multithread
// g++ -Wall -O2 -fopenmp -I /usr/include/eigen3/ tp2_ex4.cpp -o tp2_ex4 && OMP_NUM_THREADS=4 ./tp2_ex4

