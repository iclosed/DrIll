#include "Circle.h"

Circle::Circle(){this->r = 5.0;}
Circle::Circle(double r){this->r = r;}
double Circle::Area(){return 3.1415 * r * r;}
