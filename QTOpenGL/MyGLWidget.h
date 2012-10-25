#ifndef MYGLWIDGET
#define MYGLWIDGET

#include "glew.h"
#include "gMatrix3.h"
#include "gVector3.h"
#include "rPolygon.h"
#include "Square.h"
#include "Circle.h"
#include "Character.h"
#include <sstream>
#include <QGLWidget>
#include <qmessagebox.h>

class MyGLWidget : public QGLWidget {
	Q_OBJECT
protected:
	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);
	void createSquare(gMatrix3 model);
	void createPolygon(gMatrix3 model, int sides, rPolygon& p);
	void traverse(sceneNode* root, gMatrix3 t);
	sceneNode* currentNode; 
	QString name; 
	int sides; 
	bool nameChanged; 
	bool sidesChanged; 
	void addNode();
public:
	MyGLWidget(QWidget*);
	~MyGLWidget(void);
public slots:
	void translateX(int);
	void translateY(int);
	void rotation(int);
	void scaleX(int);
	void scaleY(int);
	void red(int);
	void green(int);
	void blue(int);
	void resetCharacter();
	void setCurrentNode(QTreeWidgetItem* i ,int z);
	void deleteNode();
	void addNodeName(QString s);
	void addNodeSides(QString s);
	void addQTFrame();
	void makeQTFrameBehind();
	void makeQTFrameBefore();
	void editRepaint(sceneNode*);
	void makeInterpolatedQImage(sceneNode*,sceneNode*,int); 
	void makeEditSpecificQImage(int,sceneNode*); 
	
signals:
	void makeRoot(sceneNode*);
	void makeChild(sceneNode*, sceneNode*);
	void makeFrame(QImage,sceneNode*);
	void editFrame(QImage,sceneNode*);
	void makeFrameBehind(QImage,sceneNode*);
	void makeFrameBefore(QImage,sceneNode*);
	void sendInterpolatedQImage(QImage,sceneNode*,int);
	void sendAddedNodeToFrames(int,QString,QString);
	void sendEditSpecificQImage(QImage,int,sceneNode*);
	void printWidget(QString); 
	void addOneKeyFrame(QImage,sceneNode*);
	void setFrameText(QString); 
private:
	Character* cat;
	
	//vertex arrays needed for drawing
	unsigned int vbo;
	unsigned int cbo;
	unsigned int ibo;

	//attributes
	unsigned int positionLocation;
	unsigned int colorLocation;

	// uniforms
	unsigned int u_scr_widthLocation;
	unsigned int u_scr_heightLocation;
	unsigned int u_modelMatrixLocation;

	//needed to compile and link and use the shaders
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	//helper function to read shader source and put it in a char array
	//thanks to Swiftless
	char* textFileRead(const char*);

	//some other helper functions from CIS 565
	void printLinkInfoLog(int);
	void printShaderInfoLog(int);
};

#endif