#include "Character.h"
using namespace std;

Character::Character(){
	//transformation matrices
	gMatrix3 n0TM = gMatrix3().identity();
	gMatrix3 headTM = gMatrix3().identity();
	gMatrix3 leftEarTM= gMatrix3().identity();
	gMatrix3 rightEarTM= gMatrix3().identity();
	gMatrix3 bodyTM= gMatrix3().identity();
	gMatrix3 rightFrontLegTM= gMatrix3().identity();
	gMatrix3 rightFrontPawTM= gMatrix3().identity();
	gMatrix3 leftFrontPawTM= gMatrix3().identity();
	gMatrix3 leftFrontLegTM= gMatrix3().identity();
	gMatrix3 rightHindLegTM= gMatrix3().identity();
	gMatrix3 rightHindPawTM= gMatrix3().identity();
	gMatrix3 leftHindLegTM= gMatrix3().identity();
	gMatrix3 leftHindPawTM= gMatrix3().identity();
	gMatrix3 wholeHeadTM = gMatrix3().identity();
	gMatrix3 rightFrontLimbTM = gMatrix3().identity();
	gMatrix3 leftFrontLimbTM = gMatrix3().identity();
	gMatrix3 rightHindLimbTM = gMatrix3().identity();
	gMatrix3 leftHindLimbTM = gMatrix3().identity();

	//children vectors of sceneNode*
	vector<sceneNode*> n0C;
	vector<sceneNode*> headC;
	vector<sceneNode*> leftEarC;
	vector<sceneNode*> rightEarC;
	vector<sceneNode*> bodyC;
	vector<sceneNode*> rightFrontLegC;
	vector<sceneNode*> rightFrontPawC;
	vector<sceneNode*> leftFrontPawC;
	vector<sceneNode*> leftFrontLegC;
	vector<sceneNode*> rightHindLegC;
	vector<sceneNode*> rightHindPawC;
	vector<sceneNode*> leftHindLegC;
	vector<sceneNode*> leftHindPawC;
	vector<sceneNode*> wholeHeadC;
	vector<sceneNode*> rightFrontLimbC;
	vector<sceneNode*> leftFrontLimbC;
	vector<sceneNode*> rightHindLimbC;
	vector<sceneNode*> leftHindLimbC;

	//geometry for each node
	rPolygon* n0P = new rPolygon();
	rPolygon* headP = new Circle(gVector3(1,0,0)); 
	rPolygon* rightEarP = new Triangle(gVector3(1, 0, 0));
	rPolygon* leftEarP = new Triangle(gVector3(1, 0, 0));
	rPolygon* bodyP = new Circle(gVector3(1,0,0));
	rPolygon* rightFrontLegP = new Square(gVector3(1,1,0.7));
	rPolygon* rightFrontPawP = new rPolygon(5, gVector3(1,1,0.7));
	rPolygon* leftFrontLegP = new Square(gVector3(1,1,0.7)); 
	rPolygon* leftFrontPawP = new rPolygon(5, gVector3(1,1,0.7));
	rPolygon* rightHindLegP = new Circle(gVector3(3, 0.5, 0));
	rPolygon* rightHindPawP = new rPolygon(5, gVector3(3,0.5,0));
	rPolygon* leftHindLegP = new Circle(gVector3(3,0.5,0));
	rPolygon* leftHindPawP = new rPolygon(5, gVector3(3,0.5,0));
	rPolygon* wholeHeadP = new rPolygon();
	rPolygon* rightFrontLimbP = new rPolygon();
	rPolygon* leftFrontLimbP = new rPolygon();
	rPolygon* rightHindLimbP = new rPolygon();
	rPolygon* leftHindLimbP = new rPolygon();

	//creating sceneNodes, naming them, and pushing other nodes into children vectors to create character
	sceneNode* leftHindPawN = new sceneNode(leftHindPawTM, leftHindPawC, leftHindPawP);
	leftHindPawN->name = "left hind paw";
	sceneNode* leftHindLegN = new sceneNode(leftHindLegTM, leftHindLegC, leftHindLegP);
	leftHindLegN->name = "left hind leg"; 
	leftHindLimbC.push_back(leftHindLegN);
	leftHindLimbC.push_back(leftHindPawN);
	sceneNode* leftHindLimbN = new sceneNode(leftHindLimbTM, leftHindLimbC, leftHindLimbP);
	leftHindLimbN->name = "left hind limb";

	sceneNode* rightHindPawN = new sceneNode(rightHindPawTM, rightHindPawC, rightHindPawP);
	rightHindPawN->name = "right hind paw";
	sceneNode* rightHindLegN = new sceneNode(rightHindLegTM, rightHindLegC, rightHindLegP);
	rightHindLegN->name = "right hind leg";

	rightHindLimbC.push_back(rightHindLegN);
	rightHindLimbC.push_back(rightHindPawN);
	sceneNode* rightHindLimbN = new sceneNode(rightHindLimbTM, rightHindLimbC, rightHindLimbP);
	rightHindLimbN->name = "right hind limb";

	sceneNode* leftFrontPawN = new sceneNode(leftFrontPawTM, leftFrontPawC, leftFrontPawP);
	leftFrontPawN->name = "left front paw";
	sceneNode* leftFrontLegN = new sceneNode(leftFrontLegTM, leftFrontLegC, leftFrontLegP);
	leftFrontLegN->name = "left front leg"; 

	leftFrontLimbC.push_back(leftFrontLegN);
	leftFrontLimbC.push_back(leftFrontPawN);
	sceneNode* leftFrontLimbN = new sceneNode(leftFrontLimbTM, leftFrontLimbC, leftFrontLimbP);
	leftFrontLimbN->name = "left front limb";


	sceneNode* rightFrontPawN = new sceneNode(rightFrontPawTM, rightFrontPawC, rightFrontPawP);
	rightFrontPawN->name = "right front paw";
	sceneNode* rightFrontLegN = new sceneNode(rightFrontLegTM, rightFrontLegC, rightFrontLegP);
	rightFrontLegN->name = "right front leg";

	rightFrontLimbC.push_back(rightFrontLegN);
	rightFrontLimbC.push_back(rightFrontPawN);
	sceneNode* rightFrontLimbN = new sceneNode(rightFrontLimbTM, rightFrontLimbC, rightFrontLimbP);
	rightFrontLimbN->name = "right front limb";

	sceneNode* bodyN = new sceneNode(bodyTM, bodyC, bodyP);
	bodyN->name = "body"; 

	sceneNode* leftEarN = new sceneNode(leftEarTM, leftEarC, leftEarP);
	leftEarN->name = "left ear"; 
	sceneNode* rightEarN = new sceneNode(rightEarTM, rightEarC, rightEarP);
	rightEarN->name = "right ear";
	sceneNode* headN = new sceneNode(headTM, headC, headP);
	headN->name = "head";

	wholeHeadC.push_back(leftEarN);
	wholeHeadC.push_back(rightEarN);
	wholeHeadC.push_back(headN);
	sceneNode* wholeHeadN = new sceneNode(wholeHeadTM, wholeHeadC, wholeHeadP);
	wholeHeadN->name = "whole head"; 

	n0C.push_back(leftHindLimbN);
	n0C.push_back(rightHindLimbN);
	n0C.push_back(wholeHeadN);
	n0C.push_back(bodyN);
	n0C.push_back(leftFrontLimbN);
	n0C.push_back(rightFrontLimbN);
	sceneNode* n0 = new sceneNode(n0TM, n0C, n0P);
	n0->name = "root";

	//change each transformation matrix to make character look good
	bodyN->setScaleY(1.5);
	wholeHeadN->setTranslateY(200);
	leftEarN->setTranslateX(-80);
	leftEarN->setTranslateY(77);
	leftEarN->setScaleX(0.4);
	leftEarN->setScaleY(0.4);
	leftEarN->setRotation(11);
	rightEarN->setTranslateX(80);
	rightEarN->setTranslateY(77);
	rightEarN->setScaleX(0.4);
	rightEarN->setScaleY(0.4);
	rightEarN->setRotation(48);
	
	leftFrontLegN->setScaleX(2.5);
	leftFrontLegN->setScaleY(0.3);
	leftFrontLegN->setRotation(90);
	leftFrontLimbN->setTranslateX(-50);
	leftFrontLimbN->setTranslateY(-50);
	leftFrontPawN->setScaleX(0.47);
	leftFrontPawN->setScaleY(0.47);
	leftFrontPawN->setRotation(34);
	leftFrontPawN->setTranslateX(-23);
	leftFrontPawN->setTranslateY(-100);
	rightFrontLegN->setScaleX(2.5);
	rightFrontLegN->setScaleY(0.3);
	rightFrontLegN->setRotation(90);
	rightFrontLimbN->setTranslateX(50);
	rightFrontLimbN->setTranslateY(-50);
	rightFrontPawN->setScaleX(0.47);
	rightFrontPawN->setScaleY(0.47);
	rightFrontPawN->setRotation(0);
	rightFrontPawN->setTranslateX(23);
	rightFrontPawN->setTranslateY(-100);


	rightHindLegN->setScaleX(0.8);
	rightHindLegN->setScaleY(0.8);
	rightHindLimbN->setTranslateX(30);
	rightHindLimbN->setTranslateY(-60);
	rightHindPawN->setScaleX(0.4);
	rightHindPawN->setScaleY(0.4);
	rightHindPawN->setRotation(-10);
	rightHindPawN->setTranslateX(85);
	rightHindPawN->setTranslateY(-50);


	leftHindLegN->setScaleX(0.8);
	leftHindLegN->setScaleY(0.8);
	leftHindLimbN->setTranslateX(-30);
	leftHindLimbN->setTranslateY(-60);
	leftHindPawN->setScaleX(0.4);
	leftHindPawN->setScaleY(0.4);
	leftHindPawN->setRotation(-10);
	leftHindPawN->setTranslateX(-85);
	leftHindPawN->setTranslateY(-50);
	//leftHindPawN->setRotPointX(30); 
	//leftHindPawN->setRotPointX(60); 

	//set root
	root = n0;
}

Character::Character(sceneNode* r){
	root = r; 
}

Character::~Character(){
	delete root; 
}

sceneNode* Character::getRoot(){
	return root; 
}

void Character::setRoot(sceneNode* s){
	root = s; 
}

