#include <iostream>
#include <Eigen/Dense>

double evalPolynomial(const Eigen::VectorXd &p, const double &x) {
 
	double result = 0;
	double x_tmp = 1;

	for(unsigned int i=0; i<p.size(); ++i) {
		result += p[i] * x_tmp;
		x_tmp *= x;
	}
 
	return result;
}


Eigen::VectorXd polynomialFromRoots(const Eigen::VectorXd &r) {
	/*
	//marche paaaas
	Eigen::VectorXd p = Eigen::VectorXd::Zero(r.size()+1);

	p[r.size()] = 1;

	// meme chose avec la boucle dans l'autre sens

	for(unsigned int i=1; i<=r.size(); ++i) {
	    p[r.size()-i] = -r[i-1] * p[r.size()-i+1];
	}

	// for(unsigned int i=r.size(); i>=1; --i) {
	// 	p[i-1] = -r[r.size()-i] * p[i];
	// }
 	*/

	//solution
	Eigen::VectorXd p = Eigen::VectorXd::Ones(r.size()+1);

	p[0] = -r(0);

	for(unsigned int i=1; i<r.size(); ++i) {
		for(unsigned int j=i; j>0; --j) {
		    p[j] = p[j-1] - r[i] * p[j];
		}
		p[0] *= -r[i];
	}

	return p;
}


int main() {
	Eigen::VectorXd r = Eigen::VectorXd::Zero(3);
	r[0] = 2;
	r[1] = 3;
	r[2] = 4;
 
	Eigen::VectorXd p = polynomialFromRoots(r);

	std::cout << "p : " << p.transpose() << std::endl;
	
	std::cout << "p(-2) : " << evalPolynomial(p,-2) << std::endl;
	std::cout << "p(-1) : " << evalPolynomial(p,-1) << std::endl;
	std::cout << "p(0) : " << evalPolynomial(p,0) << std::endl;
	std::cout << "p(1) : " << evalPolynomial(p,1) << std::endl;
	std::cout << "p(2) : " << evalPolynomial(p,2) << std::endl;

	return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ main.cpp -o main && ./main

