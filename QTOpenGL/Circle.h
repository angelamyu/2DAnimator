#ifndef CIRCLE
#define CIRCLE

#include "gMatrix3.h"
#include "gVector3.h"
#include "rPolygon.h"

class Circle:public rPolygon{

public:
	Circle(gVector3& c);
	~Circle(void);
};

#endif