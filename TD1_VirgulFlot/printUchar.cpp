#include <iostream>
#include <cstdlib>
#include <cmath>

void printUchar(const unsigned char x)
{
 	std::cout << (int ) x << " : ";
  
	for (int i=7; i>=0; i--) 
	{
		//décalage du bit qui nous intéresse tout à droite
		//et on l'identifie avec un le & 1 logique
		std::cout << (x >> i & 1);		
	}

  std::cout << std::endl;
}


int main(int argc, char **argv)
{
  if(argc != 2){
    std::cerr << "usage: " << argv[0] << " nb" << std::endl;
    return 0;
  }
  printUchar(atoi(argv[1]));

  return 1;
}
