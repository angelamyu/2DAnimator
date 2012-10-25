#include "Circle.h"
//#include <qDebug>
#include "gMatrix3.h"
#include "gVector3.h"
#include "math.h"
#define PI atan(1.0f)*4.0f

Circle::Circle(gVector3& c):rPolygon(100,c){

}

Circle::~Circle(){

}
