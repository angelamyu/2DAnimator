#ifndef CHARACTER_H
#define CHARACTER_H

#include "sceneNode.h"
#include "gMatrix3.h"
#include "rPolygon.h"
#include "Triangle.h"
#include "Circle.h"
#include "Square.h"

class Character{
private: 
	
public:
	Character();
	Character(sceneNode* r);
	~Character(void);
	sceneNode* getRoot();
	void setRoot(sceneNode* s);
	sceneNode* root;
	//void setBlack(sceneNode*r); 
};
#endif 