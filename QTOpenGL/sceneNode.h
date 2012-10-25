#ifndef SCENENODE_H
#define SCENENODE_H

#include "gMatrix3.h"
#include "gVector3.h"
#include "rPolygon.h"
#include <vector>
#include <QTreeWidgetItem>

using namespace std;

class sceneNode: public QTreeWidgetItem{

private: 
	gMatrix3 transfM; 
	vector<gMatrix3> transfMatrix;
	rPolygon *geometry;
	/*float translateX; 
	float translateY; 
	float rotation; 
	float scaleX; 
	float scaleY; 
	float rotPointX; 
	float rotPointY; */
public:
	float translateX; 
	float translateY; 
	float rotation; 
	float scaleX; 
	float scaleY; 
	float rotPointX; 
	float rotPointY;
	QString name;
	sceneNode();
	sceneNode(gMatrix3 tm, vector<sceneNode*> c, rPolygon* g);
	~sceneNode(void);
	gMatrix3 getTransfMatrixCalculated();
	rPolygon* getGeometry();
	vector<sceneNode*> getChildren();
	void setGeometry(rPolygon* p);
	void setChildren(vector<sceneNode*> c);
	bool hasChildren();
	bool hasGeometry();
	void setTranslateX(float x);
	void setTranslateY(float y); 
	void setRotation(float r); 
	void setScaleX(float sx); 
	void setScaleY(float sy);
	void setRotPointX(float rpx); 
	void setRotPointY(float rpy); 
	void setColor(float,float,float);
	float getTranslateX();
	float getTranslateY(); 
	float getRotation(); 
	float getScaleX(); 
	float getScaleY();
	float getRotPointX(); 
	float getRotPointY(); 
	void addTranslateX(float x);
	void addTranslateY(float y); 
	void addRotation(float r); 
	void addScaleX(float sx); 
	void addScaleY(float sy);
	void deleteNode(sceneNode* sn);
	void resetNode(); 
	vector<sceneNode*> children;
	sceneNode* parentOfDeleted; 
	sceneNode* copy();
	void addAnotherChild(sceneNode*);
	bool keyFrameCheck; 
	void setBlack(sceneNode*);
};

#endif