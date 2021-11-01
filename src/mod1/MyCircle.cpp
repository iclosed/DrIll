#include "MyCircle.h"

MyCircle::MyCircle(){this->r = 5.0;}
MyCircle::MyCircle(double r){this->r = r;}
double MyCircle::Area(){return 3.1415 * r * r;}
