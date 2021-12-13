#include <iostream>
#include "sample_mod.h"

MyCircle::MyCircle(double r){this->r = r;}
double MyCircle::Area(){
	return 3.1415 * r * r;
}

double mysqrt(double x) {
	if (x <= 0) {
		return 0;
	}
	double result = x;
	// do ten iterations
	for (int i = 0; i < 10; ++i) {
		if (result <= 0) {
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
	}
	return result;
}
