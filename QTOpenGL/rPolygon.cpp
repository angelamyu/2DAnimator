#include "rPolygon.h"
#include "gMatrix3.h"
#include "gVector3.h"
#include "math.h"
#include "Square.h"
#define PI atan(1.0f)*4.0f

rPolygon::rPolygon(){
	num = NULL; 
	points = NULL;
	colors = new gVector3[3];
	indices = NULL;
	empty = true; //"empty" rPolygon because all values null
	numInt = 0; 
	colorVector = gVector3(); 
}

rPolygon::rPolygon(int s, gVector3 co){
	num = s;
	numInt = s; 
	colorVector = co; 
	points = new gVector3[s];
	colors = new gVector3[s];
	indices = new unsigned short[(s-2)*3];
	empty = false; //not "empty rPolygon because values are not null

	for(int a = 0; a < s; a++){
		points[a] = gVector3(100.0*cos(float(a)/float(s)*2.0f*PI), 100.0*sin(float(a)/float(s)*2.0f*PI), 1);
	}
	for(int b = 0; b < s; b++){
		colors[b] = co;
	}
	for(int i = 0; i < s-2; i++) {
		indices[i*3] = 0;
		indices[i*3 + 1] = i + 1;
		indices[i*3 + 2] = i + 2;
	}
}

rPolygon::~rPolygon(){
	delete[] colors;
	delete[] points;
	delete[] indices;
}

float* rPolygon::getPoints(){
	float* returnP = new float[num*3];

	for (int i = 0; i < num; i++) {
		returnP[3*i] = points[i][0];
		returnP[3*i + 1] = points[i][1];
		returnP[3*i + 2] = points[i][2];
	}

	return returnP;
}
	
float* rPolygon::getColors(){
	float* returnC = new float[num*3];

	for (int i = 0; i < num; i++) {
		returnC[3*i] = colors[i][0];
		returnC[3*i + 1] = colors[i][1];
		returnC[3*i + 2] = colors[i][2];
	}

	return returnC;
}
	
unsigned short* rPolygon::getIndices(){
	return indices;
}


bool rPolygon::checkEmptyPolygon(){
	return empty; 
}

unsigned int rPolygon::getSides(){
	return num; 
}

gVector3* rPolygon::getPointsVector(){
	return points;
}

gVector3* rPolygon::getColorsVector(){
	return colors;
}


void rPolygon::setRed(float r){
	for(int b = 0; b < num; b++){
		colors[b][0] = r;
	}
	colorVector[0] = r; 
}

void rPolygon::setGreen(float g){
	for(int b = 0; b < num; b++){
		colors[b][1] = g;
	}
	colorVector[1] = g; 
}

void rPolygon::setBlue(float u){
	for(int b = 0; b < num; b++){
		colors[b][2] = u;
	}
	colorVector[2] = u; 
}

float rPolygon::getRed(){
	return	colors[0][0];
}

float rPolygon::getGreen(){
	return	colors[0][1];
}

float rPolygon::getBlue(){
	return	colors[0][2];
}

rPolygon* rPolygon::copy(){
	rPolygon* p; 
	if(numInt==0){
		p = new rPolygon(); 
	}
	else {
		p = new rPolygon(numInt,colorVector);
		if(numInt==4){
			p = new Square(colorVector); 
		}
	}
	return p; 
}