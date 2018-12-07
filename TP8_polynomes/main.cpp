#include <iostream>
#include <cmath>
#include <Eigen/Dense>


// g++ -Wall -O2 -I /usr/include/eigen3/ main.cpp -o main && ./main


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

Eigen::VectorXd crudeSolvePolynomialRoots(const Eigen::VectorXd &p, uint iter) {
	
	// 0/ normaliser p (a_n = 1 et pr ts i<n a_i = a_i / a_n)

	// 1/ construire la matrice compagnon :
	
	// 0 0 0 -a_0
	// 1 0 0 -a_1
	// 0 1 0 -a_2
	// ...
	// 0 0 1 -a_n-1

	// loop {
	// 		2/ décomposer la matrice C en QR

	// 		3/ répéter C = R*Q
	// end loop

	// C converge vers une matrice diagonale qui a les racines de 
	// p sur la diagonale

	double a_n = p[p.size()-1];
	Eigen::VectorXd q = p / -a_n;

	Eigen::MatrixXd C = Eigen::MatrixXd(p.size()-1, p.size()-1);
	C.bottomLeftCorner(C.rows()-1, C.cols()-1).setIdentity();
	C.rightCols(1) = q.head(q.size()-1);
	
	/*	
	//same as the 3 eigen lines above
	for (uint i=0; i<C.rows(); ++i) {
		
		if (i+1 < C.rows())
			C(i+1, i) = 1;
		
		C(i, C.rows()-1) = q(i);

	}
	*/

	//std::cout << std::endl << C << std::endl;
	
	for (uint i=0; i<iter; ++i) {
		Eigen::HouseholderQR<Eigen::MatrixXd>qr(C);
		Eigen::MatrixXd Q = qr.householderQ();
		Eigen::MatrixXd R = qr.matrixQR().triangularView<Eigen::Upper>();
		C = R*Q;
	}	
	return C.diagonal();
}

Eigen::VectorXd derivatePolynomial(const Eigen::VectorXd &p){
	Eigen::VectorXd q = Eigen::VectorXd(p.size()-1);
	for (uint i=0; i<q.size(); ++i) {
		q(i) = (i+1)*p(i+1);
	}
	return q;
}

Eigen::VectorXd solvePolynomialRoots(const Eigen::VectorXd &p, uint iter) {
	Eigen::VectorXd p2 = derivatePolynomial(p);
	Eigen::VectorXd r = crudeSolvePolynomialRoots(p, iter);
	for (uint a=0; a<r.size(); ++a) {
		//if (std::abs(evalPolynomial(p, r[a])) > 0.0001)
			//methode de newton
			for (uint i=0; i<iter; ++i) {
				r[a] = r[a] - evalPolynomial(p, r[a]) / evalPolynomial(p2, r[a]);
			}
	}
	return r;
}

int main() {
	Eigen::VectorXd r = Eigen::VectorXd::Zero(5);
	r[0] = 1;
	r[1] = 2;
	r[2] = 2;
	r[3] = 4;
	r[4] = 5;
 
	Eigen::VectorXd p = polynomialFromRoots(r);

	std::cout << "p : " << p.transpose() << std::endl;
	
	// std::cout << "p(-2) : " << evalPolynomial(p,-2) << std::endl;
	// std::cout << "p(-1) : " << evalPolynomial(p,-1) << std::endl;
	// std::cout << "p(0) : " << evalPolynomial(p,0) << std::endl;
	// std::cout << "p(1) : " << evalPolynomial(p,1) << std::endl;
	// std::cout << "p(2) : " << evalPolynomial(p,2) << std::endl;

	//std::cout << "p' : " << crudeSolvePolynomialRoots(p, 10).transpose() << std::endl;
	std::cout << "p' : " << derivatePolynomial(p).transpose() << std::endl;
	std::cout << "racines sans newton : " << crudeSolvePolynomialRoots(p, 30).transpose() << std::endl;
	std::cout << "racines avec newton : " << solvePolynomialRoots(p, 30).transpose() << std::endl;
	//newton donne des résultats chelou
	

	return 0;
}

// g++ -Wall -O2 -I /usr/include/eigen3/ main.cpp -o main && ./main

