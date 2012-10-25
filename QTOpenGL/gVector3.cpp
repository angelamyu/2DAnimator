#include "gVector3.h"
#include "assert.h"
#include <iostream>
using namespace std;

gVector3::gVector3()
{
	data[0] = 0;
	data[1] = 0; 
	data[2] = 1;
}


gVector3::gVector3(float x, float y, float z)
{
	data[0] = x; 
	data[1] = y;
	data[2] = z;
}

float gVector3::operator[](unsigned int index) const
{
	assert (index>=0 && index<=2);
	return data[index];
}

float& gVector3::operator[](unsigned int index)
{
	assert (index>=0 && index<=2);
	return data[index];
}

float gVector3::length() const
{
	float l = sqrt (pow(data[0],2) + pow(data[1],2) + + pow(data[2],2));
	return l;
}

bool gVector3::operator==(const gVector3& v2)
{
	if(fabs(data[0] - v2.data[0]) < 0.0000001 && fabs(data[1] - v2.data[1]) < 0.0000001 && 
		fabs(data[2] - v2.data[2]) < 0.0000001) {
		return true;
	}
	else{
		return false;
	}
}

bool gVector3::operator!=(const gVector3& v2)
{
	if(fabs(data[0] - v2.data[0]) > 0.0000001 || fabs(data[1] - v2.data[1]) > 0.0000001 || 
		fabs(data[2] - v2.data[2]) > 0.0000001) {
		return true;
	}
	else{
		return false;
	}
}

gVector3 gVector3::operator+(const gVector3& v2)
{
	gVector3 gv = gVector3(data[0] + v2.data[0], data[1] + v2.data[1], data[2] + v2.data[2]);
	return gv;
}

gVector3 gVector3::operator-(const gVector3& v2)
{
	gVector3 nv = gVector3(data[0] - v2.data[0], data[1] - v2.data[1], data[2] - v2.data[2]);
	return nv;
}

gVector3 gVector3::operator*(float c)
{
	gVector3 mv = gVector3(data[0]*c, data[1]*c, data[2]*c);
	return mv;
}

gVector3 operator*(float c, const gVector3& v)
{
	float v0 = v[0];
	float v1 = v[1]; 
	float v2 = v[2];
	gVector3 g = gVector3(c*v0, c*v1, c*v2);
	return g;
}

gVector3 gVector3::operator/(float c)
{
	assert(fabs(c-0) > 0.0000001);
	gVector3 dv = gVector3(data[0]/c, data[1]/c, data[2]/c);
	return dv; 
}

float gVector3::operator*(const gVector3& v2)
{
	float dp = (data[0]*v2.data[0] + data[1]*v2.data[1] + data[2]*v2.data[2]);
	return dp;
}

gVector3 gVector3::operator%(const gVector3& v2)
{
	gVector3 cp = gVector3(data[1]*v2.data[2] - data[2]*v2.data[1],data[2]*v2.data[0]- data[0]*v2.data[2], 
		data[0]*v2.data[1] - data[1]*v2.data[0]);
	return cp;
}

ostream &operator<<(ostream &stream, gVector3 v)
{

	stream << "<" << v[0] <<", " <<  v[1] <<", " <<  v[2] <<">" << endl;
	return stream;
}