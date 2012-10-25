#include "gMatrix3.h"
#include "assert.h"
#include <iostream>
using namespace std;

gMatrix3::gMatrix3()
{
	data[0] = gVector3(1,0,0);
	data[1] = gVector3(0,1,0);
	data[2] = gVector3(0,0,1);
}

gMatrix3::gMatrix3(const gVector3& row1, const gVector3& row2, const gVector3& row3)
{
	data[0] = row1;
	data[1] = row2; 
	data[2] = row3;
}

gVector3 gMatrix3::operator[](unsigned int index) const
{
	assert(index>=0 && index<=2);
	return data[index];
}

gVector3& gMatrix3::operator[](unsigned int index)
{
	assert(index>=0 && index<=2);
	return data[index];
}

gVector3 gMatrix3::getColumn(unsigned int index) const
{
	assert(index>=0 && index<=2);
	gVector3 c = gVector3(data[0][index], data[1][index], data[2][index]);
	return c;
}

gMatrix3 gMatrix3::transpose() const
{
	gMatrix3 tr = gMatrix3();
	for(int r = 0; r<=2; r++)
	{
		for(int c = 0; c<=2; c++)
		{
			tr.data[r][c] = data[c][r];
		}
	}
	return tr;
}

gMatrix3 gMatrix3::rotation2D(float angle)
{
	const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	//divide by two
	float rad = angle * PI / 180.0;
	float cosine = cos(rad);
	float sine = sin(rad); 
	if(abs(cosine - 0) < 0.0000001)
	{
		cosine = 0; 
	}
	if(abs(sine - 0) < 0.0000001)
	{
		sine = 0; 
	}
	gMatrix3 rt = gMatrix3(gVector3(cosine, -sine, 0), gVector3(sine, cosine, 0), gVector3(0,0,1));
	return rt;
}

gMatrix3 gMatrix3::translation2D(float x, float y)
{
	gMatrix3 tr = gMatrix3(gVector3(1,0,x), gVector3(0,1,y), gVector3(0,0,1));
	return tr;
}

gMatrix3 gMatrix3::scale2D(float x, float y)
{
	gMatrix3 sc = gMatrix3(gVector3(x,0,0), gVector3(0,y,0), gVector3(0,0,1));
	return sc;
}

gMatrix3 gMatrix3::identity()
{
	gMatrix3 i = gMatrix3(gVector3(1,0,0), gVector3(0,1,0), gVector3(0,0,1));
	return i;
}

bool gMatrix3::operator==(const gMatrix3& m2)
{
	for(int r = 0; r<3 ; r++)
	{
		if(data[r] != m2[r])
		{
			return false;
		}
	}
	return true;
}

bool gMatrix3::operator!=(const gMatrix3& m2)
{
	bool b = false;
	for(int r = 0; r<3 ; r++)
	{
		if(data[r] != m2[r])
		{
			b = true;
		}
	}
	return b;
}

gMatrix3 gMatrix3::operator+(const gMatrix3& m2)
{
	gMatrix3 g = gMatrix3(data[0] + m2[0], data[1] + m2[1], data[2] + m2[2]);
	return g;
}

gMatrix3 gMatrix3::operator-(const gMatrix3& m2)
{
	gMatrix3 g = gMatrix3(data[0] - m2[0], data[1] - m2[1], data[2] - m2[2]);
	return g;
}

gMatrix3 gMatrix3::operator*(float c)
{
	gMatrix3 g = gMatrix3(data[0]*c, data[1]*c, data[2]*c);
	return g;
}

gMatrix3 operator*(float c, const gMatrix3& m)
{
	gVector3 row1 = m[0];
	gVector3 row2 = m[1];
	gVector3 row3 = m[2];
	gMatrix3 g = gMatrix3(c*row1, c*row2, c*row3);
	return g; 
}

gMatrix3 gMatrix3::operator/(float c)
{
	assert(fabs(c - 0) > 0.0000001);
	gMatrix3 g = gMatrix3(data[0]/c, data[1]/c, data[2]/c);
	return g;
}

gMatrix3 gMatrix3::operator*(const gMatrix3& m2)
{
	gMatrix3 a = gMatrix3();
	for(int i = 0; i <=2 ; i++)
	{
		for(int j = 0; j <=2; j++)
		{
			a[i][j] = data[i]*m2.getColumn(j);
		}
	}
	return a;
}

gVector3 gMatrix3::operator*(const gVector3& v)
{
	float x = data[0][0]*v[0]+ data[0][1]*v[1]+data[0][2]*v[2];
	float y = data[1][0]*v[0]+ data[1][1]*v[1]+data[1][2]*v[2];
	float z = data[2][0]*v[0]+ data[2][1]*v[1]+data[2][2]*v[2];
	gVector3 a = gVector3(x,y,z);
	return a;
}

gVector3 operator*(const gVector3& v, const gMatrix3& m)
{
	gVector3 vNew = gVector3(v[0],v[1],v[2]);
	gMatrix3 mNew = gMatrix3(m[0], m[1],m[2]);
	gVector3 ans = gVector3(vNew*mNew.getColumn(0), vNew*mNew.getColumn(1), vNew*mNew.getColumn(2));
	return ans;
}

ostream &operator<<(ostream &stream, gMatrix3 m)
{
	stream << "[" << endl << m[0] <<  m[1] <<  m[2] << "]" << endl;
	return stream;
}
