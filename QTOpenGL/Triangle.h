#include "gMatrix3.h"
#include "gVector3.h"
#include "rPolygon.h"

class Triangle: public rPolygon{

private: 

public:
	Triangle(gVector3& c);
	~Triangle(void);
};