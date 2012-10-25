#include "qtFrameBook.h"

qtFrameBook::qtFrameBook(){
	setColumnCount(0);
	setRowCount(1);
	setRowHeight(0,90); 
	removeFlag = false; 
	qtimer = new QTimer();
	numBetweenKF=0; 
	remainder = 0; 
	totalNum = 0; 
	position = 0; 
	playCounter = 0; 
	remainderFlag = true; 
	endFrameCounter = 0; 
	betweenFrameCounter = 0; 
	playing = false; 
	speed = 40; 
	nonlinearFlag = false; ; 
	nlspeed = 40; 
}

qtFrameBook::qtFrameBook(QWidget* f):QTableWidget(f){
	framebook = f; 
	setColumnCount(0);
	currentColumn = 0; 
	setRowCount(1);
	setRowHeight(0,90); 
	removeFlag = false; 
	qtimer = new QTimer();
	numBetweenKF=0; 
	remainder = 0; 
	totalNum = 0;
	position = 0; 
	playCounter = 0; 
	remainderFlag = true; 
	endFrameCounter = 0; 
	betweenFrameCounter = 0; 
	playing = false; 
	speed = 40; 
	nlspeed = 40; 
	nonlinearFlag = false; 
}

void qtFrameBook::getFrame(QImage q, sceneNode* sn){
	if(columnCount()==0){
		sn->keyFrameCheck=true; 
	qtFrame* frame = new qtFrame(q, sn);
	int colCount = columnCount(); 
	setColumnCount(columnCount()+1);
	setColumnWidth(columnCount()-1,110);
	setCellWidget(0, columnCount()-1, frame);
	currentColumn = columnCount(); 
	setAnimatedFramesNumber(totalNum);
	}
}

void qtFrameBook::getCurrentFrame(int row, int col){
	currentColumn = col; 
	currentRoot =  ((qtFrame*) cellWidget(row,col))->root;
	removeFlag = true; 
	emit sendCurrentFrame(currentRoot); 
	//emit sendSetValue(col*(numBetweenKF+1)); 
}

void qtFrameBook::removeFrame(){
	if(removeFlag){
		removeColumn(currentColumn);
		removeFlag = false; 
		setAnimatedFramesNumber(totalNum);
	}
}

void qtFrameBook::getEditFrame(QImage q, sceneNode* sn){
	//maybe switch keyFrameCheck?
	if(sn->keyFrameCheck==false){
		//emit printFrame(QString("before %1").arg(sn->keyFrameCheck));
		sn->keyFrameCheck=true;
		//HAVE TO ADD FRAME IN BUT NOT YET
		//HAVE TO RECALC M AND P
		int lower = (int) floor((float)(position-1) / (numBetweenKF+1));
		qtFrame* frame = new qtFrame(q, sn);
		insertColumn(lower+1);
		setCellWidget(0, lower+1, frame);
		currentColumn = 0; 
		position = 0; 
		//emit printFrame(QString("lower + 1 %1").arg(lower));
		//emit printFrame(QString("position %1").arg(position));
		//emit setFrameTypeText(QString("Frame")); 
		setAnimatedFramesNumber(totalNum);
	}
	else{
	qtFrame* frame = new qtFrame(q, sn);
	setColumnWidth(columnCount()-1,110);
	setCellWidget(0, currentColumn, frame);
	}
}

void qtFrameBook::doAddOneKeyFrame(QImage q, sceneNode* sn){
	//maybe switch keyFrameCheck?
	//if(sn->keyFrameCheck==false){
		emit printFrame(QString("before %1").arg(sn->keyFrameCheck));
		sn->keyFrameCheck=true;
		//HAVE TO ADD FRAME IN BUT NOT YET
		//HAVE TO RECALC M AND P
		int lower = (int) floor((float)(position-1) / (numBetweenKF+1));
		if(lower<columnCount()-1){
			
			qtFrame* frame = new qtFrame(q, sn);
			insertColumn(lower+1);
			setCellWidget(0, lower+1, frame);
			currentColumn = lower+1; 
			//position = 0; 
			//emit printFrame(QString("lower + 1 %1").arg(lower));
			//emit printFrame(QString("position %1").arg(position));
			emit setFrameTypeText(QString("KeyFrame")); 
			setAnimatedFramesNumber(totalNum);
		}
		else{
			qtFrame* frame = new qtFrame(q, sn);
		insertColumn(columnCount());
		setCellWidget(0, columnCount()-1, frame);
		currentColumn = columnCount()-1; 
		//position = 0; 
		setAnimatedFramesNumber(totalNum);
		}
	//}
}

void qtFrameBook::getFrameBehind(QImage q, sceneNode* sn){
	sceneNode* inter;
	if(columnCount() - currentColumn >1){
		sceneNode* temp = ((qtFrame*) cellWidget(0,currentColumn+1))->root; 
		//inter = interpolateTwo(sn, temp,sn->copy());
		inter = interpolate(sn,temp,2,1);
	}
	else{
		inter = sn->copy(); 
	}
	inter->keyFrameCheck=true; 
	emit sendInterpolatedCopy(inter,sn,1); 
	//setAnimatedFramesNumber(totalNum);
}

void qtFrameBook::receiveInterpolatedQImage(QImage q,sceneNode* inter,int i){
	qtFrame* frame = new qtFrame(q, inter);
	insertColumn(currentColumn+i);
	setCellWidget(0, currentColumn+i, frame);
	if(i==0){
		currentColumn = currentColumn+1; 
	}
	setAnimatedFramesNumber(totalNum);
}

void qtFrameBook::receivedSpecificEditQImage(QImage q,int i,sceneNode* edited){
	edited->keyFrameCheck=true;
	qtFrame* frame = new qtFrame(q, edited);
	setCellWidget(0, i, frame);
	//setAnimatedFramesNumber(totalNum);
}

void qtFrameBook::getFrameBefore(QImage q, sceneNode* sn){
	sceneNode* inter;
	if(currentColumn >=1){
		sceneNode* temp = ((qtFrame*) cellWidget(0,currentColumn-1))->root; 
		sceneNode* temp2; 
		//inter = interpolateTwo(temp,sn,sn->copy());


		//inter = interpolateTwo(sn,temp,temp2);
		inter = interpolate(sn,temp,2,1); 
	}
	else{
		inter = sn->copy(); 
	}
	inter->keyFrameCheck=true;
	emit sendInterpolatedCopy(inter,sn,0); 

}

sceneNode* qtFrameBook::interpolateTwo(sceneNode* s1, sceneNode* s2, sceneNode* copy){
	float tx = ((s1->getTranslateX()) + (s2->getTranslateX())) / 2.0;
	float ty = ((s1->getTranslateY()) + (s2->getTranslateY())) / 2.0;
	float ro = ((s1->getRotation()) + (s2->getRotation())) / 2.0;
	float sx = ((s1->getScaleX()) + (s2->getScaleX())) / 2.0;
	float sy = ((s1->getScaleY()) + (s2->getScaleY())) / 2.0;
	float rc = (s1->getGeometry()->getRed() + s2->getGeometry()->getRed()) / 2.0;
	float gc = (s1->getGeometry()->getGreen() + s2->getGeometry()->getGreen()) / 2.0;
	float bc = (s1->getGeometry()->getBlue() + s2->getGeometry()->getBlue()) / 2.0;
	copy->setColor(rc,gc,bc);
	copy->setTranslateX(tx);
	copy->setTranslateY(ty);
	copy->setRotation(ro);
	copy->setScaleX(sx);
	copy->setScaleY(sy);
	if(s1->hasChildren() == true){
		vector<sceneNode*> c = s1->getChildren();
		//vector<sceneNode*>::iterator it;
		int si = c.size(); 
		//int counter = 0; 
		for (int i =0; i < si-1; i++ ){
			sceneNode* temp = c[i];
			sceneNode* temp2 = (s2->getChildren())[i];
			sceneNode* copyTemp = (copy->getChildren())[i];
			//counter++; 
			//temp->setText(0, temp->name);
			interpolateTwo(temp,temp2, copyTemp);
		}
	}
	
	return copy; 
}

void qtFrameBook::receiveAddedNode(int sides,QString aName,QString pName){
	sceneNode* temp;
	//emit printFrame(QString("Whee")); 
	for(int i = 0; i < columnCount(); i++){

		vector<sceneNode*> c; 
		rPolygon* p;
		if(sides!=4){
			p = new rPolygon(sides, gVector3(1,1,1));
		}
		else{
			p = new Square( gVector3(1,1,1));
		}
		temp = new sceneNode(gMatrix3().identity(), c, p);
		temp->name = aName; 

		sceneNode* tempRoot = ((qtFrame*) cellWidget(0,i))->root; 
		//if(pName.compare(aName)){
			traverseFramesForAdded(tempRoot,pName,temp);
		//}
		//sceneNode* newRoot = ((qtFrame*) cellWidget(0,i))->root; 
		//emit sendEditSpecificFrame(i,newRoot);
		emit sendEditSpecificFrame(i,tempRoot);
	}
}


void qtFrameBook::traverseFramesForAdded(sceneNode* root, QString pName, sceneNode* addition){
	if(QString::compare(root->name, pName, Qt::CaseSensitive) == 0){
		//vector<sceneNode*> c = root->getChildren();
		bool check = true; 
		vector<sceneNode*>::iterator it1;
		for ( it1=root->children.begin() ; it1 < root->children.end(); it1++ ){
			sceneNode* junk = *it1;
			if(junk->name.compare(addition->name)){
				//check = false; 
			}
		}
		if(check){
			root->children.push_back(addition);
		}
		//root->addAnotherChild(addition);
		//emit printFrame(QString("Whee")); 
		//emit printFrame(QString("FOUND"));
	}
	else if(root->hasChildren() == true){
		vector<sceneNode*> c = root->getChildren();
		vector<sceneNode*>::iterator it;
		for ( it=c.begin() ; it < c.end(); it++ ){
			sceneNode* temp = *it;
			traverseFramesForAdded(temp, pName, addition);
		}
		//emit printFrame(QString("Whee")); 
	}
}

void qtFrameBook::receiveNumberBatchAdd(QString qs){
	float number = qs.toFloat();

	sceneNode* ctemp = ((qtFrame*) cellWidget(0,currentColumn))->root;
		
	if(columnCount() - currentColumn >1){
		sceneNode* temp = ((qtFrame*) cellWidget(0,currentColumn+1))->root; 
		sceneNode* ctemp = ((qtFrame*) cellWidget(0,currentColumn))->root; 
		//insertColumn(currentColumn+1); 
		for(float i = 1; i < number+1; i++){
			sceneNode* inter = new sceneNode();
			//inter = interpolateMany(ctemp, temp,ctemp->copy(), number+1, i);
			//emit sendInterpolatedCopy(inter,ctemp,1); 
			inter = interpolate(ctemp,temp, number+1, i+0);
			inter->keyFrameCheck=true; 
			insertColumn(currentColumn+i);
			emit sendEditSpecificFrame(currentColumn+i,inter);
		}
	}
	else{

		for(float i = 0; i < number; i++){
			//inter = ctemp; 
			//emit sendInterpolatedCopy(ctemp,ctemp,1);
			ctemp = ((qtFrame*) cellWidget(0,currentColumn))->root->copy();
			ctemp->keyFrameCheck=true; 
			insertColumn(currentColumn+i);
			emit sendEditSpecificFrame(currentColumn+i,ctemp);
		}
	}
	setAnimatedFramesNumber(totalNum);
	//emit sendInterpolatedCopy(inter,ctemp,1); 
	
}


sceneNode* qtFrameBook::interpolateMany(sceneNode* s1, sceneNode* s2, sceneNode* copy, float num,float i){
	float tx = (s1->getTranslateX()) + i*(-1*(s1->getTranslateX()) + (s2->getTranslateX())) / num;
	float ty = (s1->getTranslateY()) + i*((s2->getTranslateY()) - (s1->getTranslateY())) / num;
	float ro = (s1->getRotation())+ i*((s2->getRotation()) - (s1->getRotation())) / num;
	float sx = (s1->getScaleX()) + i*((s2->getScaleX()) - (s1->getScaleX())) / num;
	float sy = (s1->getScaleY()) + i*((s2->getScaleY()) - (s1->getScaleY())) / num;
	float rc = s1->getGeometry()->getRed() + i*(s2->getGeometry()->getRed() - s1->getGeometry()->getRed()) / num;
	float gc = s1->getGeometry()->getGreen() + i*(s2->getGeometry()->getGreen() - s1->getGeometry()->getGreen()) / num;
	float bc = s1->getGeometry()->getBlue() + i*(s2->getGeometry()->getBlue() - s1->getGeometry()->getBlue()) / num;
	copy->setColor(rc,gc,bc);
	
	copy->setTranslateX(tx);
	copy->setTranslateY(ty);
	copy->setRotation(ro);
	copy->setScaleX(sx);
	copy->setScaleY(sy);
	 vector<sceneNode*> c1 = s1->getChildren();
 vector<sceneNode*> c2 = s2->getChildren();
 vector<sceneNode*> empty;
 sceneNode* newRoot =  s1->copy();
 newRoot->setChildren(empty);
 for(int i = 0 ; i < c1.size(); i++){
	 newRoot->addAnotherChild(interpolate(c1[i],c2[i],num,i));
 }
	
	return copy; 
}


sceneNode* qtFrameBook::interpolate(sceneNode* s1, sceneNode* s2, float num,float it){ 
 sceneNode* cop =  s1->copy();
 cop->translateX =(s1->translateX) + it * (-1*(s1->translateX) + (s2->translateX)) / num;
 cop->translateY = (s1->translateY) + it*(-1*(s1->translateY) + (s2->translateY)) / num;
 cop->rotation = (s1->rotation) + it*(-1*(s1->rotation) + (s2->rotation)) / num;
 cop->scaleX = (s1->scaleX) + it*(-1*(s1->scaleX) + (s2->scaleX)) / num;
 cop->scaleY = (s1->scaleY) + it*(-1*(s1->scaleY) + (s2->scaleY)) / num;
 float rc = s1->getGeometry()->getRed() + it*(s2->getGeometry()->getRed() - s1->getGeometry()->getRed()) / num;
 float gc = s1->getGeometry()->getGreen() + it*(s2->getGeometry()->getGreen() - s1->getGeometry()->getGreen()) / num;
 float bc = s1->getGeometry()->getBlue() + it*(s2->getGeometry()->getBlue() - s1->getGeometry()->getBlue()) / num;
 cop->setColor(rc,gc,bc);
 vector<sceneNode*> c1 = s1->getChildren();
 vector<sceneNode*> c2 = s2->getChildren();
 vector<sceneNode*> empty;
 cop->setChildren(empty);
 for(int i = 0 ; i < c1.size(); i++){
	 cop->addAnotherChild(interpolate(c1[i],c2[i],num,it));
 }
 return cop;
}

void qtFrameBook::play(){
	qtimer->setInterval(40);
	qtimer->start();
	
	connect(qtimer, SIGNAL(timeout()), this, SLOT(update()));
}

void qtFrameBook::pause(){
	qtimer->stop(); 
}

void qtFrameBook::getUserSpeed(int a){
	int numFrames = ceil( (double) a* 1000 / speed); 
	totalNum = numFrames; 
	setAnimatedFramesNumber(totalNum); 
}

void qtFrameBook::nonlinearPlay(){
	qtimer->setInterval(nlspeed);
	qtimer->start();
	connect(qtimer, SIGNAL(timeout()), this, SLOT(updateNL()));
}

void qtFrameBook::stop(){
	remainderFlag = true; 
	endFrameCounter = 0; 
	betweenFrameCounter = 0;
	qtimer->stop(); 
	playing = false; 
	currentColumn = 0; 
	nlspeed = speed; 
	emit sendCurrentFrame(((qtFrame*) cellWidget(0,0))->root->copy());
}

void qtFrameBook::update(){
	if(currentColumn == columnCount()-1 && (remainder ==0 || !remainderFlag)){
		qtimer->stop(); 
	}
	else if (currentColumn == columnCount()-1 && remainder >0){
		if(remainder == endFrameCounter +1){
			remainderFlag = false; 
		}
		else{
			sceneNode* a = ((qtFrame*) cellWidget(0,currentColumn))->root->copy(); 
			emit sendCurrentFrame(a); 
			endFrameCounter++; 
		}
	}
	else if(currentColumn < columnCount() -1 && endFrameCounter < numBetweenKF){
		sceneNode* a = interpolate(((qtFrame*) cellWidget(0,currentColumn))->root->copy(), 
			((qtFrame*) cellWidget(0,currentColumn+1))->root->copy(),  numBetweenKF +1, endFrameCounter); 
		emit sendCurrentFrame(a);
		endFrameCounter++; 
	}
	else if(currentColumn < columnCount() -1 && endFrameCounter == numBetweenKF ){ 
		currentColumn++; 
		emit sendCurrentFrame(((qtFrame*) cellWidget(0,currentColumn))->root->copy());
		endFrameCounter = 0; 

	}
	else{

	}
}

void qtFrameBook::updateNL(){
	if(currentColumn == columnCount()-1 && (remainder ==0 || !remainderFlag)){
		nlspeed = speed; 
		qtimer->stop(); 
	}
	else if (currentColumn == columnCount()-1 && remainder >0){
		if(remainder == endFrameCounter +1){
			remainderFlag = false; 
		}
		//else{
			sceneNode* a = ((qtFrame*) cellWidget(0,currentColumn))->root->copy(); 
			emit sendCurrentFrame(a);
			nlspeed = pow(nlspeed,1.007); 
			nonlinearPlay(); 
			qtimer->setInterval(nlspeed);
			qtimer->start();
			endFrameCounter++; 
		//}
	}
	else if(currentColumn < columnCount() -1 && endFrameCounter < numBetweenKF){
		sceneNode* a = interpolate(((qtFrame*) cellWidget(0,currentColumn))->root->copy(), 
			((qtFrame*) cellWidget(0,currentColumn+1))->root->copy(),  numBetweenKF +1, endFrameCounter); 
		emit sendCurrentFrame(a);
		nlspeed = pow(nlspeed,1.007); 
		qtimer->setInterval(nlspeed);
		qtimer->start();
		endFrameCounter++; 
	}
	else if(currentColumn < columnCount() -1 && endFrameCounter == numBetweenKF ){ 
		currentColumn++; 
		nlspeed = pow(nlspeed,1.007); 
		qtimer->setInterval(nlspeed);
		qtimer->start();
		emit sendCurrentFrame(((qtFrame*) cellWidget(0,currentColumn))->root->copy());
		endFrameCounter = 0; 

	}
	else{

	}
}

void qtFrameBook::getFrameType(int row,int col){
	bool bt = (dynamic_cast<sceneNode*>(((qtFrame*) cellWidget(row,col))->root))->keyFrameCheck;
	if(bt){
		emit setFrameTypeText(QString("KeyFrame")); 
	}
	else{
		emit setFrameTypeText(QString("Frame")); 
	}
}

void qtFrameBook::setAnimatedFramesNumber(int a){
	totalNum = a; 
	if(columnCount()==1 && a>1){
		remainder = a-1; 
		numBetweenKF = 0; 
		emit changeSliderRange(a); 
	}
	else if(a>=0 && columnCount()<a){
		numBetweenKF = (int) floor((double)(a - columnCount()) / (columnCount() -1)); 
		remainder = a - numBetweenKF * (columnCount()-1) - columnCount() ; 
		emit changeSliderRange(a); 
	}
	else{
		numBetweenKF = 0; 
		remainder = 0; 
		emit changeSliderRange(columnCount()); 
	}

	

	//emit printFrame(QString("%1").arg(columnCount()));
	//emit printFrame(QString("yo %1").arg(numBetweenKF));
	//emit printFrame(QString("ugh %1").arg(remainder));
}

void qtFrameBook::receiveAnimationSliderPosition(int pos){
	position = pos; 
	if(  (numBetweenKF != 0 && (pos-1)%(numBetweenKF+1) == 0)){
		//emit printFrame(QString("poo %1").arg((pos-1)%(numBetweenKF+1)));
		//emit printFrame(QString("Case 1"));
		sceneNode* s;
		int temp = pos/(numBetweenKF+1); 
		s = ((qtFrame*) cellWidget(0,temp))->root;
		emit sendCurrentFrame(s);
		setFrameTypeText("KeyFrame"); 
		
	}
	else if (numBetweenKF ==0 || pos ==1){
		//emit printFrame(QString("Case 2"));
		sceneNode* s;
		//int lower = (int) floor((float)(pos-1) / (numBetweenKF+1));
		int temp = pos-1; 
		if(pos>columnCount()){
			//emit printFrame(QString("Case 3"));
			
			s = ((qtFrame*) cellWidget(0,columnCount()-1))->root;
			s->keyFrameCheck=false;
			emit sendCurrentFrame(s);
			setFrameTypeText("Frame"); 
		}
		else{
			s = ((qtFrame*) cellWidget(0,pos-1))->root;
			emit sendCurrentFrame(s);
			setFrameTypeText("KeyFrame"); 
		}
	}
	else{

		sceneNode* i; 
		int lower = (int) floor((float)(pos-1) / (numBetweenKF+1));
		int upper = (int) ceil((float) (pos-1) / (numBetweenKF+1));
		int denom = numBetweenKF+1; 
		int numer = pos - floor( (float)(pos-1) / (numBetweenKF+1))*(numBetweenKF+1) -1;
		
		if(lower != columnCount()-1){
			i = interpolate(((qtFrame*) cellWidget(0,lower))->root, ((qtFrame*) cellWidget(0,upper))->root, denom, numer); 
			i->keyFrameCheck=false; 
		}
		else{
			i = ((qtFrame*) cellWidget(0,columnCount()-1))->root->copy();
			i->keyFrameCheck=false; 
		}
		i->keyFrameCheck=false; 
		setFrameTypeText("Frame"); 
		emit sendCurrentFrame(i);
	}
}

void qtFrameBook::fadeIn(){
	sceneNode* a = ((qtFrame*) cellWidget(0,0))->root->copy();
	a->setBlack(a); 
	insertColumn(0);
	setAnimatedFramesNumber(totalNum);
	emit sendEditSpecificFrame(0,a); 
}

void qtFrameBook::fadeOut(){
	sceneNode* a = ((qtFrame*) cellWidget(0,columnCount()-1))->root->copy();
	a->setBlack(a); 
	insertColumn(columnCount());
	setAnimatedFramesNumber(totalNum);
	emit sendEditSpecificFrame(columnCount()-1,a); 
}