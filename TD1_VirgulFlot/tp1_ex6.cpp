#include <iostream>

int russianMult(unsigned int x, unsigned int y) {
  
  unsigned int a = 0;
  unsigned int b = 0;
  unsigned int r = 0;

  if (x < y) {
      a = x;
      b = y;
  } else {
    a = y;
    b = x;
  }

  while (a > 1) {
    if (a & 1) {
      //a impair
      r += b;
    }
    a = a >> 1;
    b = b << 1;
  }

  return r + b;

} 

int main()
{
  unsigned int uInputA = 0; 
  unsigned int uInputB = 0; 
  std::cin >> uInputA;
	std::cin >> uInputB;

  std::cout << uInputA << " * "
            << uInputB << " = " 
            << russianMult(uInputA, uInputB) << std::endl;
    

      
  return 0;
}
