#ifndef RPOLYGON_H
#define RPOLYGON_H

#include "gMatrix3.h"
#include "gVector3.h"

class rPolygon{

private: 
	gVector3* colors;
	unsigned short* indices;
	unsigned int num;
	int numInt; 
	bool empty; 
	gVector3 colorVector; 
public:
	rPolygon();
	rPolygon(int sides, gVector3 c);
	~rPolygon(void);
	float* getPoints();
	float* getColors();
	unsigned short* getIndices();
	gVector3* points;
	unsigned int getSides();
	bool checkEmptyPolygon();
	gVector3* getPointsVector();
	gVector3* getColorsVector();
	void setRed(float r);
	void setGreen(float g);
	void setBlue(float b);
	float getRed(); 
	float getGreen(); 
	float getBlue(); 
	rPolygon* copy(); 
};

#endif