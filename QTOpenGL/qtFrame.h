#ifndef QTFRAME_H
#define QTFRAME_H

#include <qlabel.h>
#include "sceneNode.h"
#include <QImage>


class qtFrame: public QLabel{

private: 
	
	QImage qimage; 
public:
	sceneNode* root; 
	qtFrame(QImage qi, sceneNode* sn);
	sceneNode* before; 
	sceneNode* after; 
	//void setBefore(sceneNode* b); 
	//void setAfter(sceneNode* a);
	//sceneNode* getBefore(); 
	//sceneNode* getAfter(); 
};

#endif