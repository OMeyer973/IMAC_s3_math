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

int main()
{
  const unsigned int dimension = 10;
  Eigen::VectorXf v1 = Eigen::VectorXf::Random(dimension);
  std::cout << "v1 : " << v1.transpose() << std::endl;
  Eigen::VectorXf v2 = Eigen::VectorXf::Random(dimension);
  std::cout << "v2 : " << v2.transpose() << std::endl;

  float result = dotProduct(v1, v2);

  std::cout << "v1 * v2 " << result << std::endl;
  std::cout << "v1 * v2 " << v1.dot(v2) << std::endl;

  return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ tp2_ex3.cpp -o tp2_ex3 && ./tp2_ex3

