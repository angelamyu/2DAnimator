#ifndef QTFRAMEBOOK_H
#define QTFRAMEBOOK_H

#include "qtframe.h"
#include "sceneNode.h"
#include "rPolygon.h"
#include "Square.h"
#include <qtablewidget.h>
#include <qtimer.h>

class qtFrameBook: public QTableWidget{
	Q_OBJECT
private: 
	QWidget* framebook; 
	int currentColumn; 
	sceneNode* currentRoot; 
	bool removeFlag; 
	int numBetweenKF; 
	int remainder; 
	int totalNum; 
	int position; 
	int playCounter; 
	bool remainderFlag; 
	int endFrameCounter; 
	int betweenFrameCounter; 
	bool playing; 
	int speed; 
	int nlspeed; 
	bool nonlinearFlag; 
public:
	typedef QTableWidget super; 
	qtFrameBook();
	qtFrameBook(QWidget*);
	sceneNode* interpolateTwo(sceneNode* s1, sceneNode* s3, sceneNode* copy); 
	sceneNode* interpolateMany(sceneNode* s1, sceneNode* s3, sceneNode* copy, float i,float j); 
	void traverseFramesForAdded(sceneNode* root, QString pName, sceneNode* toAdd);
	sceneNode* interpolate(sceneNode* a ,sceneNode* b, float num,float it); 
	QTimer* qtimer;
public slots:
	void getFrame(QImage,sceneNode*);
	void getCurrentFrame(int,int);
	void removeFrame();
	void getEditFrame(QImage,sceneNode*); 
	void getFrameBehind(QImage,sceneNode*); 
	void getFrameBefore(QImage,sceneNode*);
	void receiveInterpolatedQImage(QImage,sceneNode*,int); 
	void receiveAddedNode(int,QString,QString);
	void receivedSpecificEditQImage(QImage,int,sceneNode*);
	void receiveNumberBatchAdd(QString); 
	void play();
	void getFrameType(int,int); 
	void setAnimatedFramesNumber(int); 
	void receiveAnimationSliderPosition(int); 
	void doAddOneKeyFrame(QImage,sceneNode*);
	void update(); 
	void updateNL(); 
	void pause(); 
	void stop(); 
	void getUserSpeed(int);
	void nonlinearPlay(); 
	void fadeIn(); 
	void fadeOut(); 
signals:
	void sendCurrentFrame(sceneNode*); 
	void sendInterpolatedCopy(sceneNode*,sceneNode*,int); 
	void sendEditSpecificFrame(int,sceneNode*); 
	void printFrame(QString); 
	void setFrameTypeText(QString); 
	void changeSliderRange(int); 
	void sendSetValue(int);
};

#endif