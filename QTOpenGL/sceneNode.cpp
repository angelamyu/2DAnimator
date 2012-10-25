#include "sceneNode.h"
//#include <qDebug>
#include "gMatrix3.h"
#include "gVector3.h"
#include "math.h"
#define PI atan(1.0f)*4.0f

using namespace std;

sceneNode::sceneNode(){
	geometry = new rPolygon();
	translateX = 0; 
	translateY = 0; 
	scaleX = 1; 
	scaleY = 1; 
	rotation = 0; 
	transfM = gMatrix3().identity();
	rotPointX = 0; 
	rotPointY = 0; 
	keyFrameCheck = false; 
}
sceneNode::sceneNode(gMatrix3 tm, vector<sceneNode*> c, rPolygon* g){
	transfM = tm; 
	children = c; 
	geometry = g; 
	translateX = 0; 
	translateY = 0; 
	scaleX = 1; 
	scaleY = 1; 
	rotation = 0; 
	rotPointX = 0; 
	rotPointY = 0; 
	keyFrameCheck = false; 
}


sceneNode::~sceneNode(){
	delete geometry;
}


rPolygon* sceneNode::getGeometry(){
	return geometry;
}

vector<sceneNode*> sceneNode::getChildren(){
	return children;
}

void sceneNode::setGeometry(rPolygon* p){
	geometry = p; 
}
	
void sceneNode::setChildren(vector<sceneNode*> c){
	children = c; 
}

void sceneNode::setColor(float r,float g,float b){
	geometry->setRed(r); 
	geometry->setGreen(g); 
	geometry->setBlue(b); 
}
bool sceneNode::hasChildren(){
	return !children.empty();
}

bool sceneNode::hasGeometry(){
	return !geometry->checkEmptyPolygon();
}

gMatrix3 sceneNode::getTransfMatrixCalculated(){
	//gMatrix3 calc = gMatrix3().translation2D(translateX, translateY)*  gMatrix3().rotation2D(rotation)*  gMatrix3().scale2D(scaleX, scaleY);
	gMatrix3 calc = gMatrix3().translation2D(rotPointX, rotPointY)* gMatrix3().translation2D(translateX, translateY)*  gMatrix3().rotation2D(rotation)*  
		gMatrix3().scale2D(scaleX, scaleY)*gMatrix3().translation2D(-rotPointX, -rotPointY) ;
	//gMatrix3 calc = gMatrix3().rotation2D(rotation)*  gMatrix3().scale2D(scaleX, scaleY) * gMatrix3().translation2D(translateX, translateY);
	return calc; 
}

void sceneNode::setTranslateX(float x){
	translateX = x; 
}

void sceneNode::setTranslateY(float y){
	translateY = y; 
}

void sceneNode::setRotation(float r){
	rotation = r; 
}

void sceneNode::setScaleX(float sx){
	scaleX = sx; 
}

void sceneNode::setScaleY(float sy){
	scaleY = sy; 
}

void sceneNode::setRotPointX(float rpx){
	rotPointX = rpx; 
}

void sceneNode::setRotPointY(float rpy){
	rotPointY = rpy; 
}

float sceneNode::getTranslateX(){
	return translateX; 
}
	
float sceneNode::getTranslateY(){
	return translateY; 
}
	
float sceneNode::getRotation(){
	return rotation; 
}
	
float sceneNode::getScaleX(){
	return scaleX; 
}
	
float sceneNode::getScaleY(){
	return scaleY; 
}

float sceneNode::getRotPointX(){
	return rotPointX; 
}

float sceneNode::getRotPointY(){
	return rotPointY; 
}

void sceneNode::addTranslateX(float x){
	translateX = translateX + x;
}

void sceneNode::addTranslateY(float y){
	translateY = translateY + y;
}


void sceneNode::addRotation(float r){
	rotation = rotation +r; 
}

void sceneNode::addScaleX(float sx){
	scaleX = scaleX*sx; 
}

void sceneNode::addScaleY(float sy){
	scaleY = scaleY*sy; 
}


void sceneNode::deleteNode(sceneNode* sn){
	if(hasChildren() == true){
		vector<sceneNode*> c = getChildren();
		vector<sceneNode*>::iterator it;
		vector<sceneNode*> ret; 
		for ( it=c.begin() ; it < c.end(); it++ ){
			sceneNode* temp = *it; 
			if(sn==*it)
			{ 
				removeChild(sn);
				vector<sceneNode*>::iterator it2; 
				for(it2 = c.begin(); it2< c.end(); it2++)
				{
					sceneNode* ugh = *it2; 
					if(ugh != sn){
						ret.push_back(ugh);
					}
				}
				setChildren(ret);
				break;
			}
			else{
				(temp)->deleteNode(sn);
			}
		}
	}
}


void sceneNode::resetNode(){
	geometry = new rPolygon();
	translateX = 0; 
	translateY = 0; 
	scaleX = 1; 
	scaleY = 1; 
	rotation = 0; 
	transfM = gMatrix3().identity();
	vector<sceneNode*> s; 
	children = s; 
}


sceneNode* sceneNode::copy(){
	rPolygon* g = geometry->copy(); 
	gMatrix3 tm = transfM;
	vector<sceneNode*> c;
	vector<sceneNode*>::iterator it;
	for(it = children.begin(); it< children.end(); it++)
	{
		sceneNode* ugh = (*it)->copy(); 
		c.push_back(ugh);
	}
	sceneNode* cpy = new sceneNode(transfM, c, g);
	cpy->setTranslateX(translateX); 
	cpy->setTranslateY(translateY); 
	cpy->setScaleX(scaleX); 
	cpy->setScaleY(scaleY); 
	cpy->setRotation(rotation); 
	cpy->name=name; 
	cpy->keyFrameCheck=keyFrameCheck; 
	return cpy;
}

void sceneNode::addAnotherChild(sceneNode* a){
	children.push_back(a); 
}

void sceneNode::setBlack(sceneNode* root){
	if(root->hasGeometry() == true){
		root->setColor(0,0,0); 
	}
	if(root->hasChildren() == true){
		vector<sceneNode*> c = root->getChildren();
		vector<sceneNode*>::iterator it;
		for ( it=c.begin() ; it < c.end(); it++ ){
			sceneNode* temp = *it;
			setBlack(temp);
		}
	}
}