#ifndef SQUARE
#define SQUARE

#include "gMatrix3.h"
#include "gVector3.h"
#include "rPolygon.h"

class Square: public rPolygon{
public:
	Square(gVector3& c);
	~Square(void);
};

#endif