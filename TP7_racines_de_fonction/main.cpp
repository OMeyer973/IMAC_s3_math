#include <iostream>
#include "Point3D.hpp"



int main(int argc, char const *argv[]) {

	// 1.1 
	// methode naive : parcourir la fonction interval par interval

	// soit a < b des reels
	// soit f fonction continue sur [a,b] / f(a) * f(b)
	// soit p 	//le pas de recherche 
	// reel naif (fonction f,borne inf a,borne sup b,reel p)
	//     soit dx = (b-a)/p
	//     soit xprev = a
	//     soit x = a + dx
 	//     tant que x < b :
 	//         si x * xprev < 0
 	// 		       retourne (x+xprev)/2
	// 	       xprev = x
	// 	       x += dx
	//    retourne PAS_DE_ZERO

	// 2.
	// methode newton : très efficace pour des courbes proche de la linéarité
	// mais pb de divergence ou de rester coincer 
	// -> qq étapes de dichotomie et polish avec newton 

	return 0;
}



