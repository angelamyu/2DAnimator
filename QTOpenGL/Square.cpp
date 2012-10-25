#include "Square.h"
#include "gMatrix3.h"
#include "gVector3.h"
#include "math.h"
#define PI atan(1.0f)*4.0f


Square::Square(gVector3& c):rPolygon(4,c){
	points[0] = gVector3(50,50,1);
	points[1] = gVector3(50,-50,1);
	points[2] = gVector3(-50, -50,1);
	points[3] = gVector3(-50,50,1);
}

Square::~Square(){
}


