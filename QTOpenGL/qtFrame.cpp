#include "qtFrame.h"


qtFrame::qtFrame(QImage qi, sceneNode* sn){
	root = sn; 
	qimage = qi; 
	qimage = qimage.scaledToWidth(110);
	qimage = qimage.scaledToHeight(90);
	setPixmap(QPixmap::fromImage(qimage));
	after= NULL; 
	before= NULL; 
}

/*void qtFrame::setBefore(sceneNode* b){
	before = b; 
}
	
void qtFrame::setAfter(sceneNode* a){
	after = a; 
}
	
sceneNode* qtFrame::getBefore(){
	return before; 
}
	
sceneNode* qtFrame::getAfter(){
	return after; 
}
*/