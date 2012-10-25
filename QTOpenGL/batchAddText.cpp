#include "batchAddText.h"


batchAddText::batchAddText(){

}

batchAddText::batchAddText(QWidget* parent) : QLineEdit(parent){

}

batchAddText::~batchAddText(){

}

void batchAddText::gotClickedNumbers(){
	emit batchAddNumbers(text());
}

void batchAddText::gotAnimatedNumberFrames(){
	emit animatedNumberFrames(text().toInt());
	
}

void batchAddText::gotSetSpeed(){
	emit userSpeed(text().toInt()); 
}